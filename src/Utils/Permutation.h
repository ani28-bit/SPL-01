#ifndef PERMUTATION_H
#define PERMUTATION_H


 class Permutation {

 public:        
    
   
    static void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
  
    
     static void reverse(int arr[], int start, int end) {
        while (start < end) {
            swap(arr[start], arr[end]);
            start++;
            end--;
        }
    }
    
    
    
     static bool contains(int arr[], int size, int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return true;
            }
        }
        return false;
    }
    
    
   
    static int indexOf(int arr[], int size, int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1; 
     }
  };

   #endif