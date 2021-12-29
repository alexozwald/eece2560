

#include <iostream>
#include <cstdlib>
#include "board.cpp"
#include "cell.h"
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
    try
    {
        board b1(SquareSize);

        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
            //cout << b1;
            b1.updateConflicts();
            //b1.printConflicts();
            //Shows whether the board is solved
            if (b1.isSolved() == false)
            {
                cout << "The board has not been solved." << endl;
            }
            else
            {
                cout << "The board is solved." << endl;
            }
        }
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

    // close file
    fin.close();

    return 0;
}



/*
int main()
{
   ifstream fin;

   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
	 b1.initialize(fin);
	 b1.print();
	 b1.printConflicts();
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
 */