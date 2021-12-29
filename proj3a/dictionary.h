//
// Created by colin on 10/26/2021.
//

#ifndef INC_3_ANDBOIOSW_3A_DICTIONARY_H
#define INC_3_ANDBOIOSW_3A_DICTIONARY_H
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class dictionary
{
public:
    dictionary();
    void readDictionary(ifstream& fin);
    void sortWords();
    string lookupWord(string word);
    friend ostream& operator<< (ostream& ostr, const dictionary& d);
private:
    //Private variable for full word list
    vector<string> wordList;
};
//Constructor class
dictionary::dictionary()
{

}
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
            wordList.push_back(currentLine);
        }
    }
    fin.close();
}

//Function that sorts the dictionary using selection sort
void dictionary::sortWords()
{
    for(long unsigned int i = 0; i < wordList.size() - 1; i++)
    {
        unsigned long int min = i;
        for(long unsigned int j = i+1; j < wordList.size(); j++)
        {
            //Changes minimum value if encountered
            if(wordList[j] < wordList[min])
                min = j;
        }
        //Swaps once gone through the list one full time
        swap(wordList[i], wordList[min]);
    }
    cout << "done the sort" << endl;
    // create sorted output file to check
    ofstream fout;
    string outFileName = "sorted_dict.txt";
    fout.open(outFileName.c_str());
    for (long unsigned int w=0; w < wordList.size(); w++)
    {
        fout << wordList[w] << "\n";
    }
    fout.close();
}


// alex's alt lookupWord
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
