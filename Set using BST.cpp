#include<iostream>
using namespace std;
struct bst
{
	int data;
	bst *left,*right;	
};
bst* getNode()
{
	bst *newNode=new bst;
	newNode->left=newNode->right=NULL;
	return newNode;	
}
bst* insert(bst *root,int data)
{
	if(!root)
	{
		root=getNode();
		root->data=data;
	}
	if(root->data!=data)
	{
		if(root->data>data)
			root->left=insert(root->left,data);
		else 
			root->right=insert(root->right,data);
	}
	return root;
}
void preorder(bst *root)
{
	if(!root)
		return;
	preorder(root->left);
	cout<<root->data<<" ";
	preorder(root->right);
}
bst *input(bst *set,int n1)
{
	cout<<"\n\n Enter the elements one by one:\t";
	for(int i=0;i<n1;i++)
	{
		int temp;
		cin>>temp;
		set=insert(set,temp);
	}
	return set;
}
void transfer(bst **unionRoot,bst *root)
{
	if(!root)
		return;
	*unionRoot=insert(*unionRoot,root->data);
	transfer(unionRoot,root->left);
	transfer(unionRoot,root->right);
	
}
void myUnion(bst *set1,bst *set2)
{
	bst *unionRoot=NULL;
	transfer(&unionRoot,set1);
	transfer(&unionRoot,set2);
	preorder(unionRoot);
}
bool search(bst *root,int data)
{
	if(!root)
		return 0;
	if(root->data==data)
		return 1;
	return search(root->left,data) || search(root->right,data);
}
void intersect(bst *set1,bst* set2)
{
	if(!set2)
		return;
	bool exist=search(set1,set2->data);
	if(exist)
		cout<<set2->data<<" ";
	intersect(set1,set2->left);
	intersect(set1,set2->right);
}
bst* inorderSuccessor(bst *root)
{
	while(!root->left)
	{
		root=root->left;
	}
	return root;
}
bst* deleteNode(bst *root,int data)
{
	if(!root)
		return NULL;
	if(root->data==data)
	{
		if(!root->left)
			return root->right;
		if(!root->right) 
			return root->left;
		bst *temp=inorderSuccessor(root->right);	
		root->data=temp->data;
		root->right=deleteNode(root->right,temp->data);
	}
	else if(root->data>data)
		root->left=deleteNode(root->left,data);
	else
		root->right=deleteNode(root->right,data);
	return root;
}
void subtract(bst **set1,bst *set2)
{
	if(!set2)
		return;
	*set1=deleteNode(*set1,set2->data);
	subtract(set1,set2->left);
	subtract(set1,set2->right);		
}
int main()
{
	bst *set1=NULL,*set2=NULL;
	cout<<"\n\n Enter the number of elements in set 1:\t";
	int n1;
	cin>>n1;
	set1=input(set1,n1);
	cout<<"\n\n Enter the number of elements in set2:\t";
	int n2;
	cin>>n2;
	set2=input(set2,n2);
	cout<<"\n\n The union is :\t";
	myUnion(set1,set2);
	cout<<"\n\n The Intersection is:\t";
	intersect(set1,set2);
	cout<<"\n\n\ The A-B is :\t";
	subtract(&set1,set2);
	//set1=deleteNode(set1,10);
	preorder(set1);
	return 0;
}
