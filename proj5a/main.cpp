/*
 * Proj:      Maze-a
 * Team:      3-AndBoiOsw
 * File:      main.cpp
 * Descr:     declares deck and will operate gameplay.  primary file to compile.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "maze.h"
using namespace std;

int main() {
    ifstream fin;

    // Read the maze from the file.
    string fileName = "maze.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
       cerr << "Cannot open " << fileName << endl;
       exit(1);
    }

    // read file & execute maze operations
    try
    {
        graph g;
        int mazeCounter = 0;
        while (fin && fin.peek() != 'Z')
        {
            // load maze & map maze to graph
            mazeCounter += 1;
            maze m(fin);
            m.mapMazeToGraph(g);

            // debug
            /**
             * m.print(6, 9, 0, 0);
             * g.printNodes();
             * m.print(6, 9, 0, 0);
             * g.printEdges();
             */

            // search algorithms
            //g.printNodes();
            //g.printEdges();
            m.bfs(g, 0, g.numNodes()-1);
            cout << "------------------------------------------------------------\n";
            m.dfs(g, 0, g.numNodes()-1);

            // print completion
            cout << "Congrats on solving Maze " << mazeCounter << "!" << endl;
            //cout << "\n\ni dont have the time for this...\n";  exit(10); // DEBUG WITH LESS OUTPUT
        }
    }
    catch (indexRangeError &ex)
    {
         cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }

    // close file
    fin.close();

    return 0;
}
