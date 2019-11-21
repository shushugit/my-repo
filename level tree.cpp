#include <iostream>
#include <sstream>
#include <queue>


class BinaryTree;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    char data;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),data('x'){};
    TreeNode(char s):leftchild(0),rightchild(0),parent(0),data(s){};

    friend class BinaryTree;
};

class BinaryTree{
private:
    TreeNode *root;
public:
    BinaryTree():root(0){};
    BinaryTree(const char* str);

    void LevelorderConstruct(std::stringstream &ss);
    void InsertLevelorder(char data);

    TreeNode* leftmost(TreeNode *current);
    TreeNode* InorderSuccessor(TreeNode *current);
    void Inorder_by_parent();
};

BinaryTree::BinaryTree(const char* str){
    std::stringstream  ss;
    ss << str;                     // magic!
    
    root = new TreeNode;           // allocate memory for root
    ss >> root->data;              // assign character to root
    
    LevelorderConstruct(ss);
}

void BinaryTree::LevelorderConstruct(std::stringstream &ss){
    
    std::queue<TreeNode*> q;         // create a queue to handle level-roder rule
    TreeNode *current = root;        // point *current to root
    char data = 'x';                 // initializa data as 'x'
    
    while (ss >> data) {
        if (data >= 65 && data <= 90){                // �B�zcurrent��leftchild
            TreeNode *new_node = new TreeNode(data);  // call constructor TreeNode(char s)
            new_node->parent = current;
            current->leftchild = new_node;
            q.push(new_node);
        }
        if (!(ss >> data)){                           // ���i��char array�t���_�Ƶ����
            break;                                    // �ҥH�b�o�̵����j��
        }
        if (data >= 65 && data <= 90){                // �B�zcurrent��rightchild
            TreeNode *new_node = new TreeNode;        // call constructor TreeNode()
            new_node->parent = current;
            current->rightchild = new_node;
            new_node->data = data;                    // assign data to new_node
            q.push(new_node);
        }
        current = q.front();                          // �qqueue����scurrent
        q.pop();                                      // ��squeue
    }
}

void BinaryTree::InsertLevelorder(char data){    

    std::queue<TreeNode*> q;
    TreeNode *current = root;
    
    while (current) {
        if (current->leftchild != NULL){               // current��leftchild�S���Ŧ�
            q.push(current->leftchild);                // �N����iqueue��
        }
        else{                                          // current��leftchild���Ŧ�
            TreeNode *new_node = new TreeNode(data);   // �إ߷s��node, �N�r����b�o��
            new_node->parent = current;
            current->leftchild = new_node;
            break;                         
        }
        if (current->rightchild != NULL) {             // current��rightchild�S���Ŧ�
            q.push(current->rightchild);               // �N����iqueue��
        }
        else{                                          // current��rightchild���Ŧ�
            TreeNode *new_node = new TreeNode(data);   // �إ߷s��node, �N�r����b�o��
            new_node->parent = current;                
            current->rightchild = new_node;
            break;
        }
        current = q.front();
        q.pop();
    }
}
TreeNode* BinaryTree::leftmost(TreeNode *current){
    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}
TreeNode* BinaryTree::InorderSuccessor(TreeNode *current){
    if (current->rightchild != NULL){
        return leftmost(current->rightchild);
    }
    
    // �Q�Ψ��pointer: successor�Pcurrent��traversal 
    TreeNode *successor = current->parent;   
    while (successor != NULL && current == successor->rightchild) {
        current = successor;
        successor = successor->parent;
    }
    return successor;
}
void BinaryTree::Inorder_by_parent(){
    TreeNode *current = new TreeNode;
    current = leftmost(root);

    while(current){
        std::cout << current->data << " ";
        current = InorderSuccessor(current);
    }
}
int main() {
	
	int i,n,a;
	node*root=NULL;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
	}
	while(cin>>data){
		
	}
	
    const char *a = "A B C D E F x x x G H x I";
    BinaryTree T(a);
    T.Inorder_by_parent();
    std::cout << std::endl;

    T.InsertLevelorder('K');
    T.InsertLevelorder('L');
    T.InsertLevelorder('M');
    T.InsertLevelorder('N');
    T.Inorder_by_parent();
    std::cout << std::endl;

    return 0;
}
