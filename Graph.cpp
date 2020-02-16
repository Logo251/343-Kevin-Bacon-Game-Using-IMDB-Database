/*
File Name:  Graph.cpp
Author:     Logan Petersen
Date:       Febuary 2, 2020
Purpose:    The purpose of this code is to be the function definitions for
            the prototypes in Graph.h. The code allows creation of Graph and
            Vertex, the use of Graph, and eventual deletion of both.
*/

#include "Graph.h"

/*
Purpose:          Construct the node when Vertex is created without arguments.
Parameters:       None.
Preconditions:    This specific Vertex object has not been instantiated.
Postconditions:   Vertex object has been instantiated with default values.
Return value:     None.
Functions Called: None.
*/
Graph::Vertex::Vertex() {
   visited = false;
   distanceFromBacon = -1; //Distance to bacon is defaulted to "infinity" because distance unknown.
}

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
Graph::Vertex::Vertex(std::string inputName, std::vector<std::string> inputMovies) {
   name = inputName;
   movies = inputMovies;
   visited = false;
   distanceFromBacon = -1; //Distance to bacon is defaulted to "infinity" because distance unknown.
}

/*
Purpose:          Construct the graph when Graph is created without arguments.
Parameters:       None.
Preconditions:    This specific Graph object has not been instantiated.
Postconditions:   Graph object has been instantiated with default values.
Return value:     None.
Functions Called: None.
*/
Graph::Graph() {}

/*
Purpose:          Delete the memory allocated by this Graph object.
Parameters:       None.
Preconditions:    This specific Graph object has left scope and is slated for deletion.
Postconditions:   Graph object has been deleted with no lost memory.
Return value:     None.
Functions Called: None.
*/
Graph::~Graph() {
   for (Vertex* i : vertices) {
      //Every Vertex inside of Vertices has not been iterated through yet.

      delete i;
   }
}

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
void Graph::Add(std::string inputName, std::vector<std::string> inputShows) {

   //Local variables
   Vertex* newVertex = new Vertex(inputName, inputShows);

   //When the graph is empty, we only need to add the item.
   if(vertices.empty()) {
      vertices.push_back(newVertex);
      return;
   }

   //Check if vertex already exists by name.
   for (Vertex* i : vertices) {
      //Every Vertex inside of Vertices has not been iterated through yet.

      if (i->name == newVertex->name) {
         return;
      }
   }

   //Now that we know that this new vertex belongs in the graph, we can add it and point it, now added, to new things.
   vertices.push_back(newVertex);
   newVertex = vertices.back();

   for (Vertex* i : vertices) {
      //Every Vertex inside of Vertices has not been iterated through yet.

      for (std::string newVertexMovieName : newVertex->movies) {
         //Every movie inside newVertex has not been iterated through yet.

         //If the node being compared is not the node just added, so we do not have nodes pointing to themselves, and the current
         //Vertex being iterated through contains the movie inside newVertex currently being compared.
         if (i->name != newVertex->name && std::find(i->movies.begin(), i->movies.end(), newVertexMovieName) != i->movies.end()) {

            //Make sure we do not already have an edge between these nodes.
            if (std::find(newVertex->edges.begin(), newVertex->edges.end(), i) == newVertex->edges.end()) {
               newVertex->edges.push_back(i);

               //This makes it an undirected graph.
               i->edges.push_back(newVertex);
            }
         }
      }
   }
}

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
std::ostream& operator<<(std::ostream& out, Graph& graph) {

   if (!graph.vertices.empty()) {
      out << graph.GenerateNumbers(graph.FindKevinBacon());
   }
   else {
      out << "No actor/actresses in this Graph.\n";
   }
   return out;
}

/*
Purpose:          Generate a string that contains every actor/actress and their bacon number on seperate lines.
Parameters:       start, a pointer to a Vertex. This is used to start the breadth first search.
Preconditions:    The Graph object has been instantiated.
Postconditions:   Nothing in the Graph changes, and a string is returned to operator<< for printing.
Return value:     A string that contains every actor/actress and their Bacon number properly formatted according to specifications.
Functions Called: None.
*/
std::string Graph::GenerateNumbers(Vertex* start) {

   //Local Variables
   std::queue<Vertex*> bfsQueue;
   std::string output;
   Vertex* poppedVertex;

   //If Kevin Bacon is not in the graph.
   if(start == nullptr) {
      return "Kevin Bacon not in Graph.\n";
   }

   start->distanceFromBacon = 0;
   bfsQueue.push(start);
   start->visited = true;

   while(!bfsQueue.empty()) {
      //The queue contains Vertex pointers.

      //Remove inital vertex, and add to output.
      poppedVertex = bfsQueue.front();
      bfsQueue.pop();
      output += (poppedVertex->name + '\t' + std::to_string(poppedVertex->distanceFromBacon) + '\n');

      for(Vertex* i : poppedVertex->edges) {
         //Every edge of the poppedVertex has not been iterated through yet.

         if(i->visited == false) {
            i->distanceFromBacon = poppedVertex->distanceFromBacon + 1;
            bfsQueue.push(i);
            i->visited = true;
         }
      }
   }

   //For the nodes that are not connected to any other nodes.
   for(Vertex* i : vertices) {
      //Every Vertex inside of Vertices has not been iterated through yet.

      if(i->distanceFromBacon == -1) {
         output += (i->name + '\t' + "infinity" + '\n');
      }
   }
   return output;
}

/*
Purpose:          Find the Kevin Bacon Vertex in the Graph.
Parameters:       None.
Preconditions:    The Graph object has been instantiated.
Postconditions:   Nothing in the Graph changes, and a pointer to either null or the Bacon Vertex is returned.
Return value:     A pointer to either null or the Bacon Vertex is returned. Nullptr is returned if Kevin Bacon does not exist, otherwise
                  the pointer points to the Kevin Bacon Vertex.
Functions Called: None.
*/
Graph::Vertex* Graph::FindKevinBacon() {

   //Local Variables
   Vertex* kevinBaconPtr;

   for(Vertex* i : vertices) {
      //Every Vertex inside of Vertices has not been iterated through yet.

      if(i->name == "Bacon, Kevin (I)") {
         kevinBaconPtr = i;
         return kevinBaconPtr;
      }
   }
   return nullptr;
}
