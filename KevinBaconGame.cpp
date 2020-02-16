/*
File Name:  KevinBaconGame.cpp
Author:     Logan Petersen
Date:       Febuary 2, 2020
Purpose:    The purpose of this code is to read from a file given through argument,
            send parsed information into Graph, then use Graph to return the degrees
            of seperation from Kevin Bacon I. Input data is given to the program through
            an argument to a file location. Valid input is a .txt file that is an excerpt
            from the IMDB database of various movies and TV shows. The file contains an
            actor name at the beginning of a entry, followed by a tab and a movie name,
            which is then potentially followed by extraneous information in this problem.
            The extraneous data is surrounded by square brackets, angled brackets, or
            parenthesis, but in the case of parenthesis it must contain non-numeric
            characters to be considered extraneous. Additional movies for an actor on put
            on following lines indented by a tab. The formatting of input file will generally
            follow this format, but it can mildly deviate. An example of properly formatted
            input is below.

            Petersen, Logan   A Very Interesting Movie (2020) <edited on a Dell E6440>
			                     A Less Interesting Movie (very boring) [version 7]

            The useful data from this is the name Logan Petersen and the movies he participated
            in, A Very Interesting Movie released in 2020 and A Less Interesting Movie.

            Output data is a list of actors and their corresponding Bacon number. Every actor will
            have their own line, and name will be in the order first name last name. The order of
            the sets will be least to greatest, based on the Bacon number. An example is below.

            Logan Petersen 1
            Billy Thomas   1
            Jimmy Pat   2
            Kyle Potters   infinity

            This programs contains no exceptions, but has error handling for conditions such as no
            argument being given to the program and no file being given to the program, Kevin
            Bacon's node not existing in the file, and attempting to print an empty Graph.

            The most imporant algorithm of this program is Graph. Graph stores nodes, named Vertex,
            which contains movie name and actor, with every person getting only one vertex, meaning
            that each vertex stores multiple movies. When a vertex is added, for every vertex current
            in the graph, if the vertex contains a movie also contained in the new vertex, a
            bidirectional edge is created between the two said vertices. After the program is finished
            adding vertices to the graph, Kevin Bacon's node is found by iterating through the list of
            vertices, and a  breadth-first search utilizing a queue is conducted starting from Kevin
            Bacon’s vertex. If Kevin Bacon’s vertex does not exist, then an error is thrown. As the
            breadth-first search is conducted, every vertex discovered is displayed according to the
            specifications given above.

            Key variables are graph, the Graph object, file, the fstream, strings to read in movies and
            names, a vector of strings containing movies, a boolean to delimiate what is the name and
            what is a movie, and a char for the input from file to go to.
*/

#include "Graph.h"
#include <fstream> //Grants file reading, for reading in the database.

int main(int argc, char** argv) {

   //Local Variables
   Graph graph;
   std::fstream file;               //Will be used to read file.
   std::string name;                //Name of actor/actress being added to Graph.
   std::string movie;               //Name of movie that will be added to the movies vector to be added to Graph.
   std::vector<std::string> movies; //Movies a specific actor/actress has been involved in.
   char input;                      //Used to read from cin.
   bool readingName = true;         //Used to parse input from the file. Starts at true because database starts at name.
                                    //Furthermore, after this is false, we are reading movies until a blank line.

   //If no argument was given.
   if (argv[1] == nullptr) {
      std::cout << "No arguments.\n";
      return 0;
   }

   //Open the file for read.
   file.open(argv[1]);

   //If file is open, returns an error if file did not open sucessfully.
   if (file) {
      while (file.get(input)) {
         //The character stream has not ended.

         //This occurs after name field has been read.
         if (input == '\t') {
            readingName = false;
         }

         //Add character to name.
         if (readingName == true) {
            name.push_back(input);
         }

         if (readingName == false) {

            //This covers the case of ()s.
            if (input == '(' && !std::isdigit(file.peek())) {
               while (file.get(input)) {
                  //The character stream has not ended and has not been broken.

                  if (input == ')') {
                     file.get(input);
                     break;
                  }
               }
            }

            //This covers the case of {}.
            if (input == '{') {
               while (file.get(input)) {
                  //The character stream has not ended and has not been broken..

                  if (input == '}') {
                     file.get(input);
                     break;
                  }
               }
            }

            //This covers the case of <> and [].
            if (input == '<' || input == '[') {
               while (file.get(input)) {
                  //The character stream has not ended and has not been broken..

                  if (input == '>' || input == ']') {
                     file.get(input);
                     break;
                  }
               }
            }

            //This covers the case of spaces, and if not space then it is actually a movie.
            //!std::isspace(input)
            if (input != '\n' && input != '\t' && input != ' ') {
               movie.push_back(input);
            }

            //End of line for actor/actress.
            if (file.peek() == EOF || input == '\n' && !movie.empty() && file.peek() == '\t' || file.peek() == '\n') {

               //If movie already exists, no need to duplicate it.
               if (std::find(movies.begin(), movies.end(), movie) == movies.end()) {
                  movies.push_back(movie);
               }
               movie.erase();
            }

            //End of actor/actress entry.
            if (file.peek() == EOF || input == '\n' && file.peek() == '\n') {
               graph.Add(name, movies);
               name.erase();
               movies.clear();
               movie.erase();
               readingName = true;

               //Put reader on the next name.
               while (!file.eof() && !std::isalpha(file.peek())) {
                  //File has not ended and the next character is not a letter of the alphabet.

                  file.get();
               }
            }
         }
      }
   }

   else {
      std::cout << "The file could not be opened.\nPerhaps path is wrong or name does not exist?\n";
   }

   //Print the Bacon Numbers for all actors found.
   std::cout << graph;
   return 0;
}
