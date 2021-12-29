//
// Created by Alex Oswald on 11/1/21.
//

#ifndef PROJ3B_HEAPSORT_H
#define PROJ3B_HEAPSORT_H

#include <string>
#include <vector>
using namespace std;

template <typename T>
class heap{
public:
    heap();

	T& getItem(int n);

	void initializeMaxHeap(vector<T> &rawList);   // ...
    void buildMaxHeap();                          // ...
	void maxHeapify(int i, int end);                       // ...

    // makes and sorts heap
	vector<T> sortWords();

private:
	// object that stores the heap
	vector<T> heapData;

    int parent(int n);
    int left(int n);
    int right(int n);
};

template <typename T>
heap<T>::heap() {}

//Code for returning the parent of a given child node
template <typename T>
int heap<T>::parent(int n)
{
    return (n / 2);
}

//Code for returning the left child of a given parent node
template <typename T>
int heap<T>::left(int n)
{
    return (2*(n + 1) - 1);
}

//Code for returning the right child of a given parent node
template <typename T>
int heap<T>::right(int n)
{
    return (2*(n + 1));
}

//Returns the current heapData item
template <typename T>
T& heap<T>::getItem(int n)
{
    return heapData[n];
}

template <typename T>
void heap<T>::initializeMaxHeap(vector <T> &rawList)
{
	for (int i=0; i<rawList.size(); i++)
	{
		heapData.push_back(rawList[i]);
	}
	buildMaxHeap(); // makes sure the conditions of a max heap are correctly implemented
}

template<typename T>
void heap<T>::buildMaxHeap()
{
    //A.heapsize = A.length;
    int heapRange = (heapData.size()+1) / 2; // Iterate through half of the tree
    for (int i=heapRange; i >= 0; i--)
    {
        // Recursively send lowest values to leaves
        maxHeapify(i,heapData.size()-1);
    }
}

//Construct the max-heapify of the heap item
template<typename T>
void heap<T>::maxHeapify(int i, int end)
{
    // i is current index in heapData vector
    int left = heap::left(i);
    int right = heap::right(i);
    int largest;

    //If not out of range
    if (left <= end)
    {
        //For when it's the last index
        if (left == end)
        {
            largest = left;
        }
        else
        {
            //Sets equal to the left side if it's larger, right otherwise
            if (heapData[left] > heapData[right])
            {
                largest = left;
            }
            else
            {
                largest = right;
            }
            if (heapData[largest] > heapData[i])
            {
                iter_swap(heapData.begin()+i, heapData.begin()+largest);
				maxHeapify(largest, end);
            }
        }
    }
}

template<typename T>
vector<T> heap<T>::sortWords()
{
	buildMaxHeap();
	int heapSize = heapData.size(); // size of heap after the heap becomes equal to the size of the wordlist
	int length = heapSize - 1;

    while (length > 0)
    {
        iter_swap(heapData.begin()+0, heapData.begin()+length);
        length--;
        maxHeapify(0, length);
    }
	//for (int len = length; len>0; len--)  // go backwards for maxheapify
	//{
    //    iter_swap(heapData.begin()+0, heapData.begin()+len);
	//	heapSize = heapSize - 1;
	//	maxHeapify(heapSize);
	//}
    return heapData;
}

#endif //PROJ3B_HEAPSORT_H
