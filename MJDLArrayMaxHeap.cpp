//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/***********************
Program Name: MJDLArrayMaxHeap
Programmer: Miguel Lock

Class: CSC 145 A
Date: 5-01-23
Version: 1.0
***********************/

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */ 
 
#include <cmath> // for log2
#include "ArrayMaxHeap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Custom exception if stack is too small
class PrecondViolatedExcep : public runtime_error
{
   public:
   PrecondViolatedExcep(const string& message = "") : runtime_error(message) {}
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


/* pseudocode heapRebuild
if subTreeNodeIndex is a leaf, you are done!
if subTreeNodeInex is not a leaf:
   sets values of leftChildIndex and rightChidIndex
   assert that largerChildIndex is the rightChildIndex
   if (largerChildIndex is more than or equal to itemCount) OR if (items[leftChidIndex] is more than items[rightChildIndex]):
      largerChildIndex is the leftChildIndex (inital assertion was wrong)
      if items[subTreeNodeIndex] is less than items[largerChildIndex]:
         swap the two items
         pass largerChildIndex into function heapRebuild
*/
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
   if (itemCount == 0) { return true; }
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
   return itemCount;
}  // end getNumberOfNodes

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
   itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   if (isEmpty()) { throw PrecondViolatedExcep("Error: Inaccessable Item: Heap is empty!"); }
   return items[0];
} // end peekTop

/*pseudocode add
items[itemCount] is assigned the newData

newDataIndex is assigned the itemCount
declare boolean inPlace, set to false
while the newDataIndex is more than or equal to 0 AND if inPlace is false:
   parentIndex is (newDataIndex - 1) / 2
   if items[newDataIndex] is less than or equal to items[parentIndex]:
      set inPlace to true
   otherwise:
      swap the data in items[newDataIndex] and items[parentIndex]
      newDataIndex is assigned to the parentIndex
increment the value of itemCount
return inPlace (which, by this point, is true)
*/
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
   const int arr_size = 20;

   // initialize array myArray size 20 with integers 1-20
   int myArray [arr_size];
   for(int i=0; i < arr_size; i++) {
      myArray[i] = i + 1;
   }

   // print out myArray
   cout << "myArray:\n";
   cout << "[ ";
   for(int i=0; i < arr_size - 1; i++) {
      cout << myArray[i] << ", ";
   }
   cout << myArray[arr_size - 1] << " ]\n\n";

   // create heap myHeap, dump in contents of myArray
   ArrayMaxHeap<int> myHeap;
   for(int i=0; i <= arr_size - 1; i++) {
      myHeap.add(myArray[i]);
   }

   // prints all items form myHeap from top to bottom, removes each item after is read
   // try catch catches PrecondViolatedExcep and prints error message to the screen
   cout << "myHeap from top to bottom:\n";
   int heap_size = myHeap.getNumberOfNodes();
   try {
      cout << "[ ";
      for(int i=0; i < heap_size - 1; i++) {
         cout << myHeap.peekTop() << ", ";
         myHeap.remove();
      }
      cout << myHeap.peekTop() << " ]\n";
   } catch (PrecondViolatedExcep thisTime) {
      cout << "\n" << thisTime.what() << "\n";
   }


   cout << "\n\n\nExtra credit:\n";


   // initialize array extraCreditArray size 20 with integers 1-20, out of order
   int extraCreditArray [arr_size] = { 2, 19, 9, 3, 13, 6, 4, 10, 12, 14, 11, 15, 1, 16, 7, 17, 5, 18, 20, 8 };

   // print out extraCreditArray
   cout << "extraCreditArray:\n";
   cout << "[ ";
   for(int i=0; i < arr_size - 1; i++) {
      cout << extraCreditArray[i] << ", ";
   }
   cout << extraCreditArray[arr_size - 1] << " ]\n\n";

   // create heap extraCreditHeap, dump in contents of extraCreditArray
   ArrayMaxHeap<int> extraCreditHeap;
   for(int i=0; i <= arr_size - 1; i++) {
      extraCreditHeap.add(extraCreditArray[i]);
   }

   // prints all items form extraCreditHeap from top to bottom, removes each item after is read
   // try catch catches PrecondViolatedExcep and prints error message to the screen
   cout << "extraCreditHeap from top to bottom:\n";
   heap_size = extraCreditHeap.getNumberOfNodes();
   try {
      cout << "[ ";
      for(int i=0; i < heap_size - 1; i++) {
         cout << extraCreditHeap.peekTop() << ", ";
         extraCreditHeap.remove();
      }
      cout << extraCreditHeap.peekTop() << " ]\n";
   } catch (PrecondViolatedExcep thisTime) {
      cout << "\n" << thisTime.what() << "\n";
   }

   return 0;
}
