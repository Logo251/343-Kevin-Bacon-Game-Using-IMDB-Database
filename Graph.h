/*
File Name:  Graph.h
Author:     Logan Petersen
Date:       Febuary 2, 2020
Purpose:    This is the header file for the Graph class containing Graph's interface.
            It contains the declarations for Graph's and its structure Vertex's methods
            and variables.
*/

#pragma once

#include <iostream>  //Grants the use of the ostream for operator <<.
#include <vector>    //Grants the vector that will be used for storing movie names.
#include <string>    //Grants string for storage of information such as names of people and movies.
#include <list>      //Grants the list for use of storing edges in Vertex and the Vertices of Graph.
#include <queue>     //Gives a queue, which is used to implement the breadth-first search.
#include <algorithm> //Gives find, which is used when adding new nodes.

class Graph {
public:
   /*
   Purpose:          Construct the graph when Graph is created without arguments.
   Parameters:       None.
   Preconditions:    This specific Graph object has not been instantiated.
   Postconditions:   Graph object has been instantiated with default values.
   Return value:     None.
   Functions Called: None.
   */
   Graph();

   /*
   Purpose:          Delete the memory allocated by this Graph object.
   Parameters:       None.
   Preconditions:    This specific Graph object has left scope and is slated for deletion.
   Postconditions:   Graph object has been deleted with no lost memory.
   Return value:     None.
   Functions Called: None.
   */
   ~Graph();

   /*
   Purpose:          Add a node Vertex to the graph.
   Parameters:       inputName, a string that represents the name of an actor/actress.
                     inputMovies, a vector of strings representing the movies the actor/actress was in.
                     Both of these are used to construct a Vertex for the Graph, which allows Graph to
                     eventually calculate the Bacon number for this actor/actress.
   Preconditions:    A Graph object has been instantiated.
   Postconditions:   The Graph object now contains a node Vertex 
   Return value:     None.
   Functions Called: None.
   */
   void Add(std::string inputName, std::vector<std::string> inputMovies);

   /*
   Purpose:          Output the Bacon numbers for each actor/actress according to specifications.
   Parameters:       out, the ostream that is the stream of characters being sent to the terminal.
                     graph, the Graph that is going to be printed according to specifications.
   Preconditions:    The Graph has been instantiated.
   Postconditions:   If the Graph is empty, print a statement that Graph is empty.
                     Otherwise, display each actor/actress and their Bacon Number according to specifications.
   Return value:     out, an ostream to allow statements to be chained according to operator<<'s specification.
   Functions Called: GenerateNumbers(), a function that generates the string of actors/actresses and their Bacon
                     number based on specifications to be sent to terminal.
                     FindKevinBacon(), a function that returns the location of the Kevin Bacon Vertex.
                     This function prints GenerateNumbers, which requires FindKevinBacon to print the degree's of
                     seperation from Kevin Bacon.
   */
   friend std::ostream& operator<<(std::ostream& out, Graph& graph);
private:
   struct Vertex {

      /*
      Purpose:          Construct the node when Vertex is created without arguments.
      Parameters:       None.
      Preconditions:    This specific Vertex object has not been instantiated.
      Postconditions:   Vertex object has been instantiated with default values.
      Return value:     None.
      Functions Called: None.
      */
      Vertex();

      /*
      Purpose:          Construct the node when Vertex is created with arguments.
      Parameters:       inputName, a string that is an actor/actress's name.
                        inputMovies, a vector of strings, each representing a move that actor/actress was in.
                        these are used to create the Vertex object that will be used to find the actor/actress's
                        Bacon number.
      Preconditions:    This specific Vertex object has not been instantiated.
      Postconditions:   Vertex object has been instantiated with default values excluding given values.
      Return value:     None.
      Functions Called: None.
      */
      Vertex(std::string inputName, std::vector<std::string> inputMovies);

      //Variables
      int distanceFromBacon;           //The distance from Kevin Bacon.
      std::string name;                //The name of the act or this vertex belongs to.
      std::vector<std::string> movies; //The list of movies that is associated with the actor.
      std::list<Vertex*> edges;        //The list of vertices connected to this vertex.
      bool visited;
   };
   std::list<Vertex*> vertices;        //This is the list of vertices pointers in the graph. Each vertex contains its edges.
                                       //It is a list because a vector will change memory locations, breaking pointers.
                                       //I use pointers for this becuase it is quite difficult to do Add with my design without
                                       //these being pointers, the for loop iteration is a temporary variable rather than
                                       //The actual nodes.

   /*
   Purpose:          Generate a string that contains every actor/actress and their bacon number on seperate lines.
   Parameters:       start, a pointer to a Vertex. This is used to start the breadth first search.
   Preconditions:    The Graph object has been instantiated.
   Postconditions:   Nothing in the Graph changes, and a string is returned to operator<< for printing.
   Return value:     A string that contains every actor/actress and their Bacon number properly formatted according to specifications.
   Functions Called: None.
   */
   std::string GenerateNumbers(Vertex* start);

   /*
   Purpose:          Find the Kevin Bacon Vertex in the Graph.
   Parameters:       None.
   Preconditions:    The Graph object has been instantiated.
   Postconditions:   Nothing in the Graph changes, and a pointer to either null or the Bacon Vertex is returned.
   Return value:     A pointer to either null or the Bacon Vertex is returned. Nullptr is returned if Kevin Bacon does not exist, otherwise
                     the pointer points to the Kevin Bacon Vertex.
   Functions Called: None.
   */
   Vertex* FindKevinBacon();
};
