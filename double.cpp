void ChangeSize1D(){

    capacity *= 2;                            // 加倍容量
    int *newStack = new int[capacity];        // 建 newStack

    for (int i = 0 ; i < capacity/2; i++) {   // 複製 element 到 newStack
        newStack[i] = stack[i];
    }

    delete [] stack;              // 釋放stack記憶體
    stack = newStack;             // 讓建好的newstack變成stack，完成stack容量加倍
}