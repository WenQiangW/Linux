#pragma ocne
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


template<class T>
struct BlancedBinaryTreeNode
{
	BlancedBinaryTreeNode(T* data)
	: _data(data)
	, _bf(0)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	{
	}
	T* _data;
	int _bf; //Æ½ºâÒò×Ó
	BlancedBinaryTreeNode<T>* _pLeft;
	BlancedBinaryTreeNode<T>* _pRight;
	BlancedBinaryTreeNode<T>* _pParent;	
};

template<class T>
class BlancedBinaryTree
{
	
public:
	typedef BlancedBinaryTreeNode<T>* Node;
	BlancedBinaryTree()
		:_pRoot(NULL)
	{
	}
	bool Insert(const T data)
	{
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (data < _pRoot->_data)
		}
	}
private:
	BlancedBinaryTreeNode<T>* _pRoot;
};