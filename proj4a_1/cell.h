/*
 * Proj:      Sudoku-a
 * Team:      3-AndBoiOsw
 * File:      cell.h
 * Descr:     class container for each cell of sudoku board and relevant funcs
 */

#ifndef PROJ4A_CELL_H
#define PROJ4A_CELL_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <streambuf>

/****************** SUDOKU BOARD CLASS *******************/
/********************** CELL CLASS ***********************/
// cell container class for each piece of sudoku board - contains cell manipulation fns
class cell {
public:
    //Blank and pre-populated cell
    cell();
    cell(int val);
    //Get and set cell functions
    int getCellValue();
    void setCellValue(int val);
    //All components for setting and getting conflicts
    void clearCell();
    void addConflict(int a);
    vector<int> getConflicts();
    //Overloaded operator to print the cells
    friend ostream &operator<<(ostream &ostr, const cell& c);

    //boolean for whether the number was a part of the original text file
    bool givenInFile = false;
private:
    //Cell value and total conflict vectors
    int cellValue;
    vector<int> cellConflicts;
    vector<int> cellPossibleNumbers;
};
//Base constructor with no variable assignment
cell::cell()  {}

//Constructor with defined starting value
cell::cell(int val)
{
    cellValue = val;

    // board.h inits matrix of cells with value -1, not Null values.  so givenInFile can retreat to class-wide
    // pre-population standard and should be altered on a per-case basis outside of Cell.
    //givenInFile = true;
}

//Gets the value contained in the cell of the board
int cell::getCellValue()
{
    return cellValue;
}

//Sets the value for the specified cell of the board
void cell::setCellValue(int val)
{
    cellValue = val;
}

//Clears the value from the cell to make it blank
void cell::clearCell()
{
    //Resets cell value and clears all of its conflicts
    cellValue = -1;
    givenInFile = false;
    cellPossibleNumbers.clear();
    cellConflicts.clear();
}

//Adds a conflict to a specific cell when # doesn't work
void cell::addConflict(int a)
{
    bool containsA = false;
    for (int i = 0; i < cellConflicts.size(); i++)
    {
        if (cellConflicts[i] == a)
        {
            containsA = true;
        }
    }

    //if a is not contained in
    if (containsA == false)
    {
        if (a != -1)
        {
            cellConflicts.push_back(a);
        }
    }
}

//Returns the integer vector of conflicts for a given cell
vector<int> cell::getConflicts()
{
    return cellConflicts;
}

/***************** OVERLOADED OPERATORS ******************/

// print cell.  for use in board<< operator.
ostream &operator<<(ostream &ostr, const cell& c)
{
    ostr << c.cellValue;
    return ostr;
}

#endif //PROJ4A_CELL_H
