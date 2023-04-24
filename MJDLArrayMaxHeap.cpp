//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */ 
 
#include <cmath> // for log2
#include "ArrayMaxHeap.h"
#include <iostream>

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
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex) //Need to pass in itemCount as well????
{
  // implement this function

   /*
   for (subTreeNodeIndex = itemCount / 2 - 1; i >= 0; i-- ) {
      heapRebuild(subTreeNodeIndex);
   }
   */
   
}  // end heapRebuild


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
      std::cout << "The Heap is empty\nThe returned value is garbage";
      return items[0]; //the returned value is garbage
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

   return 0;
}