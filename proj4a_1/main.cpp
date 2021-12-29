/*
 * Proj:      Flip-a
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
         << "Select:  ";
    cin >> selection;
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
            fileName = "sudoku1.txt";
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

    // generate grid
    board b1(SquareSize);
    while (fin && fin.peek() != 'Z')
    {
        b1.initialize(fin);
    }
    // close file
    fin.close();

    // execute desired operations
    cout << b1;
    b1.updateConflicts();
    b1.printConflicts();

    // is board solved?
    cout << "STATUS: ";
    if (b1.isSolved())
        cout << "The board is solved." << endl;
    else
        cout << "The board has not been solved." << endl;

    b1.getCell(0,5).getConflicts().clear();

    return 0;
}
