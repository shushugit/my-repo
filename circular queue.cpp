#include <iostream> 
#include <stdlib.h>
using namespace std; 
   
struct Node { 
    int data; 
    struct Node* next; 
}; 
class Queue{
 	public:
   		Queue(): first(),last() {}
   		void push(int data);
   		void pop();
   		void print();
   		Node *first,*last;
};
 
void Queue::push(int value) //�[�J�����ú������� 
{ 
    struct Node *ptr = new Node; //�ؤ@��ptr���� 
    ptr->data = value; //�[�Jvalue 
    if (!this->first) //�Yqueue���� 
        this->first = ptr; 
    else
        this->last->next = ptr; 
     
	this->last = ptr; 
    this->last->next = this->first; //�إ����� 
} 

void Queue::pop() 
{ 
    if (!this->first) 
    { 
        cout<< ("Queue is empty"); 
    } 
    
    if (this->first == this->last) //�p�G�u�Ѥ@��list 
    { 
        struct Node *pop = this->first;//�N�R�� 
        free(pop); 
        this->first = NULL; 
        this->last = NULL; 
    } 
    else  
    { 
        struct Node *ptr = this->first; 
       this->first = this->first->next;//���ʫ��� 
        this->last->next= this->first; 
        free(ptr); //�R�� 
    }    
} 
void Queue::print() 
{ 
    struct Node *ptr = this->first; 
    while (ptr->next != this->first) 
    { 
        cout<<ptr->data<<" "; 
        ptr = ptr->next; 
    } 
    cout<<ptr->data<<endl; 
} 

int main() 
{ 
    Queue *q = new Queue; 
    q->first = q->last = NULL; //first last��l�ۦP�B���]null 
    
    q->push(1); //���եδ��� 
	q->push(2); 
    q->push(3); 
    q->push(4);
    q->push(5);
    q->push(6);
	q->print(); 
    q->pop();
    q->pop();
	q->pop();
    q->pop();
    q->print(); 
    q->push(11); 
    q->push(27); 
    q->print();
} 

