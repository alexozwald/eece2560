//
// Created by colin on 10/26/2021.
//

#ifndef INC_3_ANDBOIOSW_3A_DICTIONARY_H
#define INC_3_ANDBOIOSW_3A_DICTIONARY_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "quicksort.h"
#include "selectionsort.h"
#include "heapsort.h"
using namespace std;

class dictionary
{
public:
    dictionary();                                                       // constructor
    void readDictionary(ifstream& fin);                                 // reads file
    string lookupWord(string word);                                     // lookup word in Dict
    friend ostream& operator<< (ostream& ostr, const dictionary& d);    // print sorted dict (overloaded operator)
    // sorting functions  (via outside header files)
    void getSelectionSort();                                            // run selection sort
    void getQuickSort();                                                // run quick sort
    void getHeapSort();                                                 // run heap sort
    void writeDict(string name);                                        // write dict to check work

private:
    // private variable for full (unsorted) word list
    vector<string> rawList;
    //Private variable for full (sorted) word list
    vector<string> wordList;
};

//Constructor class
dictionary::dictionary() {}

//Function to read in all the words from a given dictionary file
void dictionary::readDictionary(ifstream &fin)
{
    string currentLine, endline;
    //Exits program if no file
    if (!fin)
    {
        cout << "No file to read goodbye" << endl;
        exit(1);
    }
    //Starts filling the vector otherwise
    else
    {
        //Runs until the file contains no more information
        while(getline(fin, currentLine))
        {
            currentLine.pop_back();
            //Makes every word lowercase to be read by the user
            if (isupper(currentLine[0]))
            {
                currentLine = tolower(currentLine[0]);
            }
            //Adds the current word to the vector
            rawList.push_back(currentLine);
        }
    }
    fin.close();
}

// write dictionary - takes parameters to indicate sorting type when outputting
void dictionary::writeDict(string name)
{
    // create sorted output file to check
    ofstream fout;
    string outFileName = name;
    fout.open(outFileName.c_str());
    for (long unsigned int w=0; w < wordList.size(); w++)
    {
        fout << wordList[w] << "\n";
    }
    fout.close();
}

void dictionary::getSelectionSort()
{
    selectionsort selSort;
    wordList = selSort.sortWords(rawList);
    writeDict("selsort_dict.txt");
}
void dictionary::getQuickSort()
{
    quicksort qSort;
    wordList = qSort.sortWords(rawList, 0, rawList.size());
    writeDict("quicksort_dict.txt");
}
void dictionary::getHeapSort()
{
    vector<string> tempList = rawList;
    heap<string> hSort;
    hSort.initializeMaxHeap(tempList);
    wordList = hSort.sortWords();
    writeDict("heapsort_dict.txt");
}


// alex's alt lookupWord - a binary search algorithm
string dictionary::lookupWord(string word)
{
    int low = 0;
    int high = wordList.size() - 1;
    string midStr;
    while (low <= high)
    {
        // reset mid variable iteratively + get new mid-word
        int mid = (low + high) / 2;
        midStr = wordList[mid];

        // COMPARE STRINGS DIRECTLY WITH  > < == OPERATORS
        // if dictWord is the same as word -> finish search
        if (midStr == word)
        {
            return word;
        }
        // if dictWord is greater than word -> go lower
        else if (midStr > word)
        {
            high = mid - 1;
        }
        // if dictWord is lesser than word -> go higher
        else if (midStr < word)
        {
            low = mid + 1;
        }
    } // end while loop (finds mid)
    // if no match
    midStr = "";
    return midStr;
}

//Overloaded operator that prints the whole word list.
ostream& operator<< (ostream& ostr, const dictionary& d)
{
    for (long unsigned int i = 0; i < d.wordList.size() - 1; i++)
    {
        ostr << d.wordList[i] << endl;
    }
    return ostr;
}
#endif //INC_3_ANDBOIOSW_3A_DICTIONARY_H
