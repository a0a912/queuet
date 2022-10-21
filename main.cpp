
#include <iostream>
#include "QueueT.h"
//#include "Queue2.h"
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



int main()
{
    printf("Hello World");


simpleTest();

    return 0;
}
