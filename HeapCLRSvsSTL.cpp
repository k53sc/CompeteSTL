// DO WHATEVER YOU WANT TO LICENSE.

// Will create heap out of std::vector in two ways and measure performance of both the ways.
// 1. Use standard make_heap() method 
// 2. Use Introduction to Algorithms - CLRS implementation of creating heap, chapter 6

#include <iostream>
#include <algorithm> // for heap operations
#include <vector>
#include <ctime>
#include <chrono>
#include <numeric>
using namespace std;

// Utility funciton that checks if the list follows the heap property or not.
void check( std::vector<int> list, int max )
{
    if( list.front() == max )
    {
        cout << "passed" << endl;
    }
    else
    {
        cout << "failed" << endl;
    }
}


// ----------------METHODS FOR STD HEAP USAGE ----------------- // 
// create random array and return max element in it
int createRandomArray( int size, std::vector<int> & list )
{
    int max = 0;
    vector<double> timeElapsed;
    for( int itr = 0; itr < size; ++itr )
    {
        int rand = std::rand();
        if( rand > max )
        {
            max = rand;
        }
        list.push_back( rand  );
    }
    return max;
}

// create a random array and heapify it with C++ standards
void stdcheap( std::vector<int> & loopCount )
{
    for( int itr = 0; itr < loopCount.size(); ++itr )
    {
        std::vector<int> list;
        int max = createRandomArray( loopCount[itr], list );

        auto begin = std::chrono::high_resolution_clock::now();
        std::make_heap( list.begin(), list.end() );
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_secs = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        cout << elapsed_secs << endl;

        check( list, max );
    }
}


// ----------------CUTSOM HEAP IMPLEMENTATION CODE STARTS----------------- // 

// return the index of left child
int left( int i, std::vector<int> & list )
{
    if( ( 2*i ) > list.size() )
        return -1;

    return 2*i;
}

// return the index of right child
int right( int i, std::vector<int> & list )
{
    if( ( 2*i + 1 ) > list.size() )
        return -1;

    return 2*i + 1;
}

// core max heap algo
void maxHeap( int index, std::vector<int> & list )
{
    int l = left( index, list );
    int r = right( index, list );

    int largest = index;

    if( l > -1 )
    {
        if( list[index -1] < list[l-1] )
            largest = l;
    }

    if( r > -1 )
    {
        if( list[index-1] < list[r-1] )
        {
            if ( list[r-1] > list[largest -1 ] )
                largest = r;
        }
    }

    if( largest != index )
    {
        // interchange index and largest
        int temp = list[largest-1];
        list[largest-1] = list[index-1];
        list[index-1] = temp;

        maxHeap( largest, list );
    }
}

// make the whole list max heap
void clrsHeap( std::vector<int> & list )
{
    for( int i = ( list.size()/2 ); i > 0; --i )
    {
        maxHeap( i, list );
    }
}

// CLRS approach of creating heap
// Time measured to heapify a random list
void myHeap( std::vector<int> & loopCount )
{
    for( int itr = 0; itr < loopCount.size(); ++itr )
    {
        double timeElapsed;
        std::vector<int> list;
        int max = createRandomArray( loopCount[itr], list );

        auto begin = std::chrono::high_resolution_clock::now();
        clrsHeap( list );
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_secs = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        cout << elapsed_secs << endl;

        check( list, max );
    }

}

// ----------------CUTSOM HEAP IMPLEMENTATION CODE ENDS----------------- // 

// driver code 
// loop count contains number of iteration and each element contains the size of heap
int main()
{
    std::vector<int> loopCount;
    loopCount.push_back( 10 ); // create a heap of size 10
    loopCount.push_back( 100 );
    loopCount.push_back( 1000 );
    loopCount.push_back( 10000 );
    loopCount.push_back( 100000 );
    loopCount.push_back( 1000000 );
    loopCount.push_back( 10000000 );

    stdcheap( loopCount );
    cout << "break" << endl;
    myHeap( loopCount );
}
