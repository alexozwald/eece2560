//
// Created by colin on 10/26/2021.
//

#include <string>
#include <vector>
#include <fstream>
#include "d_matrix.h"
using namespace std;

#ifndef INC_3_ANDBOIOSW_3A_GRID_H
#define INC_3_ANDBOIOSW_3A_GRID_H

class grid
{
public:
    //grid();                               // default constructor
    grid(const string infile);              // constructor passed file
    // return word starting from char at coordinates in direction 'dir' for length 'len'
    string getWord(int row, int col, int dir, int len);
    void printGrid();                       // testing
    int gRow;                   // grid global row dimension
    int gCol;                   // grid global col dimension

private:
    matrix<string> hotGrid;     // imported matrix
};

// constructor passed file
grid::grid(const string infile)
{
    // declarations to open file
    ifstream fin;
    fin.open(infile.c_str());

    // get rows + columns from first line
    string row_str, col_str;
    int row, col;
    getline(fin, row_str, ' ');  // file, var, delimeter to stop at
    //fin.getline(row_str, 1, ' ');  // file, var, delimeter to stop at
    row = stoi(row_str);
    getline(fin, col_str, '\n');  // file, var, delimeter to stop at (default but put in for clarity)
    col = stoi(col_str);

    // resize grid to read-in dimensions
    hotGrid.resize(row, col);

    // read each char to correct location
    string letter;
    for (int y=0; y<row; y++)
    {
        for (int x=0; x<col-1; x++)
        {
            //Get the next letter and place it in the grid
            getline(fin, letter, ' ');
            hotGrid[y][x] = letter;
        }
        // no ' ' before last letter --> read in the rest of the line with getline--no delimiter param
        getline(fin, letter);
        hotGrid[y][col-1] = letter;
    }

    // declare global rows/cols ints
    gRow = row;
    gCol = col;

    // close file
    fin.close();
}

// 'dir' identifier map:
//  7   0   1
//  6   X   2
//  5   4   3
string grid::getWord(int row, int col, int dir, int len)
{
    string word;

    int cRow, cCol; // current row + col ints
    switch (dir)
    {
        case 0:  // up
            for (int i=0; i<len; i++)
            {
                cCol = col;
                cRow = row - i;
                if (cRow < 0)  { cRow = gRow + cRow; }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 1:  // right-up
            for (int i=0; i<len; i++)
            {
                cCol = col + i;
                cRow = row - i;
                if (cRow < 0)  { cRow = gRow + cRow; }
                if (cCol >= gCol)  { cCol = 0 + (cCol - gCol); }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 2:  // right
            for (int i=0; i<len; i++)
            {
                cCol = col + i;
                cRow = row;
                if (cCol >= gCol)  { cCol = 0 + (cCol - gCol); }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 3:  // right-down
            for (int i=0; i<len; i++)
            {
                cCol = col + i;
                cRow = row + i;
                if (cRow >= gRow)  { cRow = 0 + (cRow - gRow); }
                if (cCol >= gCol)  { cCol = 0 + (cCol - gCol); }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 4:  // down
            for (int i=0; i<len; i++)
            {
                cCol = col;
                cRow = row + i;
                if (cRow >= gRow)  { cRow = 0 + (cRow - gRow); }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 5:  // left-down
            for (int i=0; i<len; i++)
            {
                cCol = col - i;
                cRow = row + i;
                if (cRow >= gRow)  { cRow = 0 + (cRow - gRow); }
                if (cCol < 0)  { cCol = gCol + cCol; }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 6:  // left
            for (int i=0; i<len; i++)
            {
                cCol = col - i;
                cRow = row;
                if (cCol < 0)  { cCol = gCol + cCol; }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        case 7:  // left-up
            for (int i=0; i<len; i++)
            {
                cCol = col - i;
                cRow = row - i;
                if (cRow < 0)  { cRow = gRow + cRow; }
                if (cCol < 0)  { cCol = gCol + cCol; }
                word.append(hotGrid[cRow][cCol]);
            }
            break;
        default:
            break;
    }

    // return word made by appendiation
    return word;
}

void grid::printGrid()
{
    for (int x=0; x<gRow; x++)
    {
        for (int y=0; y<gCol; y++)
        {
            cout << hotGrid[x][y] << " ";
        }
        cout << "\n";
    }
}


#endif //INC_3_ANDBOIOSW_3A_GRID_H
