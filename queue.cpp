#include <iostream>
#include <stack>
using namespace std;
template<class T>
class Queue{
	public: //1 2 3 4 5 
    	void enqueue(const T& t){//入隊
        stack1.push(t);
    	}
    	T dequeue(){//出隊 
        	if (stack2.size() == 0) {
            	while (stack1.size() > 0)   //將stack裡所有element倒入stack 2: 5 4 3 2 1
            	{
                	stack2.push(stack1.top());
                	stack1.pop();
            	}
        	}
            	if (stack2.size() > 0) {
                	T data=stack2.top();//data出隊並傳回data:5出隊，傳回5 
                	stack2.pop();
                	return data;
            	}
            	else
            	{
                	cout << "empty" << endl;
                	return NULL;
            	}
    	}
			bool Empty(){//都為空代表入隊出隊結束
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
