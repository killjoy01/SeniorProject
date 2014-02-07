/*templatedArray.h
Written by Phil Marinucci
10/10/2012
*/
#pragma once

#define INDEX int

#include <iostream>
using namespace std;
#include <stdio.h>
#include <time.h>

template<typename TYPE>
class tArray{
private:

	//the array that holds everything
	TYPE *arr;

	//last index that contains something in the 
	int currentSize;

	//size of the array
	int maxSize;

	//if currentSize=maxSize, returns true
	bool isFull;

	//if the array is full, make it bigger
	TYPE * allocateBigger(){
		//if array is full
		if(isFull){
			//increase the size of the array by 100
			maxSize+=100;
			//initialize a temp array of the new size
			TYPE * temp = new TYPE[maxSize];

			//copy them over from the actual array to temp
			for(int i = 0; i < currentSize; ++i)
				temp[i] = arr[i];
			//array no longer full
			isFull = false;
			//send out the new array
			return temp;
		}
		else
		{}
	}
	//NOT SURE IF THIS WORKS. NEED TO CHECK
	/*void reallocate(int newsize){
	TYPE* temp = new TYPE[newsize];
	TYPE* old = arr;

	arr = temp;

	for(int i = 0; i < newsize; ++i)
	temp[i] = old[i];

	delete old;
	}*/


public:
	//cotr that inits the array to maxSize
	tArray()
		:currentSize(0), maxSize(10), isFull(false)
	{
		arr = new TYPE[maxSize];

	}

	//cotr that inits the array to whatever size you want
	tArray(int s)
		:currentSize(0), maxSize(s), isFull(false)
	{
		arr = new TYPE[maxSize];
	}

	//move cotr
	tArray(tArray && tArr)
		:currentSize(tArr.maxSize), maxSize(tArr.maxSize), isFull(tArr.isFull)
	{
		tArr.currentSize = 0;
		tArr.maxSize = 0;
		tArr.isFull = false;
	}

	//copy cotr
	void copy(const tArray & tArr){
		tArr.maxSize = maxSize;
		tArr.isFull = isFull;
		tArr.currentSize = currentSize;

		for(int i = 0; i < currentSize; ++i)
			tArr.arr[i] = arr[i];
	}

	//insert something into the array
	void insert(TYPE toAdd){
		//if there is no array
		if(!arr)
			arr = new TYPE[maxSize+10];
		//if array is not full
		if(currentSize < maxSize){
			//add toAdd to the end
			arr[currentSize] = toAdd;
			//make increment the index of the last full spot
			currentSize++;
		}
		//if the array is full
		else{
			//set is full to true
			isFull = true;
			//add 100 to maxsize
			arr = allocateBigger();
			//call again with array not full
			insert(toAdd);
		}
	}

	TYPE & operator[](int index){
		return arr[index];
	}

	//returns the element at index in the array
	TYPE get(int index){
		//if index is in the array
		if(index<currentSize)
			//return the element at index
			return arr[index];
		//if index is not in the array
		else
			//return 0
			throw(exception("Out of bounds"));
	}
	//sets the element at index to data
	void set( int index, TYPE data){
		arr[index] = data;
	}

	//sets all attributes of the array to setTo
	void setAll(TYPE setTo){
		for(int i = 0; i < currentSize; ++i)
			arr[i] = setTo;

	}

	//removes the passed element from the array
	void removeData(TYPE data){
		//init index to 0
		int index = 0;
		//look for data in the array
		for(int i = 0; i < currentSize; ++i)
			//when you find it
			if(arr[i] == data){
				//save the index
				index = i;
				//remove the element at the index
				removeIndex(index);
			}
	}

	//remove the element at the index from the array
	void removeIndex(INDEX index){
		//for each element of the array
		for(int i = index; i < currentSize; ++i)
			//move it back one
			arr[i] = arr[i+1];

		//decriment size
		currentSize--;

	}

	//removes the passed element from the array, then returns it
	TYPE removeAndReturn(TYPE data){
		//init index to 0
		int index = 0;
		//look for data in the array
		for(int i = 0; i < currentSize; ++i)
			//when you find it
			if(arr[i] == data)
				//save the index
				index = i;
		//remove the element at the index
		return removeAndReturn(index);
	}

	//remove the element at the index from the array, then returns it
	TYPE removeNReturn(INDEX index){
		//for each element of the array
		for(int i = index; i < currentSize; ++i)
			//move it back one
			arr[i] = arr[i+1];

		//decriment size
		currentSize--;

	}


	//print each element of the array seperated by a space
	void printWithoutNewLines(){
		if(currentSize)
			for(int i = 0; i < currentSize; ++i)
				cout << arr[i] << " ";
		else
			printf("this list is empty\n");
	}

	//print each element of the array seperated by a new line
	void printWithNewLines(){
		if(currentSize)
			for(int i = 0; i < currentSize; ++i)
				cout << arr[i] << "\n";
		else
			printf("this list is empty\n");
	}

	//prints the element at the index;
	void printElement(int index){
		cout << arr[index];
	}

	//NOT SURE IF IT WORKS
	/*void userReallocate(int newsize){
	if(newsize > currentSize)
	reallocate(newsize);
	}*/

	//empty the array
	void empty(){
		//deletes it
		if(arr){
			delete [] arr;
			//resets currentSize and maxSize to 0 so that you can start again
			currentSize = 0;
			maxSize = 0;
		}
	}

	//returns the number of elements in the array
	int size(){
		return currentSize;
	}

	//checks to see if the passed thing is in the array
	bool isInArray(TYPE toCheck){
		//for each element of the array
		for(int i = 0; i < size(); ++i)
			//check to see if it is the same as the passed element
			if(arr[i] == toCheck)
				//if it is, return true
				return true;

		//if you never find it, return false
		return false;
	}

	//return the element of the array that was passed
	TYPE find(TYPE data){
		//for each element
		for(int i = 0; i < size(); ++i)
			//look for data
			if(arr[i] == data)
				//if you find it, return it
				return arr[i];

		//else return 0
		return 0;
	}

	//returns the index that data is located at
	int findIndex(TYPE data){
		//for each element
		for(int i = 0; i < size(); ++i)
			//look for data
			if(arr[i] == data)
				//when you find it, return the index of data
				return i;

		//else return -1
		return -1;
	}

	void shuffle(){
		//create temperary array of TYPES to hold the shuffled array
		tArray<TYPE> temp;
		//and another temperary array of types to hold the unshuffled array, to deal with directly.
		tArray<TYPE> data;

		//when it's done, will be true
		bool isDone = false;

		//init counter
		TYPE counter;



		//fill array
		for(int i = 0; i < currentSize; ++i){
			//fill data with arr
			data.insert(arr[i]);
		}

		//shuffle the array
		while(!isDone){
			//find a random point in the array that isnt full
			counter =data[rand()%data.size()];
			//fill it
			temp.insert(counter);

			//take the data out of the array
			data.removeData(counter);

			//there is still unsorted data, keep going.
			if(!data.size())
				isDone = true;
		}

		//error checking: if 1/5 of the array is the same as the preshuffle array, redo it.
		int tooMuch = currentSize/5;
		int x = 0;

		for(int i = 0; i < currentSize; ++i)
		{
			if(temp[i] == arr[i])
				x++;
		}

		if(x >= tooMuch)
			shuffle();


		//put the shuffled array back into arr
		for(int x = 0; x < currentSize; ++x)
			arr[x] = temp.get(x);

		//delete them
		temp.empty();
		data.empty();
	}

};