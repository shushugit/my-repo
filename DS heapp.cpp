void exchange(int *node1, int *node2){//�洫child and parent 
	int temp;
	temp=*node1;
	*node1=*node2;
	*node2=temp;	
	
}
void insertmaxheap(int node){//node=�n���J����
    static int last;
	last=-1; 
	int index=0;//�`�I���ޭ� 
	heaptree[++last]=node;//last���}�C���� 
	index=last;
	
	while(index>0){
		if(index%2==0&&heaptree[index]<=heaptree[(index-2)/2]){
			break;//�p�G�Oright child�ˬd���S���j��parent,�S���N���X 
		}
		if(index%2==1&&heaptree[index]<=heaptree[(index-1)/2]){
			break;//�p�G�Oleft child�ˬd���S���j��parent,�S���N���X 
		}
		if(index==1){
			if(heaptree[1]>heaptree[0]){//�p�G1��m�j��0��m(root)�����洫 
				exchange(&heaptrree[1],&heaptree[0]);
			}
		}
		else{//�p�G�j��parent�N�洫 
			exchange(&heaptrree[index],&heaptree[(index-1)/2]);
			index=(index-1)/2;
		}
		
	} 
	
}
int main(){
	//Ū�J�}�C��insertmaxheap 
}
