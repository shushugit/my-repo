#include <iostream> 
#include <queue>
using namespace std ;
template <class T > 
class  A{ //stack A
    public : 
        //push function of stack
        void  addTail ( const T & node ){//插入element 
            if  ( B . size ( )  >  0  && C . size ( )  >  0 ) 
        {
            cout<<"error"; 
        } 
            else //插入到非空queue，如果均為空則插入到C中
        { 
            if  ( B . size ( )  ==  0) 
                { 
                C . push ( node ) ; 
            } 
            else 
                { 
                B . push ( node ) ; 
            } 
        } 
    }
        //pop function of stack
        T deleteHead ( ) 
      { 
        if  ( B . size ( )  ==  0  && C . size ( )  ==  0 ) 
        { 
            cout <<"stack is empty"  ; 
        } 
        T head ; 
        if  ( B . size ( )  >  0) { 
            while  ( B . size ( ) > 1 ) 
            { 
                //B中的元素依次刪除，並插入到C中，其中B的最後一個element取出傳回head
                T & data = B . front ( ) ; 
                B . pop ( ) ; 
                C . push ( data ) ; 
            } 
        head = B . front ( ) ; //head存入B的最後一個
        B . pop ( ) ; 
    } 
        else { 
            while  ( C . size ( ) > 1 ) 
            {
                //C中的元素依次刪除，並插入到B中，其中C刪除最後一個元素
                T & data = C . front ( ) ; 
                C . pop ( ) ; 
                B . push ( data ) ; 
            } 
        head = C . front ( ) ; 
        C . pop ( ) ; 
    } 
    return head ; 
}

    private : 
        queue < T > B ; 
        queue < T > C ; 
    } ;
