/*
 * Proj:      Sudoku-b
 * Team:      3-AndBoiOsw
 * File:      board.h
 * Descr:     class container for sudoku board
 */
#include <iostream>
#include <climits>      // formerly:  #include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "cell.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


/************** CLASS-PROVIDED DEFINITIONS ***************/
typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    // improvement suggested per compiler  (range-based for loop)
    for (int i : v)
        ostr << i << ' ';
    //for (int i = 0; i < v.size(); i++)
    //    ostr << v[i] << " ";
    return ostr;
}

// ADDED FOR CLARITY PRINTING BOARD + IDENTIFIERS
vector<string> rowIDs = {"ⅰ", "ⅱ", "ⅲ", "ⅳ", "ⅴ", "ⅵ", "ⅶ", "ⅷ", "ⅸ", "ⅹ", "ⅺ", "ⅻ"};
string colIDs = "abcdefghijklmnop";


/****************** SUDOKU BOARD CLASS *******************/
// Stores the entire Sudoku board using cells
class board
{
public:
    // Sample functions
    board(int);
    void clear();
    void initialize(ifstream &fin);
    bool isBlank(int i, int j);
    cell getCell(int i, int j);

    // New functions for 4a
    void setCell(int a, int b, int val);
    void emptyCell(int a, int b);
    bool isSolved();                                        // determines if board is solved
    void setConflicts(int row, int column, cell &cell);     // internal: sets conflicts on a per-cell basis
    void updateConflicts();                                 // update conflicts after modification
    void printConflicts();                                  // print conflicts
    friend ostream& operator<< (ostream& ostr, board& b);   // prints board - replaces print()
    int getSquareMin(int x);                                // gets lower boundary of square given coordinate

    //4b functions
    void solveSudoku();
    void alexSolveAlt();
    void updatePossibilities();
    void findBestCell(int &x, int &y);

private:
      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
      matrix<cell> value;
};


/********* FUNCTION DEFINITIONS, CLASS-INSPIRED **********/
// Board constructor
board::board(int sqSize)
    : value(BoardSize,BoardSize)
{
    clear();
}

// Mark all possible values as legal for each board entry
void board::clear()
{
    for (int i = 0; i < BoardSize; i++)
    {
         for (int j = 0; j < BoardSize; j++)
            {
                value[i][j] = Blank;
            }
    }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;

    clear();

    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
        {
            fin >> ch;

            // If the read char is not Blank
            // all non pre-solved locs start as Null types not cells
            if (ch != '.')
            {
                setCell(i,j,ch-'0');   // Convert char to int
                value[i][j].placedCell = true;
            }
        }
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.

    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

cell board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    //if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
    if ((i >= 0 && i < BoardSize) && (j >= 0 && j < BoardSize))
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 0 || i >= BoardSize || j < 0 || j >= BoardSize)
        throw rangeError("bad value in setCell");

    //char tempCellVal;
    //tempCallVal << getCell(i,j);
    // return (tempCallVal == Blank);
    //return (getCell(i,j).placedCell);
    //return !value[i][j].placedCell;
    if (value[i][j].getCellValue() == Blank)
        return true;
    else
        return false;
}

//Sets an object of the cell class equal to a given cell in the matrix
void board::setCell(int a, int b, int val)
{
    value[a][b].setCellValue(val);
}


//Clear a cell in the matrix at a specific point
void board::emptyCell(int a, int b)
{
    value[a][b].clearCell();
    updateConflicts();
}

//Determines whether the sudoku has been completely filled or not
bool board::isSolved()
{
    bool solved = true;
    updateConflicts();
    for (int i=0; i<BoardSize; i++)
    {
        for (int j=0; j<BoardSize; j++)
        {
            //if any cell is blank the board is not solved
            if (isBlank(i, j))
            {
                solved = false;
            }
        }
    }
    return solved;
}

// DO NOT CHECK THE CURRENT GUESS CELL
// Finds + sets the conflicts for a specific cell in the sudoku
void board::setConflicts(int row, int col, cell& c)
{
    // exit early if cell is not empty
    //if (!isBlank(row,col))
    //    return;

    // remove previous conflicts
    c.getConflicts().clear();

    //Checks for all conflicts within the row
    for (int j=0; j<BoardSize; j++)
    {
        // ignore blank cells or the specified cell
        if (isBlank(row, j) || j == row) // || j == row
            continue;
        else
            c.addConflict(value[row][j].getCellValue());
    }

    //Checks for all conflicts within the column
    for (int i = 0; i < BoardSize; i++)
    {
        // ignore blank cells or the specified cell
        if (isBlank(i, col) || i == col) // || i == col
            continue;
        else
            c.addConflict(value[i][col].getCellValue());
    }

    // get square boundaries to iterate through
    int startRow = getSquareMin(row);
    int startCol = getSquareMin(col);

    //Changes location based on which square it's doing
    for     (int i=startRow;  i < startRow+SquareSize;  i++)
        for (int j=startCol;  j < startCol+SquareSize;  j++)
        {
            if (i == row && j == col)
                continue;
            if (!isBlank(i,j))
                c.addConflict(value[i][j].getCellValue());
        }
}

//Updates the board's cells with their conflicts when needed
//Saves space in other parts of the program to avoid repeating
void board::updateConflicts()
{
    //Goes through every cell and sets the conflicts
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            setConflicts(i, j, value[i][j]);
        }
    }
}

//Prints the conflicts for specific cells on the board
void board::printConflicts()
{
    //cout << " (Row ⨯ Col)\n";
    //For every row
    for (int i = 0; i < BoardSize; i++)
    {
        //For every column
        for (int j = 0; j < BoardSize; j++)
        {
            //cout << "Cell [" << i+1 << "][" << j+1 << "] conflicts: ";
            cout << "Cell [" << colIDs[i] << "," << rowIDs[j] << "]\tconflicts:  ";  // "⨯"
            //Prints out every cell
            //if (value[i][j].getCellValue() != Blank)
            if (isBlank(i,j))
            {
                //cout << value[i][j].getConflicts() << endl;
                vector<int> conflicts = value[i][j].getConflicts();
                cout << conflicts << endl;
            }
            else
            {
                cout << "Known value." << endl;
            }
        }
    }
}

int board::getSquareMin(int x)
{
    int min;
    if (0 <= x && x < 3)
        min = 0;
    else if (3 <= x && x <=6)
        min = 3;
    else if (6 <= x && x < 9)
        min = 6;

    return min;
}

/***************** PROJECT 4b ADDITIONS *****************/
int recursionCount;

void board::alexSolveAlt()
{
    recursionCount++;
    updateConflicts();
    updatePossibilities();

    // logging (commented out later)
    if (recursionCount % 1250 == 0)
        cout << "\nRecursion count: " << recursionCount;

    // we're using the cell placedCell (bool) framework for identifying if it's a guess or not.
    // we loop the entire list to see if there's a perfect fill -> if there is we set the cell as placed with finality
    // and do a recursion call on the loop.
    // if the entire board is looped with no cell identified with 1 possible-value, then a case for 2 possible-values
    // will be entered.  the 2nd case loop
    // second case will be entered


    /**  THIS WAS CODE TO REMOVE IMPERFECT GUESSES BUT WE CHOSE NOT TO PURSUE IT
     *bool errorsHelp = true;
     *while (errorsHelp)
     *{
     *    errorsHelp = false;
     *    //updateConflicts();updatePossibilities();
     *    for (int i=0; i<BoardSize; i++)
     *        for (int j=0; j<BoardSize; j++)
     *        {
     *            // NOT placed cell
     *            // curr value is not blank
     *            // curr value is in conflicts list
     *            // --> set to blank.  double break and dont let it
     *            if (value[i][j].placedCell)
     *                continue;
     *
     *            vector<int> v = value[i][j].getConflicts();
     *            //(!value[i][j].placedCell) &&
     *            if (find(v.begin(), v.end(), value[i][j].getCellValue()) != v.end())
     *            {
     *                errorsHelp = true;
     *                value[i][j].setCellValue(Blank);
     *                cout << "\nMatrix [" << i << "][" << j << "] removed.";
     *            }
     *            v.clear();
     *        }
     *}
     **/

    int numPossibilities;
    bool prevCellFilled = true;
    // find a match of 1 potential-value
    for (int i=0; i<BoardSize; i++)
        for (int j=0; j<BoardSize; j++)
        {
            // skip loop if cell is filled AND/OR ID if prevCellFilled
            if (value[i][j].placedCell && prevCellFilled) {
                prevCellFilled = true;
                continue;
            } // if not prev filled but still already certain:  skip
            else if (value[i][j].placedCell)
                continue;

            prevCellFilled = false;

            // try for perfect match
            numPossibilities = value[i][j].cellPossibleNumbers.size();
            if (numPossibilities == 1 && !value[i][j].placedCell) {
                cout << "\nMatrix [" << i << "][" << j << "] placed.";
                int cellFillNum = value[i][j].cellPossibleNumbers[0];
                value[i][j].setCellValue(cellFillNum);
                value[i][j].placedCell = true;
                return alexSolveAlt();
            }
            // if guess from another recursion is correct...
            //--> that will be found in the former loop.
        }

    // if the entire list was correct -> return from recursive call
    if (prevCellFilled)
        return;

    // case for 2 potential-values
    for (int i=0; i<BoardSize; i++)
        for (int j=0; j<BoardSize; j++)
        {
            updateConflicts();updatePossibilities();
            // alt process to 1 potential-value --> now tests guesses without return recursion, ie more recursive tries
            numPossibilities = value[i][j].cellPossibleNumbers.size();
            if (numPossibilities == 2 && isBlank(i,j)) {
                for (int x=0; x<numPossibilities; x++)
                {
                    int attemptCellNum = value[i][j].cellPossibleNumbers[x];
                    value[i][j].setCellValue(attemptCellNum);
                    alexSolveAlt(); // not RETURN alexSolveAlt() so that the loop can finish if the guess is bad.

                    // if return from recursive call bc cell is placed correctly -> stop testing u whore
                    if (value[i][j].placedCell)
                        break;

                    //// check if guess worked
                    //updateConflicts(); updatePossibilities();
                    //if (value[i][j].cellPossibleNumbers.size() == 1) {
                    //    value[i][j].placedCell = true;
                    //    break;
                    //}
                }
            // if none of the tested values work -> remove it u rat
            if (!value[i][j].placedCell)
                value[i][j].setCellValue(Blank);
            //updateConflicts();updatePossibilities();
            }
        }
    //return;

    // case for 3 potential-values
    for (int i=0; i<BoardSize; i++)
        for (int j=0; j<BoardSize; j++)
        {
            // alt process to 1 potential-value --> now tests guesses without return recursion, ie more recursive tries
            numPossibilities = value[i][j].cellPossibleNumbers.size();
            if (numPossibilities == 3 && !value[i][j].placedCell) {
                for (int x=0; x<numPossibilities; x++)
                {
                    int attemptCellNum = value[i][j].cellPossibleNumbers[x];
                    value[i][j].setCellValue(attemptCellNum);
                    alexSolveAlt();

                    // if return from recursive call bc cell is placed correctly -> stop testing u whore
                    if (value[i][j].placedCell)
                        break;
                }
            }
        }


    // check for case of guess
    //USING IN-FOR-LOOP
    //return;// --> it finished!! (even tho it was wrong) --> fix next loop

    /*
    prevCellFilled = true;
    // loop to check for prev non-return recursions to fall back on
    for (int i=0; i<BoardSize; i++)
        for (int j=0; j<BoardSize; j++)
        {
            if (value[i][j].placedCell && prevCellFilled) {
                prevCellFilled = true;
                continue;
            } else if (value[i][j].placedCell)
                continue;
            prevCellFilled = false;
        }
    */

    //return alexSolveAlt();
    return;

    // if the code makes it here we're in trouble.
    exit (EXIT_FAILURE);
}

void board::updatePossibilities()
{
    vector<int> defaultPossibilities = {1,2,3,4,5,6,7,8,9};
    vector<int> possibilities;
    for (int i=0; i<BoardSize; i++)
        for (int j=0; j<BoardSize; j++)
        {
            value[i][j].cellPossibleNumbers.clear();

            //Creates vector for the conflicts in the cell
            vector<int> conflicts(value[i][j].getConflicts());

            sort(conflicts.begin(), conflicts.end()); // sort the conflicts in preparation for the set_difference
            //it = set_difference(allPossibilities.begin(), allPossibilities.end(), conf.begin(), conf.end(), possibilities.begin());
            // takes all conflicts and removes them from the all possibilities and then adds the nonconflicts into a "possibilities" vector
            set_difference(defaultPossibilities.begin(), defaultPossibilities.end(), conflicts.begin(),
                           conflicts.end(), std::inserter(possibilities,
                                                          possibilities.begin()));
            //Sets possible numbers for the cell to the possibilities variable
            value[i][j].cellPossibleNumbers = possibilities;
            //Clears the vector so it can be reused for all cells
            possibilities.clear();
        }
}













void board::solveSudoku()
{
    //Updates conflicts each run
    updateConflicts();
    //Updates count every time
    recursionCount++;
    //Makes a matrix of the current board in the event it's needed for wrong possibilities
    matrix<cell> currBoard(value);
    //Vectors for default and specific possibilities
    vector<int> defaultPossibilities = {1,2,3,4,5,6,7,8,9};
    vector<int> possibilities;

    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            //Creates vector for the conflicts in the cell
            vector<int> conflicts(value[i][j].getConflicts());
            //Only runs if the cell actually has conflicts
            if (conflicts.size() > 0)
            {
                sort(conflicts.begin(), conflicts.end()); // sort the conflicts in preparation for the set_difference
                //it = set_difference(allPossibilities.begin(), allPossibilities.end(), conf.begin(), conf.end(), possibilities.begin());
                set_difference(defaultPossibilities.begin(), defaultPossibilities.end(), conflicts.begin(), conflicts.end(), std::inserter(possibilities, possibilities.begin())); // takes all conflicts and removes them from the all possibilities and then adds the nonconflicts into a "possibilities" vector
                //Sets possible numbers for the cell to the possibilities variable
                value[i][j].cellPossibleNumbers = possibilities;
                //Clears the vector so it can be reused for all cells
                possibilities.clear();
            }
        }
    }
    //Variables for finding the best cell
    int x = 0;
    int y = 0;
    findBestCell(x,y);
    //Sets possibilities equal to the possibilities of the best cell
    possibilities = value[x][y].cellPossibleNumbers;
    for (int i = 0; i < possibilities.size(); i++)
    {
        //sets the possibility to the given cell
        value[x][y].setCellValue(possibilities[i]);
        solveSudoku();  // recursive call after the previous call was created
        if (!isSolved())
        {
            // if attempts fail -> reset to blank
            value[x][y].setCellValue(Blank);
            for (int row = 0; row < BoardSize; row++)
            {
                for (int col = 0; col < BoardSize; col++)
                {
                    value[row][col] = currBoard[row][col]; // refreshes board if the placement of a possibility is incorrect
                }
            }
        }
        else
            return; // solved
    }
}

void board::findBestCell(int &x, int &y)
{
    //Starts with all possibilities
    int minPossibilities = 9;
    //Runs through each cell
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (isBlank(i, j)) // if the cell is blank
            {
                //Finds the number possibilities for a given cell
                int possibilities = getCell(i, j).cellPossibleNumbers.size();
                //Changes minimum number if the possibilities is smaller than before
                if (possibilities < minPossibilities)
                {
                    minPossibilities = possibilities;
                    x = i;
                    y = j;
                }
            }
        }
    }
}


/***************** OVERLOADED OPERATORS ******************/

// Print sudoku board - overloaded sudoku board << operator
ostream& operator<< (ostream& ostr, board& b)
{
    // prepare row + col ids
    // defined globally

    // i = row.  j = column
    //ostr << "\nCurrent Sudoku Board:\n";

    // print top labels  (clion: not perf monospacing;  terminal: good monospacing... -> choose to keep x>6 or not)
    for (int x=0; x<BoardSize; x++)
    {
        if (x%3 == 0)
            ostr << " ";
        //else if (x > 6)
        //    ostr << " " << rowIDs[x];
        //else
        ostr << "  " << rowIDs[x];
    }
    ostr << endl;

    // print border
    ostr << " ╔═════════╤═════════╤═════════╗";
    for (int i=0; i<MaxValue; i++)
    {
        // separate squares with box-lines
        if ((((i+1) % 3) == 1) && (i+1 != 1))
        {
            ostr << "║\n";
            ostr << " ╟─────────┼─────────┼─────────╢";
            ostr << "\n" << colIDs[i] << "║";
        }
        else if (i+1 != 1)
            ostr << "║\n" << colIDs[i] << "║";
        else if (i == 0)
            ostr << "\n" << colIDs[i] << "║";

        // print main number sequence within each box level boxes
        for (int j=0; j<MaxValue; j++)
        {
            if (b.isBlank(i,j))
                ostr << " · ";
            else
                ostr << ' ' << b.value[i][j] << ' ';

            // separate squares with vert line between boxes
            if ((((j+1) % 3) == 0) && (j+1 != 9))  { ostr <<"│"; }
            //if (j+1 == 9)                          { ostr <<"│"; }
        }
    }
    ostr << "║\n";
    ostr << " ╚═════════╧═════════╧═════════╝";
    ostr << '\n';

    return ostr;
}
