void exchange(int *node1, int *node2){//交換child and parent 
	int temp;
	temp=*node1;
	*node1=*node2;
	*node2=temp;	
	
}
void insertmaxheap(int node){//node=要插入的值
    static int last;
	last=-1; 
	int index=0;//節點索引值 
	heaptree[++last]=node;//last為陣列尾端 
	index=last;
	
	while(index>0){
		if(index%2==0&&heaptree[index]<=heaptree[(index-2)/2]){
			break;//如果是right child檢查有沒有大於parent,沒有就跳出 
		}
		if(index%2==1&&heaptree[index]<=heaptree[(index-1)/2]){
			break;//如果是left child檢查有沒有大於parent,沒有就跳出 
		}
		if(index==1){
			if(heaptree[1]>heaptree[0]){//如果1位置大於0位置(root)直接交換 
				exchange(&heaptrree[1],&heaptree[0]);
			}
		}
		else{//如果大於parent就交換 
			exchange(&heaptrree[index],&heaptree[(index-1)/2]);
			index=(index-1)/2;
		}
		
	} 
	
}
int main(){
	//讀入陣列做insertmaxheap 
}
