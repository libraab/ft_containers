#include "stack.hpp"
#include <iostream>

int main() {
  ft::stack<int> myStack;

  // Push elements onto the stack
  myStack.push(1);
  myStack.push(2);
  myStack.push(3);

  // Display the top element of the stack
  std::cout << "Top element: " << myStack.top() << std::endl;

  // Pop elements from the stack
  myStack.pop();
  std::cout << "Top element after pop: " << myStack.top() << std::endl;
  
  // Check if the stack is empty
  if (myStack.empty()) {
    std::cout << "The stack is empty" << std::endl;
  } else {
    std::cout << "The stack is not empty" << std::endl;
  }

  return 0;
}



