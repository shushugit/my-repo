#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int main(){
	
	 int i,j;
	 int col,row;
	 cin>>col>>row;
    
	char**matrix;
    matrix = new char*[col];
    for(i = 0; i < col; i++){
	   matrix[i] = new char[row];
}
    for(i=0;i < col; i++){
        for(j=0;j < row; j++){
        	
        	cin>>matrix[i][j];
        }    
    }
    for(i=0;i < col; i++){//test
        for(j=0;j < row; j++){
        	cout<<matrix[i][j];
        	
        }
		cout<<endl;    
}
		int k;
      k=matrix[0][1]-48+matrix[0][0]-48;
      cout<<k;
      cout<<matrix[0][1]<<matrix[0][0];
      
      
}
