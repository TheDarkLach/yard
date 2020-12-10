//shuting yard by Faizan Karim
//space reserved for when i start complaining cuz i started late

#include <iostream>
#include <cstring?
#include <iomanip>
#include <stack>
#include "node.h"

using namespace std;

//prototypes
void doPrefix(Node* t);
void doPostfix(Node* t);
void doInfix(Node* t);

//yea idk
int precedence(char* op);

//t = tree
void pushT(Node* &tree, Node* &add);
void popT(Node* &tree);

void enqueue(Node* &front, Node* &rear, char* val);
void dequeue(Node* &front, Node* &rear);
bool isEmpty(Node* front, Node* rear);
void showFront(Node* front, Node* rear);
void displayQueue(Node* front, Node* rear);

//rain drop, drop top
void push(Node* &top, char* val);
void pop(Node* &top);
Node* peek(Node* top);
bool isempty(Node* top);

int main()
{
  int countSigns = 0;
  int countNum = 0;
  
  Node* top = NULL;
  Node* front = NULL;  
  Node* rear = NULL;

  bool run = true;
  char input[100];
  char in[10];

  while(run)
  {
    
  }
}
