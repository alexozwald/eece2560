/*
 * Proj:      Sudoku-b
 * Team:      3-AndBoiOsw
 * File:      main.cpp
 * Descr:     declares deck and will operate gameplay.  primary file to compile.
 */

#include <iostream>
#include <cstdlib>
#include "board.h"
using namespace std;


int main()  // inspired by provided board.cpp
{
    // choose which sudoku board to play
    int selection;
    string fileName;
    cout << "Welcome to Sudoku!  Which board would you like to play?\n"
         << "(1) Board 1\n"
         << "(2) Board 2\n"
         << "(3) Board 3\n"
         << "Select:  [[preselected all boards]]";
    //cin >> selection; -> solve all boards!
    switch (selection)
    {
        case 1:
            fileName = "sudoku1.txt";
            break;
        case 2:
            fileName = "sudoku2.txt";
            break;
        case 3:
            fileName = "sudoku3.txt";
            break;
        default:
            fileName = "sudoku1-3.txt";
            break;
    }

    ifstream fin;

    // Read the sample grid from the file.
    fin.open(fileName.c_str());
    if (!fin)
    {
       cerr << "Cannot open " << fileName << endl;
       exit(1);
    }


    // read file to string for simplified board management (using singlefile)
    //string
    cout << "\n\n";

    // begin loop to read combo file & solve sequentially
    int numGrids = 0;           // start count of boards from file
    board b(SquareSize);         // init board to be reused
    while (fin && fin.peek() != 'Z')    // read grids
    {
        // keep grid count + formatting
        numGrids += 1;
        recursionCount = 0;
        cout << "\n├─────────── Sudoku " << numGrids << " ──────────┤\n";

        // stops reading ifstream after BoardSize**2  (ie while loop repeats)
        b.initialize(fin);

        // unsolved board
        cout << "Provided Sudoku Board  (unsolved)\n";
        cout << b;

        // solve board + output
        b.updateConflicts();
        //b.printConflicts();
        //b.solveSudoku();
        b.alexSolveAlt();
        cout << "\nSOLVED Sudoku Board in " << recursionCount << " operations\n";
        cout << b;

        if (fin.peek() == 'Z')
            cout << "├───────────────────────────────┤";
    }

    // close file
    fin.close();

    return 0;
}
