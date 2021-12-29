//
// Created by Alex Oswald on 11/1/21.
//

#ifndef PROJ3B_QUICKSORT_H
#define PROJ3B_QUICKSORT_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class quicksort
{
public:
    quicksort();
    int partition(vector<string> &array, int p, int r);
    vector<string> sortWords(vector<string> &array, int left, int right);
};

// constructor
quicksort::quicksort() = default;

// partition
int quicksort::partition(vector<string> &array, int p, int r)
{
    string pivotPoint = array[r];
    int i = p;
    for (int j=p; j < r; j++)
    {
        if (array[j] <= pivotPoint)
        {
            // use iter_swap instead (https://stackoverflow.com/questions/14024228/iter-swap-versus-swap-whats-the-difference)
            iter_swap(array.begin()+i, array.begin()+j);
            //swap(array[i], array[j]);
            i++;
        }
        iter_swap(array.begin()+i, array.begin()+r);
        //swap(array[i], array[r]);
    }
    return i;
}

// quicksort implementation
vector<string> quicksort::sortWords(vector<string> &array, int left, int right)
{
    if(left < right)
    {
        int s = partition(array, left, right);
        sortWords(array, left, s-1 );
        sortWords(array, s+1, right);
    }
    return array;
}

#endif //PROJ3B_QUICKSORT_H
