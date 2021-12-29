/*
 * Proj:      Flip-a
 * Team:      3-AndBoiOsw
 * File:      main.cpp
 * Descr:     declares deck and will operate gameplay.  primary file to compile.
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "dictionary.h"
#include "grid.h"
using namespace std;

/* RESULTS OF SUCCESSFUL RUNS
 * 15x15 Matrix
 * northeastern, northeaster, northeast, north, students, student, motivated, motivate, trams, dents, eastern, easter,
 * smart, astern, aster, ducat, snake, stern, educated, educate, talented,
 * 30x30 Matrix
 * pointer, point, eared, class, search, inter, construct, stove, array, dolce, leash, graph, algorithm, object, meres,
 * destruct, curse, vector, blank, fused,
 * 50x50 Matrix
 * sliding, peony, nicks, sower, aside, frost, vacation, sledding, robed, tangy, shivering, shiver, snowman, winter,
 * inter, blizzard, hovel, shovel, shove, skiing, beers, clouds,
 */


//Main function that is passed the dictionary and the grid as
//parameters and prints out all candidate words that can be found in the dictionary.
void findMatches(ifstream& myWordFile, string myGridFile, int searchType)
{
    //Creates new dictionary and reads in the words from the file
    dictionary myDict;
    grid myGrid(myGridFile);

    // SWAP COMMENTED SECTIONS TO IMPROVE PERFORMANCE + USE PRESORTED DICT
    // import dictionary from file + sort words using selection sort
    myDict.readDictionary(myWordFile);

    switch(searchType)
    {
        case 1:  // Selection Sort
            myDict.getSelectionSort();
            break;
        case 2:  // Quick Sort
            myDict.getQuickSort();
            break;
        case 3:  // Heap Sort
            myDict.getHeapSort();
            break;
        default: // default:  Quick Sort
            myDict.getQuickSort();
            break;
    }
    
    //Creates vector for the words found in the grid & dictionary
    vector<string> foundWords;

    //Searches for the words using binary search...

    // determine max length of word (min dimension for non-square grids)
    int len_max;
    if ((myGrid.gRow == myGrid.gCol) || (myGrid.gRow < myGrid.gCol))
    {
        len_max = myGrid.gRow - 1;
    }
    else
    {
        len_max = myGrid.gCol - 1;
    }
    //Strings for the temporary word and match word.
    string tempWord, tempMatch;

    // print grid for good measure
    cout << "Chosen grid:" << endl;
    myGrid.printGrid();
    cout << endl;

    //Loops through every row, column, direction, and word length
    for (int x=0; x < myGrid.gCol; x++)
    {
        for (int y=0; y < myGrid.gRow; y++)
        {
            for (int dir=0; dir<8; dir++)
            {
                for (int len = len_max; len >= 5; len--)
                {
                    //Gets value for tempWord and tempMatch
                    tempWord = myGrid.getWord(x, y, dir, len);
                    tempMatch = myDict.lookupWord(tempWord);
                    if (!tempMatch.empty() && len >= 4)
                    {
                        foundWords.push_back(tempMatch);
                    }
                }
            }
        }
    }


    //Prints out the vector of found words
    cout << endl << "All of the words found in the grid are seen below: " << endl;
    for (long unsigned int i = 0; i < foundWords.size()-1; i++)
    {
        //Prints each word in the vector
        cout << foundWords[i] << ", ";
    }
    cout << foundWords[foundWords.size()] << endl;
}

//Function that reads the name of the grid file from the keyboard and
//prints out all words from the candidate word list that is found in the grid.
void search(int searchType)
{
    int searchNumber = searchType;
    /* For when there aren't specified files given in the code
    * string userWord;
    * cout << "Type in your grid" << endl;
    * cin >> userGrid;
    * gridFile.open(userGrid);
    * string userWord;
    * cout << "Type in your list" << endl;
    * cin >> userWord;
    * wordFile.open(userWord);
    * */
    //Variables for grid number and input file streaming
    int gridNumber;
    //inputs for the dictionary file and the grid file
    ifstream wordFile;
    string gridFile;
    //Asks user to choose grids
    cout << "Choose one of the grids from the following list" << endl;
    cout << "(1)  input15.txt\n" << "(2)  input30.txt\n" << "(3)  input50.txt\n";
    cout << "Answer:  ";
    cin >> gridNumber;
    //Opens the correct file given the user's choice for the grid.
    if (gridNumber > 3 || gridNumber < 1)
    {
        //cout << "I hate you please just pick one of them \n";
        exit(1);
    }
    switch(gridNumber)
    {
        case 1:
            gridFile = "input15.txt";
            break;
        case 2:
            gridFile = "input30.txt";
            break;
        case 3:
            gridFile = "input50.txt";
            break;
        default:
            gridFile = "input15.txt";
            break;
    }
    //Opens the word list file
    wordFile.open("Dictionary.txt");
    //Returns the words by running the find matches function
    findMatches(wordFile, gridFile, searchNumber);
    //Closes dictionary file when the search is done
    wordFile.close();
}

//Main function for accessing the search function on startup.
int main()
{
    //Allows the user to choose the sort type
    int searchType;
    cout << "Choose which sorting method you would like to use:\n"
         << "(1)  Selection sort\n"
         << "(2)  Quick sort\n"
         << "(3)  Heap sort\n"
         << "Answer:  ";
    cin >> searchType;
    //For when the sort type is out of bounds
    if (searchType > 3 || searchType < 1)
    {
        cout << "please don't make this harder for us" << endl;
        exit(1);
    }
    else
    {
        //Performs the search specified by the user
        search(searchType);
    }
    return 0;
}
