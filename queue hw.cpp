#include <iostream>
using namespace std;
//push_back empty front pop_front

class list{
	friend class Graph;
private:
    int capacity, front, back;
    int *queue;
public:
    list():capacity(5),front(-1),back(-1){
        queue = new int[capacity];
    };
    void push_back(int x);
    void pop_front();
    bool empty();
    int Front();
    int Back();
    int size();
};

void list::push_back(int x){

    queue[++back] = x;
}
void list::pop_front(){

    front++;        
}

bool list::empty(){

    return (front  == back);
}
int list::Front(){


    return queue[front+1];
}
int list::Back(){

   

    return queue[back];
}
int list::size(){

    return (back - front);
}


void printSequentialQueue (list queue){
    cout << "front: " << queue.Front() << "    back: " << queue.Back() << "\n"
    << "capacity: " <<  "  number of elements: " << queue.size() << "\n\n";
}
int main(){

    list q;
    if (q.empty()) {
        cout << "Queue is empty.\n\n";
    }
    q.push_back(24);
    cout << "After push 24: \n";
    printSequentialQueue(q);
    q.push_back(8);
    q.push_back(23);
    cout << "After push 8, 23: \n";
    printSequentialQueue(q);
    q.pop_front();
    cout << "After pop 24: \n";
    printSequentialQueue(q);
    q.push_back(13);
    cout << "After push 13: \n";
    printSequentialQueue(q);
    q.pop_front();
    cout << "After pop 8: \n";
    printSequentialQueue(q);
    q.push_back(35);
    cout << "After push 35: \n";
    printSequentialQueue(q);
    q.push_back(9);
    cout << "After push 9: \n";
    printSequentialQueue(q);

    return 0;
}
