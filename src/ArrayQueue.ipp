//You will need this so you can make a string to throw in
// remove
#include <string>
//Syntax note: This uses the pre-processor to create a constant
// You could also use "const static" to make a constant, as in Java.
// Notice, however, that START_SIZE is NOT a variable! Instead, any
// place that the pre-processor sees "START_SIZE" it will replace it with
// 10 ... so this is like a global "find and replace".
#define START_SIZE 1000

//Syntax note: C++ is not very good at figuring out which methods belong
// to which classes. That is why we have to use the scope operator to
// tell the compiler that this ArrayQueue() method belongs to the
// ArrayQueue<T> class.
template <class T>
ArrayQueue<T>::ArrayQueue(){
    backingArray = new T [START_SIZE];
    front = 0;
    backingArraySize = START_SIZE;
    numItems = 0;
}

template <class T>
ArrayQueue<T>::~ArrayQueue() {
   delete[] backingArray;
}

template <class T>
void ArrayQueue<T>::add(T toAdd){
    if(numItems+1>backingArraySize)
        grow();
    
    backingArray[(front+numItems)%backingArraySize] = toAdd;
    numItems++;

}

template <class T>
  T ArrayQueue<T>::remove(){
  if(numItems==0)
    throw (std::string)"No elements in the array, nothing deleted.";

  T thingToRemove = backingArray[front];
  front ++;
  if (front>=backingArraySize){
     front = 0;
  }
 
   numItems -=1;
  return thingToRemove;
}

template <class T>
unsigned long ArrayQueue<T>::getNumItems(){
    return numItems;
}

template <class T>
void ArrayQueue<T>::grow(){
   T* largerArray = new T[backingArraySize*2];
   if(largerArray==NULL)
        throw (std::string)"Not enough memory to create new array.";
  
   int itemsCopied = 0;
   int index = 0;
   while (itemsCopied<numItems){
      largerArray[index] = remove();
      itemsCopied++;
   }
  
   front = 0;
   backingArraySize *=2;
   delete[] backingArray;

   backingArray = new T[backingArraySize];
   for(int i = 0; i<=numItems; i++){
        backingArray[i] = largerArray[i];
   }
   delete[] largerArray;

}
