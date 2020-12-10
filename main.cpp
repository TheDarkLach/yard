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
    cout << endl << "what do you want to do? Calculate (calc) or quit?" << endl;
    cin.get(in, 10);
    cin.clear();
    cin.ignore(10000, '\n');

    if (strcmp(in, "calc") == 0) {
      cout << "=========Calculate========" << endl;
      cout << "Input equation with infix notation:" << endl;
      cin.get(input, 100);
      cin.clear();
      cin.ignore(10000, '\n');
      
      char** modif = new char*[100];  //clear char* array
      top = front = rear = NULL;  //clear stack & queue
      //begin input splitting:
      //break input by spaces
      int l = 0;  //keeps track of # of chars before space
      int count = 0; //number of chars
      
      for (int i = 0; i < strlen(input); i++)
      {
	if (input[i] == ' ')
	{
	  if (l == 1)
	  {
	    char *temp = new char[10];
	    for (int z = 0; z < sizeof(temp); z++)
	    {  //clear temp memory
	      temp[z] = 0;
	    }
	    temp[0] = input[i-1];
	    modif[count] = temp;
	    count++;
	    l = 0;
	  }
	  else
	  {
	    char *temp = new char[10];
	    for (int z = 0; z < sizeof(temp); z++)
	    {
	      temp[z] = 0;
	    }
	    for (int a = 0; a < l; a++) {
	      temp[a] = input[i-l+a]; 
	    }
	    modif[count] = temp;
	    count++;
	    l = 0;
	  }
	}
	else
	{
	  char *temp = new char[10];
	  for (int z = 0; z < sizeof(temp); z++)
	  {  //clear temp memory
	    temp[z] = 0;
	  }
	  l++;
	  if (i == strlen(input) - 1)
	  {  //last possible pair of chars
	    for (int a = 0; a < l; a++)
	    {
	      temp[a] = input[i+a+1-l];
	    }
	    modif[count] = temp;
	    count++;
	  }
	}
      }
      cout << "Input = Recieved" << endl;
      for (int i = 0; i < count; i++)
      {
	cout << modif[i] << "  p: " << precedence(modif[i]) << endl;
      }
      int c = 0;
      
      // SHUNTING YARD
      while (c < count)
      {
	//if number
	if (precedence(modif[c]) == 0)
	{  
	  //enqueue on output queue
	  enqueue(front, rear, modif[c]);
	}
	if (precedence(modif[c]) == 1 || precedence(modif[c]) == 2 || precedence(modif[c]) == 3)
	{
	  //if token is an operator
	  if (top != NULL) {
	    while (precedence(top->getData()) >= precedence(modif[c]) &&
		   *top->getData() != '(') {
	      //pop from stack and enqueue on output queue
	      enqueue(front, rear, top->getData());
	      pop(top);
	      if (top == NULL) break;
	    }
	  }
	  //push to stack
	  push(top, modif[c]);
	}
	if (*modif[c] == '(') {  //if token is a left parenthesis
	  //push to stack
	  push(top, modif[c]);
	}
	if (*modif[c] == ')') {  //if token is a right parenthesis
	  while (*top->getData() != '(') { 
	    //pop from stack and enqueue on output queue
	    enqueue(front, rear, top->getData());
	    pop(top);
	  }
	  if (*top->getData() == '(') {
	    //pop from stack and discard
	    pop(top);
	  }
	}
	c++; //haha this is the language
      }
      if (c == count) { //if no tokens left to read
	while(top != NULL) {  //while stack is not empty
	  //pop from stack and enqueue on output queue
	  enqueue(front, rear, top->getData());
	  pop(top);
	}
      }
      //cout << "==========================" << endl;
      //print queue node list
      cout << "Binary Tree created based on:" << endl;
      displayQueue(front, rear);
      cout << "with " << count << " tokens." << endl;
      //cout << "==========================" << endl;
      //BEGIN BINARY TREE
      Node* tree = NULL;  //tree stack top
      //turn queue into tree stack
      while (front != rear) {
	Node* n = new Node();
	n->setData(front->getData());
	pushT(tree, n);
	front = front->getNext();
      }
      //do this for rear as well
      Node* n = new Node();
      n->setData(rear->getData());
      pushT(tree, n);
      //output post-, pre-, or in- fix
      cout << "Type in pre, post, or in, if you want to see prefix, postfix, or infix." << endl;
      char in[5];
‎ cin. ‎‎get‎‎(in, ‎‎5‎);
‎ cin. ‎‎clear‎();
‎ cin. ‎‎ignore‎‎(‎‎10000‎‎, ‎‎'‎‎\n‎‎'‎);
      cout << "~Output~" << endl;
      if (strcmp(in, "pre") == 0) {
	doPrefix(tree);  //prefix notation
      } else if (strcmp(in, "post") == 0) {
	doPostfix(tree);  //postfix notation
      } else if (strcmp(in, "in") == 0) {
	doInfix(tree);  //infix notation
      } else {
	cout << "Invalid input :(" << endl;
      }
      cout << endl;
    }
    else if (strcmp(in, "quit") == 0) {
      cout << endl << "Beep Boop, quitting the program" << endl;
      run = false;
    }
    else {
      cout << endl << "Unknown command. Try again." << endl;
    }
  }
}

int precedence(char* op) {
  if (*op == '^') {
    return 3;  //highest precedence
  } else if (*op == '*' || *op == '/') {
    return 2; //second highest precedence
  } else if (*op == '+' || *op == '-') {
    return 1;  //second lowest precedence
  } else if (*op == '(' || *op == ')') {
    return 4;  //whatever value, just different
  }
  else {
    return 0; //number has lowest precedence
  }
}

bool isempty(Node* top) {  //check stack
  if (top == NULL) {
    return true;
  } else {
    return false;
  }
}

//push function to add new element at end of stack  --  thanks CodeWhoop vid
void push (Node* &top, char* val) {
  Node* ptr = new Node();
  ptr->setData(val);
  ptr->setNext(top);
  top = ptr;
}

//pop function to remove newst added element
void pop(Node* &top) {
  if (isempty(top)) {
    cout << "Stack is empty." << endl;
  } else {
    Node* ptr = top;
    top = top->getNext();
    ptr->setNext(NULL);
  }
}

//WOW this is useless, i already have the top, WHAt am i doing
Node* peek(Node* &top) {
  if (isempty(top)) {
    cout << "Stack is empty." << endl;
    Node* no = new Node();
    return no;
  } else {
    return top;
  }
}

//add node to queue  --  thanks CodeWhoop
void enqueue(Node* &front, Node* &rear, char* val) {
  Node* ptr = new Node();
  ptr->setData(val);
  ptr->setNext(NULL);
  if (front == NULL) {  //no node yet
    front = ptr;
    rear = ptr;
  } else {  //one or more nodes existent
    rear->setNext(ptr);
    rear = ptr;
  }
}

//remove first node in queue
void dequeue(Node* &front, Node* & rear) {
  if(isEmpty(front, rear)) {
    cout << "Queue is empty." << endl;
  } else if (front == rear) {  //if one node
    //delete existent node
    front = NULL;
    rear = NULL;
  } else {
    Node* ptr = front;
    front = front->getNext();
    ptr->setNext(NULL);
  }
}

//check if queue is empty
bool isEmpty (Node* front, Node* rear) {
  if (front == NULL && rear == NULL) {
    return true;
  } else {
    return false;
  }
}

void showFront(Node* front, Node* rear) {
  if (isEmpty(front, rear)) {
    cout << "Queue is empty." << endl;
  } else {
    cout << front->getData();
  }
}

void displayQueue(Node* front, Node* rear) {
  if(isEmpty(front, rear)) {  //empty queue
    cout << "Queue is empty." << endl;
  } else {
    Node* ptr = front;
    while (ptr != NULL) {
      cout << ptr->getData() << " ";
      ptr = ptr->getNext();
    }
    cout << endl;
  }
}

//tree functions

void pushT(Node* &tree, Node* &add) {
  if (tree == NULL) {  //empty tree stack
    add->setNext(tree);
    tree = add;
  } else {
    if (precedence(add->getData()) == 0) {  //if a number
      add->setNext(tree);
      tree = add;
    } else {  //if an operator
      //pop last two nodes and keep them
      Node* l = tree;
      popT(tree);
      l->setNext(NULL);
      Node* r = tree;
      popT(tree);
      r->setNext(NULL);
      //push operator node
      add->setNext(tree);
      tree = add;
      //make the two popped numbers left and right pointers of operator node
      tree->setLeft(l);
      tree->setRight(r);
    }
  }
}

void popT(Node* &tree) {
  if (tree == NULL) {
    cout << "Tree stack empty." << endl;
  } else {
    Node* ptr = tree;
    tree = tree->getNext();
    ptr->setNext(NULL);
  }
}

//display final tree -- thanks Wikipedia

void doPrefix(Node* t) {
  if (t != NULL) {
    cout << t->getData() << " ";
    doPrefix(t->getLeft());
    doPrefix(t->getRight());
  }
}

void doPostfix(Node* t) {
  if(t != NULL) {
    doPostfix(t->getLeft());
    doPostfix(t->getRight());
    cout << t->getData() << " ";
  }
}

void doInfix(Node* t) {
  if (t != NULL) {
    if (precedence(t->getData()) != 0) {
      cout << "( ";
    }
    doInfix(t->getLeft());
    cout << t->getData() << " ";
    doInfix(t->getRight());
    if (precedence(t->getData()) != 0) {
      cout << ") ";
    }
  }
}
