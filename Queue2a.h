#pragma once
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

//Start Writing
template < class T > class NodeT
{
public:
  T data;
  NodeT *next;

//Constructor

  NodeT (T d, NodeT * t)
  {

    data = d;
    next = t;			///?????
  }

  NodeT (T d)
  {
    data = d;
    next = nullptr;
  }

};

template < class T > class QueueT
{

  /*
     Your class should be implemented using a linked list and should have the following private member variables

     A pointer to a NodeT that represents the front of the queue
     A pointer to a NodeT that represents the back of the queue
     An int that records the current curr_size of the queue (i.e. the number of values in the queue)
   */
private:
  NodeT < T > *front, *rear;
  int curr_size;

public:

  QueueT ();
  QueueT (QueueT < T > *QT);
  QueueT < T > &operator= (const QueueT < T > &QT);

  ~QueueT ();

  void enqueue (T value);

  T dequeue ();

  void print ();

  bool empty ();

  int size ();

  void concatenate (QueueT < T > &concat, int n);

  QueueT < T > *merge (QueueT < T > mer);


  NodeT < T > *getFront ();
};

template < class T > NodeT < T > *QueueT < T >::getFront ()
{

  if (front == nullptr)
    {

      cout << "~~~~Null Value  " << endl;

     throw runtime_error (" empty");
    }

  return front;
};

template < class T > QueueT < T >::QueueT ()
{
  front = nullptr;
  rear = nullptr;
  curr_size = 0;
}

template < class T > QueueT < T >::QueueT (QueueT < T > *QT)
{
  if (QT->curr_size == 0)
    {
      front = nullptr;
      rear = nullptr;
      curr_size = 0;

      return;
    }


  NodeT < T > *temp = QT->front;
//Creating first node
  NodeT < T > *curr = new NodeT < T > (temp->data);
  front = curr;
  curr_size = 1;
//Creating rest of the elements

  while (curr_size < QT->curr_size)
    {
      temp = temp->next;
      NodeT < T > *nn_node = new NodeT < T > (temp->data);
//Connecting prior node to new
      curr->next = nn_node;
      curr = nn_node;
      curr_size++;
    }
  rear = curr;

}

template < class T >
  QueueT < T > &QueueT < T >::operator= (const QueueT < T > &QT)
{

  if (this->curr_size == 0)
    {
      this->front = nullptr;
      this->rear = nullptr;
      this->curr_size = 0;
      return *this;

    }

  NodeT < T > *temp = this->front;
//Creating first node
  NodeT < T > *curr = new NodeT < T > (temp->data);
  this->front = curr;
  curr_size = 1;
//Creating rest of the elements

  while (curr_size < QT.curr_size)
    {
      temp = temp->next;
      NodeT < T > *nn_node = new NodeT < T > (temp->data);
//Connecting prior node to new
      curr->next = nn_node;
      curr = nn_node;
      curr_size++;
    }
  this->rear = curr;

  return *this;
}

template < class T > QueueT < T >::~QueueT ()
{
  int counter = 0;
  NodeT < T > *temp = front;
  while (counter < curr_size)
    {
      if (temp->next != nullptr)
	{
	  front = temp->next;
	}
      delete temp;
      temp = front;
      counter++;

    }
}

template < class T > void QueueT < T >::enqueue (T value)
{

  NodeT < T > *node_to_insert = new NodeT < T > (value);

  //If inserting the first element/node
  if (front == nullptr)
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


template < class T > T QueueT < T >::dequeue ()
{

  if (empty ())
    {
      cout << "~~~Queue is empty\n";

      throw runtime_error (" empty");
    }

  cout << "~~~AFTER";
  //only one element/node in queue.
  if (front == rear)
    {
      cout << endl << "~~~in front == rear";
      T temp = front->data;
      delete (front);
      front = rear = nullptr;
      curr_size = 0;
      cout << "~~~front = rear";
      return temp;
    }
  else
    {
      cout << endl << "~~~in front != rear";
      T temp = front->data;
      NodeT < T > *node_to_remove = front;
      front = front->next;
      cout << "~~~from the other";
      delete node_to_remove;
      curr_size--;
      return temp;
    }

//Trying out other dequeues

/*
// Deque is empty
	if (front == nullptr) {
		throw runtime_error("remove_front failed - empty");
	}
	T result = front->data;
	NodeT < T > *temp = front;
	front = front->next;
	if (front == nullptr) {
		rear = nullptr;
	}
	else {
		front->next = nullptr;
	}

	curr_size--;
	delete temp;
	return result;
	}
*/
/*
 // 
 
        if (front == NULL)
           throw runtime_error("remove_front failed - empty");
  
        // Store previous front and
        // move front one node ahead
        NodeT <T> * temp = front;
        front = front->next;
  
        // If front becomes NULL, then
        // change rear also as NULL
        if (front == NULL)
            rear = NULL;
  
        delete (temp);
        
        */
    }




template < class T > void QueueT < T >::print ()
{
  if (empty ())
    cout << "~~Queue is empty\n";
  else
    {
      NodeT < T > *printer = front;
      while (printer != nullptr)
	{
	  cout << printer->data << endl;
	  printer = printer->next;
	}
    }
}

template < class T > bool QueueT < T >::empty ()
{
  if (curr_size == 0)
    {
      cout << "~~Queue is empty" << endl;
      return true;
    }
  cout << "~~Queue is not empty" << endl;
  return false;
}

template < class T > int QueueT < T >::size ()
{
  return curr_size;
}

template < class T >
  void QueueT < T >::concatenate (QueueT < T > &concat, int n)
{

  cout << endl << "~~n in concat = " << n << endl;
  cout << "~~concat.curr_size " << concat.curr_size;
  if (n > concat.curr_size)
    {				//bad
      throw runtime_error (" empty");
    }
  T temp;
  cout << endl << "~~IN CONCAT 55555";
  for (int ii = 0; ii < n; ii++)
    {
      temp = concat.dequeue ();
      cout << endl << "~~temp in concat :" << temp;
      this->enqueue (temp);
    }
}

/*
QueueT* QueueT::merge(QueueT mer){

cout<<"inside merge";
QueueT* QA = this;
QueueT* QB = &mer;
QueueT* QC;
cout<<"after copy";
int val;
while (QA->curr_size > 0 && QB->curr_size >0){
val = QA->dequeue();
cout<<"val from A =" << val;
QC->enqueue(val);
QC->enqueue(QB->dequeue());

}
cout<<"after mrg1";
while(QA->curr_size >0){
  QC->enqueue(QA->dequeue());
}

while(QB->curr_size >0){
  QC->enqueue(QB->dequeue());
}

return QC;

}
*/
/*
QueueT* QueueT::merge(QueueT mer){

cout<<"inside merge";
QueueT* QA = new QueueT();
QueueT* QB = new QueueT();
QueueT* QC = new QueueT();
QA = this;
QB = &mer;
cout<<"after copy";
int val;
while (QA->curr_size > 0 || QB->curr_size >0){
val = QA->dequeue();
cout<<"val from A =" << val;
QC->enqueue(val);
QC->enqueue(QB->dequeue());

}
cout<<"after mrg1";
while(QA->curr_size >0){
  QC->enqueue(QA->dequeue());
}

while(QB->curr_size >0){
  QC->enqueue(QB->dequeue());
}

return QC;
}
*/

template < class T > QueueT < T > *QueueT < T >::merge (QueueT < T > mer)
{

  cout << "~~inside merge";

  QueueT < T > *QA = new QueueT < T > (this);
  QueueT < T > *QB = new QueueT < T > (&mer);
  QueueT < T > *QC = new QueueT < T > ();
//QA = this;
//QB = &mer;
  cout << "~~after copy";
  while (QA->curr_size > 0 || QB->curr_size > 0)
    {
      if (QA->curr_size != 0)
	{
	  QC->enqueue (QA->dequeue ());
	}

      if (QB->curr_size != 0)
	{
	  QC->enqueue (QB->dequeue ());
	}
    }

  return QC;
}




void
simpleTest ()
{
  cout << "SIMPLE TEST" << endl;
  QueueT < int >q1;

  q1.enqueue (2);
  q1.enqueue (4);
  q1.enqueue (6);

  cout << "empty: 0 = " << q1.empty () << endl;
  cout << "print: {2,4,6} = ";
  q1.print ();
  cout << endl << "curr_size: 3 = " << q1.size () << endl;

  QueueT < int >q2 (q1);
  QueueT < int >q3;
  q3 = q1;

  q1.dequeue ();

  cout << "q1 post copy: {4,6} = ";
  q1.print ();
  cout << endl << "q2 (copy): {2,4,6} = ";
  q2.print ();
  cout << endl << "q3 (op=): {2,4,6} = ";
  q3.print ();

  QueueT < int >q4;
  q4.enqueue (5);

  cout << "content of q1";
  q1.print ();
  QueueT < int >q5 (q1.merge (q4));
  cout << endl << "q5 (merge): {4,5,6} = ";
  q5.print ();
  cout << "content of q1";
  q1.print ();
  cout << "HERE";
  q1.concatenate (q4, 1);
  cout << endl << "q1 (concatenate): {4,6,5} = ";
  q1.print ();



  NodeT < int >*front = q1.getFront ();
  cout << endl << "front->next->data: 6 = " << front->next->data << endl;
  cout << "END SIMPLE TEST" << endl;
}


/*
    QueueT test_qu;
test_qu.print();
    test_qu.enqueue(1);
    test_qu.enqueue(2);
    test_qu.enqueue(3);
   
   QueueT concQ;

   concQ.enqueue(4);
   concQ.enqueue(5);
   concQ.enqueue(6);
   concQ.enqueue(7);
   concQ.enqueue(8);

NodeT* temp1= test_qu.getFront();

cout <<"Testing Temp1   " <<temp1->data << endl;


     cout << "Testing get front  " << test_qu.getFront() << endl;

      // test_qu.concatenate(concQ,  2);

   

    cout << "testing Merge"<< endl;
   QueueT* mergeQ = test_qu.merge(concQ);

 cout << " printing merge"<< endl;
   mergeQ->print();

    cout << " printing test_qu and concQ"<< endl;
    test_qu.print(); concQ.print();

  

    //cout << test_qu(1) <<endl;
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

     constructor b creates an empty queue
     copy constructor b a constructor that creates a deep copy of its constant QueueT reference parameter
     destructor b deallocates dynamic memory allocated by the queue
     operator= b overloads the assignment operator for QueueT b (deep) copies its constant QueueT reference parameter into the calling object and returns a reference to the calling object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the parameter the operator should not copy it
     enqueue b inserts its template type parameter at the back of the queue
     dequeue b removes and returns the value at the front of the queue; if the queue is empty throws a runtime_error (this error class is defined in the stdexcept library file)
     print b prints the contents of the queue, one value per line, from front to back
     empty b returns true if the queue is empty, false otherwise
     curr_size b returns the number of items stored in the queue
     concatenate b has two parameters, a QueueT reference and an integer (referred to as n in this description) adds the first n values stored in its QueueT parameter to the end of the calling object, the resulting queue therefore contains its original contents b order unchanged b followed by the first n values of the parameter queue in their original order; the values added to the calling object should be removed from the parameter; both queue's curr_sizes should be adjusted as appropriate; if n is greater than the curr_size of the parameter a runtime_error should be thrown and no changes made to either queue
     merge b returns a QueueT object that contains the contents of the calling object and its constant QueueT reference parameter, the resulting queue should start with the first value in the calling object, followed by the first value in the parameter, subsequent values should be copied b in order b from the two queues alternating between them; no changes should be made to either the calling object or the parameter; example: calling object = {a,b,c,d,e}, parameter = {r,s,t}, result = {a,r,b,s,c,t,d,e}
     getFront b returns a pointer to the node at the front of the queue. This method is provided to you here: NodeT<T>* getFront() { return front; }; Its purpose is to allow us to directly access your queue's linked list for testing. It is not something a working class should include since allowing access to the internal structure of a class is not good design. Note that if you called your pointer to the node at the front of the queue something other than "front" you will need to change the method's return statement.
     Additional Notes
     The calling object should be made constant for any method where the calling object's attribute values should not change
     You may implement helper methods if you wish (for example, you might want to implement a private method that does the work of copying the parameter to the calling object and then call it in both the copy constructor and the overloaded assignment operator)
     Your class may include other private attributes that you deem necessary - unless the entail significant changes to the structure of the queue described in this document
     Method parameters and return values are noted (and highlighted) in the method descriptions b you must not add additional parameters to the methods; if the method description does not mention a parameter it does not have one, similarly if no return value is mentioned the method is void (or a constructor or destructor)
     The parameter type for enqueue and the return type of dequeue should be your template variable b see the implementation notes near the end of this document
     NodeT Class
     The NodeT class should have a template type attribute for its data and a pointer to the next NodeT in the list. These attributes must be made public and must be named data and next. The class should have constructors as you see fit b I would suggest one with two parameters that sets the data and next NodeT (pointer) to the parameter values and one with a single template type parameter that sets its next pointer to a nullptr.

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
     //b& includes constructor definitions b&
     };

     class QueueT{
     //b&
     };

     //QueueT method implementations
     QueueT::QueueT()
     {
     //b&
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
