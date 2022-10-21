#pragma once
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

//Start Writing
template <class T> 
class NodeT{
  public:
  T data;
  NodeT* next;

NodeT(T d, NodeT* t) {
data = d;
next = t;
}

NodeT(T d){
  data = d;
  next = nullptr;
}
};

template <class T>
class QueueT{
  /*
Your class should be implemented using a linked list and should have the following private member variables

A pointer to a NodeT that represents the front of the queue
A pointer to a NodeT that represents the back of the queue
An int that records the current curr_size of the queue (i.e. the number of values in the queue)
  */
private:
NodeT<T> *front, *rear;
int curr_size;

public:
QueueT<T>();
QueueT<T>(const QueueT<T> &QT);
QueueT<T>& operator=(const QueueT<T>& QT);
~QueueT();
void enqueue(T value);
T dequeue();
void print();
bool empty();
int size();
void concatenate(QueueT<T> &concat, int n);
QueueT<T> merge(const QueueT<T> &mer);
NodeT<T>* getFront();
};

template<class T> 
NodeT<T>* QueueT<T>::getFront() { 
if (front == nullptr){
    cout<< "In getFront: front==nullptr" << endl;
    throw runtime_error(" - empty");
}
return front; 
}

/*

constructor – creates an empty queue
*/

template<class T> 
QueueT<T>::QueueT(){
front = nullptr;
rear = nullptr;
curr_size = 0;
}


/*

copy constructor – a constructor that creates a deep copy of its constant QueueT reference parameter
*/

template<class T> 
QueueT<T>::QueueT(const QueueT<T> &QT){
//cout<<"Copy constructor called"<<endl;
//cout<<"QT.curr_size = " <<QT.curr_size;
if (QT.curr_size == 0){
    front = nullptr;
    rear = nullptr;
    curr_size = 0;
    return;
    }
NodeT <T>*temp = QT.front;
//Creating first node
NodeT<T>* curr = new NodeT<T> (temp->data);
front = curr;
curr_size = 1;
if (QT.curr_size == 1)
    {
    rear = curr;
    }
while (curr_size < QT.curr_size ){
      if (temp->next != nullptr)
      {
          temp = temp->next;
      }
      NodeT<T>* nn_node = new NodeT<T> (temp->data);
      //Connecting prior node to new
      curr->next= nn_node;
      curr = nn_node;
      curr_size++;
    }
rear = curr;
}

/*
operator= – overloads the assignment operator for QueueT – (deep) copies its constant QueueT reference parameter into the calling object and returns a reference to the calling object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the parameter the operator should not copy it

*/


template <class T> 
QueueT<T>& QueueT<T>::operator=(const QueueT<T> &QT){
//If the source is empty queue, make the destination empty
if (QT.curr_size == 0){
  this->front = nullptr;
  this->rear = nullptr;
  this->curr_size = 0;
  return *this;
}
NodeT<T> *temp = QT.front;
//Creating first node
NodeT<T>* curr = new NodeT<T> (temp->data);
this->front = curr;
curr_size = 1;
if (QT.curr_size == 1)
    {
        this->rear = curr;
        return *this;
    }
//Creating rest of the elements
while (curr_size < QT.curr_size ){
      temp = temp->next;
      NodeT<T>* nn_node = new NodeT<T> (temp->data);
      //Connecting prior node to new
      curr->next= nn_node;
      curr = nn_node;
      curr_size++;
      }
curr_size--;
this->rear = curr;
return *this;
}

/*
destructor – deallocates dynamic memory allocated by the queue
*/

template <class T> 
QueueT<T>::~QueueT(){
int counter = 0;
NodeT<T>* temp = front;
while (counter < curr_size){
     if (temp->next != nullptr){
         front = temp->next;
        }
     delete temp;
     temp = front;
     counter++;
    }
}

/*
enqueue – inserts its template type parameter at the back of the queue
*/

template <class T> 
void QueueT<T>::enqueue(T value){
    NodeT<T>* node_to_insert = new NodeT<T>(value);
   //If inserting the first element/node
    if( front == nullptr )
      {
      front = node_to_insert;
      rear = node_to_insert;
      }
    else
      {
      rear->next = node_to_insert;
      rear = node_to_insert;
      }
    curr_size++;
}

/*
dequeue – removes and returns the value at the front of the queue; if the queue is empty throws a runtime_error (this error class is defined in the stdexcept library file)
*/

template <class T> 
T QueueT<T>::dequeue(){
    T ret_val;
    if( empty() )
     {
     cout<<"dequeue(): Empty queue, no items to pop\n";
     throw  runtime_error("dequeue failed - empty");
     }
   // cout<<"dequeue(): Non-Empty queue\n";
    if( front == rear && front!=nullptr)
      {
    //   cout<<endl<<"dequeue(): Only one element";
       T temp = front->data;
       delete front;
       front = rear = nullptr;
       curr_size = 0;
       return temp;
      }
    if( front != rear && front!=nullptr)
      {
      T temp = front->data;
      NodeT<T> *node_to_remove = front;
      front = front->next;
      delete node_to_remove;
      curr_size--;
      return temp;
      }
     return ret_val;
}

/*
print – prints the contents of the queue, one value per line, from front to back

*/

template <class T> 
void QueueT<T>:: print(){
  if (empty())
      cout<<"print(): Empty queue\n";
  else
      {
       NodeT<T> *printer = front;
       while( printer != nullptr)
       {
        cout<<printer->data<< endl;
        printer= printer->next;
       }
      }
    }

/*
empty – returns true if the queue is empty, false otherwise
*/

template <class T> 
bool QueueT<T>:: empty(){
    if (curr_size == 0){
       //cout<<"empty(): True" <<endl;
       return true;
       }
    //cout<<"empty(): False" <<endl;
    return false;
    }

/*
size – returns the number of items stored in the queue
*/

template <class T> 
int QueueT<T>:: size(){
    return curr_size;
 }

/*
concatenate – has two parameters, a QueueT reference and an integer (referred to as n in this description) adds the first n values stored in its QueueT parameter to the end of the calling object, the resulting queue therefore contains its original contents – order unchanged – followed by the first n values of the parameter queue in their original order; the values added to the calling object should be removed from the parameter; both queue's curr_sizes should be adjusted as appropriate; if n is greater than the curr_size of the parameter a runtime_error should be thrown and no changes made to either queue

*/

template <class T> 
void QueueT<T>::concatenate(QueueT<T> &concat, int n){
    if (n > concat.curr_size){//bad
      // cout<<"concatenate(): Given curr_size n > queue curr_size"<<endl;
       throw runtime_error("N too big");
       }
    T temp;
    for(int ii=1; ii <= n; ii++){  
       temp = concat.dequeue();
     //  cout<<endl<<"concatenate(): Item popped = "<<temp;
       this->enqueue(temp);
    }
}
/*
merge – returns a QueueT object that contains the contents of the calling object and its constant QueueT reference parameter, the resulting queue should start with the first value in the calling object, followed by the first value in the parameter, subsequent values should be copied – in order – from the two queues alternating between them; no changes should be made to either the calling object or the parameter; example: calling object = {a,b,c,d,e}, parameter = {r,s,t}, result = {a,r,b,s,c,t,d,e}
g
*/

template <class T> 
QueueT<T> QueueT<T>::merge(const QueueT<T> &mer){
QueueT<T> *QA = new QueueT<T>(*this);
QueueT<T> *QB = new QueueT<T>(mer);
QueueT<T> QC;


int c = 0;
while (QA->curr_size > 0 || QB->curr_size >0){
      c++;
      if (QA->curr_size != 0 ){
          QC.enqueue(QA->dequeue());
        }
      if (QB->curr_size != 0 ){
          QC.enqueue(QB->dequeue());
        }

      }
return QC;
}

/*
//Tests Functions
void simpleTest()
{
	cout << "SIMPLE TEST" << endl;
	QueueT<int> q1;
 
	q1.enqueue(2);
	q1.enqueue(4);
	q1.enqueue(6);
 
	cout << "empty: 0 = " << q1.empty() << endl;
	cout << "print: {2,4,6} = ";
	q1.print();
	cout << endl << "curr_size: 3 = " << q1.size() << endl;
	q1.print();
    cout<<"Breakpoint 1";
 	QueueT<int> q2(q1);
	cout<<"Breakpoint 2";
	QueueT<int> q3;
 	q3 = q1;
 
	q1.dequeue();
 
	cout << "q1 post copy: {4,6} = ";
	q1.print();
	cout << endl << "q2 (copy): {2,4,6} = ";
	q2.print();
	cout << endl << "q3 (op=): {2,4,6} = ";
	q3.print();
 
	QueueT<int> q4;
	q4.enqueue(5);
 
  cout<<"content of q1===";
  q1.print();
  cout<<"content of q4=";
  q4.print();
	QueueT<int> q5(q1.merge(q4));
	cout << endl << "q5 (merge): {4,5,6} : "<<endl;
	q5.print();
    cout<<"content of q1";
    q1.print();
    cout<<"HERE";
	q1.concatenate(q4, 1);
	cout << endl << "q1 (concatenate): {4,6,5} = ";
	q1.print();


 
	NodeT<int>* front = q1.getFront();
	cout << endl << "front->next->data: 6 = " << front->next->data << endl;
	cout << "END SIMPLE TEST" << endl;
}


void simpleTeststr()
 {
 	cout << "SIMPLE TEST" << endl;
 	QueueT<string> q1;

 	q1.enqueue("aaa");
 	q1.enqueue("bbb");
 	q1.enqueue("ccc");

 	cout << "empty: 0 = " << q1.empty() << endl;
 	cout << "print: {aaa,bbb,ccc} = ";
 	q1.print();
 	cout << endl << "curr_size: 3 = " << q1.size() << endl;
 	q1.print();
     cout<<"Breakpoint 1";
  	QueueT<string> q2(q1);
 	cout<<"Breakpoint 2";
 	QueueT<string> q3;
  	q3 = q1;

 	q1.dequeue();

 	cout << "q1 post copy: {4,6} = ";
 	q1.print();
 	cout << endl << "q2 (copy): {2,4,6} = ";
 	q2.print();
 	cout << endl << "q3 (op=): {2,4,6} = ";
 	q3.print();

 	QueueT<string> q4;
 	q4.enqueue("eee");

   cout<<"content of q1";
   q1.print();
 	QueueT<string> q5(q1.merge(q4));
 	cout << endl << "q5 (merge): {4,5,6} : "<<endl;
 	q5.print();
   cout<<"content of q1";
   q1.print();
   cout<<"HERE";
 	q1.concatenate(q4, 1);
 	cout << endl << "q1 (concatenate): {4,6,5} = ";
 	q1.print();



 	NodeT<string>* front = q1.getFront();
 	cout << endl << "front->next->data: 6 = " << front->next->data << endl;
 	cout << "END SIMPLE TEST" << endl;
 }
 
 */
 
/*
int main ()
  {

   // QueueT <int> test_qu;
// test_qu.print();
  //   test_qu.enqueue(1);
  //  test_qu.enqueue(2);
  //  test_qu.enqueue(3);
   
 //  QueueT <int> concQ;

//   concQ.enqueue(4);
//   concQ.enqueue(5);
//   concQ.enqueue(6);
//   concQ.enqueue(7);
//   concQ.enqueue(8);

// NodeT* temp1= test_qu.getFront();

// cout <<"Testing Temp1   " <<temp1->data << endl;


//      cout << "Testing get front  " << test_qu.getFront() << endl;

//       // test_qu.concatenate(concQ,  2);

   

//     cout << "testing Merge"<< endl;
//   QueueT* mergeQ = test_qu.merge(concQ);

//  cout << " printing merge"<< endl;
//   mergeQ->print();

//     cout << " printing test_qu and concQ"<< endl;
//     test_qu.print(); concQ.print();

  

    //cout << test_qu(1) <<endl;


//simpleTest();

//simpleTeststr();

return 0;
  }
*/
 
  /*
Queue Class
Class Description
Your class should be named QueueT and should support these operations:

Creating an empty queue
Inserting a value
Removing a value
Finding the curr_size of the queue
Printing the contents of the queue
Adding the contents of one queue to the end of another
Merging the contents of two queues into a third, new, queue
Class Attributes
Your class should be implemented using a linked list and should have the following private member variables

A pointer to a NodeT that represents the front of the queue
A pointer to a NodeT that represents the back of the queue
An int that records the current curr_size of the queue (i.e. the number of values in the queue)
Queue Public Methods
You must implement a QueueT template class to store data of any type. The queue must be implemented using a singly linked list of nodes, where NodeT is a class that you also implement. The enqueue and dequeue methods should be implemented in constant time.

 The QueueT class should implement the following public methods:

constructor – creates an empty queue
copy constructor – a constructor that creates a deep copy of its constant QueueT reference parameter
destructor – deallocates dynamic memory allocated by the queue
operator= – overloads the assignment operator for QueueT – (deep) copies its constant QueueT reference parameter into the calling object and returns a reference to the calling object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the parameter the operator should not copy it
enqueue – inserts its template type parameter at the back of the queue
dequeue – removes and returns the value at the front of the queue; if the queue is empty throws a runtime_error (this error class is defined in the stdexcept library file)
print – prints the contents of the queue, one value per line, from front to back
empty – returns true if the queue is empty, false otherwise
curr_size – returns the number of items stored in the queue
concatenate – has two parameters, a QueueT reference and an integer (referred to as n in this description) adds the first n values stored in its QueueT parameter to the end of the calling object, the resulting queue therefore contains its original contents – order unchanged – followed by the first n values of the parameter queue in their original order; the values added to the calling object should be removed from the parameter; both queue's curr_sizes should be adjusted as appropriate; if n is greater than the curr_size of the parameter a runtime_error should be thrown and no changes made to either queue
merge – returns a QueueT object that contains the contents of the calling object and its constant QueueT reference parameter, the resulting queue should start with the first value in the calling object, followed by the first value in the parameter, subsequent values should be copied – in order – from the two queues alternating between them; no changes should be made to either the calling object or the parameter; example: calling object = {a,b,c,d,e}, parameter = {r,s,t}, result = {a,r,b,s,c,t,d,e}
getFront – returns a pointer to the node at the front of the queue. This method is provided to you here: NodeT<T>* getFront() { return front; }; Its purpose is to allow us to directly access your queue's linked list for testing. It is not something a working class should include since allowing access to the internal structure of a class is not good design. Note that if you called your pointer to the node at the front of the queue something other than "front" you will need to change the method's return statement.
Additional Notes
The calling object should be made constant for any method where the calling object's attribute values should not change
You may implement helper methods if you wish (for example, you might want to implement a private method that does the work of copying the parameter to the calling object and then call it in both the copy constructor and the overloaded assignment operator)
Your class may include other private attributes that you deem necessary - unless the entail significant changes to the structure of the queue described in this document
Method parameters and return values are noted (and highlighted) in the method descriptions – you must not add additional parameters to the methods; if the method description does not mention a parameter it does not have one, similarly if no return value is mentioned the method is void (or a constructor or destructor)
The parameter type for enqueue and the return type of dequeue should be your template variable – see the implementation notes near the end of this document
NodeT Class
The NodeT class should have a template type attribute for its data and a pointer to the next NodeT in the list. These attributes must be made public and must be named data and next. The class should have constructors as you see fit – I would suggest one with two parameters that sets the data and next NodeT (pointer) to the parameter values and one with a single template type parameter that sets its next pointer to a nullptr.

Your NodeT class must be written in your QueueT.h file, above and outside the QueueT class definition. Your NodeT constructors should be written in the NodeT class definition, and not in a separate NodeT.cpp file.
Implementation Notes
The way I would suggest approaching writing the assignment is something like this:

Create a new project with a file that contains a main function that you will use for testing; add a new QueueT class to the project; then compile and run your project to make sure it is set up correctly
Write your NodeT and QueueT classes as regular, non-template, classes that store a base type, like an int, testing methods as you implement them
Write, and thoroughly test, one or two functions at a time.
Once your class is working perfectly convert it into a template class
Note that Bjarne Stroustrup (Links to an external site.) recommends implementing template classes by first implementing a non-template class version - and I suspect his advice is worth following!

Template classes are often contained in a single .h file as there are compilation issues with breaking them down into separate files, and this is what I want you to do for this assignment. I still want you to keep the implementation separate from the interface as much as possible within this structure, so your method implementations should appear below your QueueT class definition. Your .h file will therefore have this general structure.

//include statements
class NodeT{
         //… includes constructor definitions …
};

class QueueT{
         //…
};

//QueueT method implementations
QueueT::QueueT()
{
         //…
}

Simple Test

Below is a test function that you can use as a very simple and incomplete test of each of the methods that you are to implement. To reiterate - this is not an adequate test of your class! However, if you can't compile and run this simple test you know that your assignment is not ready for submission.

void simpleTest()
{
	cout << "SIMPLE TEST" << endl;
	QueueT<int> q1;
 
	q1.enqueue(2);
	q1.enqueue(4);
	q1.enqueue(6);
 
	cout << "empty: 0 = " << q1.empty() << endl;
	cout << "print: {2,4,6} = ";
	q1.print();
	cout << endl << "curr_size: 3 = " << q1.curr_size() << endl;
 
	QueueT<int> q2(q1);
	QueueT<int> q3;
	q3 = q1;
 
	q1.dequeue();
 
	cout << "q1 post copy: {4,6} = ";
	q1.print();
	cout << endl << "q2 (copy): {2,4,6} = ";
	q2.print();
	cout << endl << "q3 (op=): {2,4,6} = ";
	q3.print();
 
	QueueT<int> q4;
	q4.enqueue(5);
 
	QueueT<int> q5(q1.merge(q4));
	cout << endl << "q5 (merge): {4,5,6} = ";
	q5.print();
 
	q1.concatenate(q4, 1);
	cout << endl << "q1 (concatenate): {4,6,5} = ";
	q1.print();
 
	NodeT<int>* front = q1.getFront();
	cout << endl << "front->next->data: 6 = " << front->next->data << endl;
	cout << "END SIMPLE TEST" << endl;
}



  */
