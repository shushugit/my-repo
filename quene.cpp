class Queue<T> {
		
		
	    private: Stack<T> *inStack;
		         Stack<T> *outStack;
 
	    public:
		
			Queue() {
				inStack = new Stack<T>();
				outStack = new Stack<T>();
				}
 
			enqueue(T t) {
				inStack.push(t);
				}
 
			T dequeue() {
				T temp = null;
				if (!outStack.isEmpty()) {//�˥X����out�̭����� 
					temp = outStack.pop();
				} 
				else {
					while (!inStack.isEmpty()) {
					temp = inStack.pop();
					outStack.push(temp);
				}
 
				if (!outStack.isEmpty()) {
					temp = outStack.pop();
				}
				}
				return temp;
				}
 
	
			boolean isEmpty() {
				return inStack.isEmpty() && outStack.isEmpty();
			}
 
	
			void clear() {
				inStack.clear();
				outStack.clear();
				}
			}
