#include <iostream>
using std::cout;

class QueueArrayCircular{
private:
    int capacity, front, back;
    int *queue;
    void DoubleCapacity();
public:
    QueueArrayCircular():capacity(5),front(0),back(0){ // 從0開始, 第一個位置放掉
                                                       //front 不存東西
        queue = new int[capacity];//建立一個擁有capacity空間的queue
    }
    void Push(int x);
    void Pop();
    bool IsEmpty();
    bool IsFull();
    int getFront();
    int getBack();
    int getSize();
};

void QueueArrayCircular::DoubleCapacity(){

    int *newQueue = new int[capacity*2];

    int j = front, size = getSize();
    for (int i = 1; i <= size; i++) {
        newQueue[i] = queue[++j % capacity];    // j 要先加一, 因為 front 沒有東西
                                                //把原本的queue存到newQueue
    }

    back = getSize();   // 要在更改 capacity 之前抓住 back，知道尾端在哪
    front = 0;          // 改變 front 要在 getSize() 之後
    capacity *= 2;      //capacity加倍

    delete [] queue;    //釋放原本的queue
    queue = newQueue;   //newQueue成為queue
}
void QueueArrayCircular::Push(int x){

    if (IsFull()) {
        DoubleCapacity();
    }

    back = (back + 1)%capacity;//back若超過尾端還需要再放入element
                               //back也要先加一因為front會空一格
                               //直接跳到前面操作pop而空出的記憶體
    queue[back] = x;
}
void QueueArrayCircular::Pop(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    front = (front + 1)%capacity;//front前進，front也要先加一空一格
}
bool QueueArrayCircular::IsEmpty(){

    return (front == back);
}
bool QueueArrayCircular::IsFull(){

    return ((back + 1)%capacity == front);//代表element再push的話會超出capacity，傳回1
}
int QueueArrayCircular::getFront(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";//queuq為空front傳回-1
        return -1;
    }
    return queue[(front + 1)%capacity];
}
int QueueArrayCircular::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }

    return queue[back];//back前面已取mod操作過，直接回傳back即可
}
int QueueArrayCircular::getSize(){//有兩種情況，判斷back現在在前面還是後面

    int size;
    if (front < back) {
        size = back - front;
    }
    else {
        size = capacity - (front - back);
    }

    return size;
}

