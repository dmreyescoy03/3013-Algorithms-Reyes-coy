/*****************************************************************************                 
*  Author:           David Reyes-coy
*  Email:            dmreyescoy0318@my.msutexas.edu
*  Label:            P01
*  Title:            Resizable stack
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This code contains a class that is an array based stack.
*        the stack is resizeable. Grows and shrinks based on the input.
*        even numbers are stored to the stack and odds are thrown out.
*        it will never go bellow 10 and has thresh holds. uses command line.
*  Usage:
*        N/A.
* 
*  Files:            main.cpp:      |driver file|
*                    nums_test.dat  |file for input|
*****************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

class ArrayStack {
private:
  int *A;   // pointer to array of int's
  int top;  // top of stack

public:
  // Default Values
  int size;
  double growthThresh = 0.85;
  double shrinkThresh = 0.15;
  double growthMul = 2.0;
  double shrinkMul = 0.5;
  int numComs = 0;
  int resize = 0;
  int maxSize = 0;
  
  ArrayStack() {
    size = 10;
    A = new int[size];
    top = -1;
  }

  ArrayStack(int s) {
    size = s;
    A = new int[s];
    top = -1;
  }
  
  bool Empty() {
    return (top <= -1);
  }
  
  bool Full() {
    return (top >= size - 1);
  }

  int Peek() {
    if (!Empty()) {
      return A[top];
    }

    return -99;
  }

  int Pop() {
    if (!Empty()) {
      return A[top--];
      checkResize();
    }

    return -99;
  }

  void Print() {
    for (int i = 0; i <= top; i++) {
      cout << A[i] << " ";
    }
    cout << "\n";
  }

  bool Push(int x) {
    if (Full()) {
      ContainerGrow();
    }
    if (!Full()) {
      A[++top] = x;
      checkResize();
      return true;
    }
    return false;
  }

  void ContainerGrow() {
    int newSize = size * growthMul;    // double size of original
    maxSize = newSize; // Set new max size because container grows
    int *B = new int[newSize]; // allocate new memory

    for (int i = 0; i < top; i++) { // copy values to new array
      B[i] = A[i];
    }

    delete[] A; // delete old array

    size = newSize; // save new size

    A = B; // reset array pointer
  }

  void ContainerShrink() {
    int newSize = size * shrinkMul;    // halve size of original
    if (newSize >= 10) {
      int *B = new int[newSize]; // allocate new memory

      for (int i = 0; i < top; i++) { // copy values to new array
        B[i] = A[i];
      }

      delete[] A; // delete old array

      size = newSize; // save new size

      A = B; // reset array pointer
    }
  }

  void checkResize() {
    double check = double(top) / size;
    if (check >= growthThresh) {
      ContainerGrow();
      resize++;
    }
    if (size > 10 && check <= shrinkThresh) {
      ContainerShrink();
      resize++;
    }
  }
};

int main(int argc, char *argv[]) {
  ifstream fin;
  ArrayStack stack;

  int num = 0;

  string file = "nums_test.dat"; // Default file name
  fin.open(file);
  if (argc == 5) {
    stack.growthThresh = atof(argv[1]);
    stack.shrinkThresh = atof(argv[2]);
    stack.growthMul = atof(argv[3]);
    stack.shrinkMul = atof(argv[4]);
  }
  if (argc == 6) {
    stack.growthThresh = atof(argv[1]);
    stack.shrinkThresh = atof(argv[2]);
    stack.growthMul = atof(argv[3]);
    stack.shrinkMul = atof(argv[4]);
    file = argv[5];
  }

  while (!fin.eof()) {
    stack.numComs++;
    fin >> num;
    if (num %2 == 0) {
      stack.Push(num);
    }
    if (num %2 == 1) {
      stack.Pop();
    }
  }

  cout << "Full Threshold: " << stack.growthThresh << "\n";
  cout << "Shrink Threshold: " << stack.shrinkThresh << "\n";
  cout << "Grow Ratio: " << stack.growthMul << "\n";
  cout << "Shrink Ratio: " << stack.shrinkMul << "\n" << "\n";
  cout << "Processed " << stack.numComs << " Commands" << "\n" << "\n";
  cout << "Max Stack Size: " << stack.maxSize << "\n";
  cout << "End Stack Size: " << stack.size << "\n";
  cout << "Stack Resized: " << stack.resize << "\n";

  return 0;
}
