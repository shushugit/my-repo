#include <iostream>
#include <stack>
using namespace std;
template<class T>
class Queue{
	public: //1 2 3 4 5 
    	void enqueue(const T& t){//�J��
        stack1.push(t);
    	}
    	T dequeue(){//�X�� 
        	if (stack2.size() == 0) {
            	while (stack1.size() > 0)   //�Nstack�̩Ҧ�element�ˤJstack 2: 5 4 3 2 1
            	{
                	stack2.push(stack1.top());
                	stack1.pop();
            	}
        	}
            	if (stack2.size() > 0) {
                	T data=stack2.top();//data�X���öǦ^data:5�X���A�Ǧ^5 
                	stack2.pop();
                	return data;
            	}
            	else
            	{
                	cout << "empty" << endl;
                	return NULL;
            	}
    	}
			bool Empty(){//�����ťN��J���X������
            	if (stack1.size() == 0 && stack2.size() == 0){
			 		return true;
					} 
            	else{ 
                	return false;
            	} 
        	}
	private:
    	stack<T> stack1;
    	stack<T> stack2;
};
