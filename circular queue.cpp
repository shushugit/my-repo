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
 
void Queue::push(int value) //加入元素並維持環狀 
{ 
    struct Node *ptr = new Node; //建一個ptr指標 
    ptr->data = value; //加入value 
    if (!this->first) //若queue為空 
        this->first = ptr; 
    else
        this->last->next = ptr; 
     
	this->last = ptr; 
    this->last->next = this->first; //建立環狀 
} 

void Queue::pop() 
{ 
    if (!this->first) 
    { 
        cout<< ("Queue is empty"); 
    } 
    
    if (this->first == this->last) //如果只剩一個list 
    { 
        struct Node *pop = this->first;//就刪掉 
        free(pop); 
        this->first = NULL; 
        this->last = NULL; 
    } 
    else  
    { 
        struct Node *ptr = this->first; 
       this->first = this->first->next;//移動指標 
        this->last->next= this->first; 
        free(ptr); //刪掉 
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
    q->first = q->last = NULL; //first last初始相同且先設null 
    
    q->push(1); //測試用測資 
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

