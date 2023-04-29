//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */ 
 
#include <cmath> // for log2
#include "ArrayMaxHeap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Custom exception in case stack is too small
class PrecondViolatedExcep : public std::runtime_error
{
   public:
   PrecondViolatedExcep(const std::string& message = "") : std::runtime_error(message) {}
};


template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}  // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}  // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}  // end isLeaf

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   // Recursively trickle the item at index nodeIndex down to its proper position by 
   // swapping it with its larger child, if the child is larger than the item. 
   // If the item is at a leaf, nothing needs to be done. 
   if (!isLeaf(subTreeNodeIndex))
   {
      // The root must have a left child; find larger child 
      int leftChildIndex = getLeftChildIndex(subTreeNodeIndex);
      int rightChildIndex = getRightChildIndex(subTreeNodeIndex);
      int largerChildIndex = rightChildIndex; // Assume right child exists and is the larger 
      // Check whether right child exists; if so, is left child larger? 
      // If no right child, left one is larger 
      if ((largerChildIndex >= itemCount) || (items[leftChildIndex] > items[rightChildIndex]))
         largerChildIndex = leftChildIndex; // Assumption was wrong 
         if (items[subTreeNodeIndex] < items[largerChildIndex])
         {
            swap(items[subTreeNodeIndex], items[largerChildIndex]);
            // Transform the semiheap rooted at largerChildIndex into a heap
            heapRebuild(largerChildIndex);
         }
      }
      // Else root is a leaf, so you are done 
}



template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);  
   }  // end for
}  // end heapCreate

//******************************************************************
// 
// Public methods start here
//
//******************************************************************

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
    items = new ItemType[DEFAULT_CAPACITY];
}

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
   // Allocate the array
   items = new ItemType[2 * arraySize];

   
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   
   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{  
   delete [] items;
}  // end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
   if (itemCount == 0) {
      return true;
   }
   
   return false;
}  // end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
   return ceil(log2(itemCount + 1));
}  // end getHeight

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
  // implement this function
   return -1;
   //return itemCount; Is this it?
}  // end getNumberOfNodes

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
   itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const //throw(PrecondViolatedExcep)
{
   if (isEmpty()) {
      throw PrecondViolatedExcep("Error: Precondition Violated: Heap is empty!");
   }
   
   return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
   //Place new data at the bottom of the tree
   items[itemCount] = newData;

   //Make new item bubble up the the appropriate spot in the tree
   int newDataIndex = itemCount;
   bool inPlace = false;
   while ((newDataIndex >= 0) && !inPlace) {
      int parentIndex = (newDataIndex - 1) / 2;
      if (items[newDataIndex] <= items[parentIndex]) {
         inPlace = true;
      }
      else {  //swap items[newDataIndex] and items[parentIndex]
         ItemType temp = items[newDataIndex];
         items[newDataIndex] = items[parentIndex];
         items[parentIndex] = temp;
         newDataIndex = parentIndex;
      }
   }
   
   itemCount++;
   return inPlace;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   bool isSuccessful = false;
   if (!isEmpty()) 
   {
      items[ROOT_INDEX] = items[itemCount - 1];
      itemCount--;
      heapRebuild(ROOT_INDEX);
      isSuccessful = true;
   }  // end if
   
   return isSuccessful;
}  // end remove


int main() {
   std::cout << "Hello world!\n";

   int myArray [20];

   for(int i=0; i < 20; i++) {
      myArray[i] = i + 1;
   }
   
   std::cout << "[ ";
   for(int i=0; i < 19; i++) {
      std::cout << myArray[i] << ", ";
   }
   std::cout << myArray[19] << " ]\n\n";

   ArrayMaxHeap<int> myHeap;

   for(int i=0; i < 19; i++) {
      myHeap.add(myArray[i]);
   }


   //myHeap.clear();

   std::cout << myHeap.isEmpty();

   try {
        std::cout << myHeap.peekTop();
   } catch (PrecondViolatedExcep thisTime) {
        cout << thisTime.what();  // prints exception if peek fails
   }

   return 0;
}