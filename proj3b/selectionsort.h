//
// Created by Alex Oswald on 11/1/21.
//

#ifndef PROJ3B_SELECTIONSORT_H
#define PROJ3B_SELECTIONSORT_H

#include <string>
#include <vector>
using namespace std;

class selectionsort
{
public:
    selectionsort();
    vector<string> sortWords(vector<string> rawList);
};

// constructor
selectionsort::selectionsort() {}

//Function that sorts the dictionary using selection sort
vector<string> selectionsort::sortWords(vector<string> rawList)
{
    for(long unsigned int i = 0; i < rawList.size() - 1; i++)
    {
        unsigned long int min = i;
        for(long unsigned int j = i+1; j < rawList.size(); j++)
        {
            //Changes minimum value if encountered
            if(rawList[j] < rawList[min])
                min = j;
        }
        //Swaps once gone through the list one full time
        swap(rawList[i], rawList[min]);
    }
    //cout << "done the sort" << endl;

    return rawList;
}

#endif //PROJ3B_SELECTIONSORT_H
