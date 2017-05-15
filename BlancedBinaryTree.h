#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

template<class T>
struct BlancedBianryTreeNode
{
	BlancedBianryTreeNode(T data)
	: _data(data)
	, _bf(0)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	{}
	T _data;
	int _bf; //平衡因子:右子树的高度-左子树的高度
	BlancedBianryTreeNode<T>* _pLeft;
	BlancedBianryTreeNode<T>* _pRight;
	BlancedBianryTreeNode<T>* _pParent;
};

template<class T>
class BlancedBianryTree
{
	typedef BlancedBianryTreeNode<T> Node;
public:
	BlancedBianryTree()
		:_pRoot(NULL)
	{
	}
	bool Insert(T data)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(data);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (data > pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}
		//找到插入节点，
		pCur = new Node(data);
		pCur->_pParent = pParent;
		if (data > pParent->_data)
			pParent->_pRight = pCur;
		else
			pParent->_pLeft = pCur;

		//更新平衡因子
		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;			
			else
				pParent->_bf++;
			//平衡因子改变
			if (pParent->_bf == 0)
				return true;
			else if (pParent->_bf <-1 || pParent->_bf > 1)
				break;
			else
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}			
		}
		//跳出循环 pParent的因子可能为2 或者 -2 则进行旋转
		//旋转
		//可能pParent为空，不需要进行旋转
		if (pParent)
		{
			if (pParent->_bf == 2)
			{
				if (pCur->_bf == 1)//进行左旋
					_RotateL(pParent);
				else
					_RotateRL(pParent);
			}
			else if (pParent->_bf == -2)
			{
				if (pCur->_bf == -1)
					_RotateR(pParent);
				else
					_RotateLR(pParent);
			}
		}	
		return true;
	}

	void Inorder()
	{
		_Inorder(_pRoot);
		cout << endl;
	}


	int Height()
	{
		return _Height(_pRoot);
	}
	bool IsBlanced()
	{
		return _isBlanced(_pRoot);
	}
private:
	//左旋三种情况：右右：pParent
	/*	 当 正 正 进行左旋
		(1)	    20  pParent			30		    (2)   20                (3) SubRL为空       
			   /  \				   /  \				 /  \						20     
		     15   30 SubR		 20	  40	        15   30                       \                                
		         /  \			/  \	\			    /  \                       30 
		   SubRL25   40		   15	25	45			   25   40                      \
					 \									    /					    25 新增							
					 45 新增的节点						  35                    
	*/
	void _RotateL(Node* pParent) //左旋
	{
		Node* SubR = pParent->_pRight; //当前节点pParent的左孩子
		Node* SubRL = SubR->_pLeft; //可能为空
		//先将 SubRL 链接到
		pParent->_pRight = SubRL;
		if (SubRL) //第三种情况
		{
			SubRL->_pParent = pParent;
		}
		//修改SubR
		Node *pPparent = pParent->_pParent;  //pParent可能为根节点
		SubR->_pParent = pPparent; //修改SubR的父节点
		//把SubR链接到原子树上
		if (pPparent == NULL)//可能为根节点
		{
			_pRoot = SubR;
		}
		else
		{
			if (pParent == pPparent->_pLeft) 
				pPparent->_pLeft = SubR;
			else
				pPparent->_pRight = SubR;
		}

		//修改pParent,
		SubR->_pLeft = pParent;
		pParent->_pParent = SubR;

		//更新SubR和pParent的平衡因子
		SubR->_bf = pParent->_bf = 0;
	}

	//右旋三种情况：负 负 进行右旋
	/*	(1)	    50  pParent			15		    (2)   50           (3) SubRL为空            
		       /  \				   /  \				 /  \					 50            
		 	  40   60    		 20	   40	        40   60                 /                    
	         /  \			    /  \	 \		   /  \                    40                    
	       30   45		      15	25	 45	      30  45                   /                      
	       /									   \				      25 新增                 
新增：	  20                   					   35
	*/
	void _RotateR(Node* pParent) //右旋
	{
		Node* SubL = pParent->_pLeft;
		Node* SubLR = SubL->_pRight; //可能为第三种情况

		//修改SubLR
		pParent->_pLeft = SubLR;
		if (SubLR)
		{
			SubLR->_pParent = pParent;
		}
		//修改subL
		Node* pPparent = pParent->_pParent;
		SubL->_pParent = pPparent;
		//subL链接到原子树上
		if (pPparent == NULL)
			_pRoot = SubL;
		else
		{
			if (pPparent->_pLeft == pParent)
				pPparent->_pLeft = SubL;
			else
				pPparent->_pRight = SubL;
		}
		//修改pparent
		SubL->_pRight = pParent;
		pParent->_pParent = SubL;

		//更新subl和pparent的平衡因子
		SubL->_bf = pParent->_bf = 0;
	}
	//左右旋三种情况：负 正 进行左右旋
	/*	(1)	    50  pParent			45		    (2)    50           (3) SubRL为空
		       /  \				   /  \				  /  \					 50
		 SubL40   60    		 40	   50	         40   60                 /
	        /  \			    /  \	 \		    /  \                    40
	      30   45		      30   44	 60        30  45                   \
				/									    \				    45 新增
	新增：	   44                   				    46
	*/
	void _RotateLR(Node* pParent) //左右旋 分三种
	{
		//根据 subLR的平衡因子：
		int bs = pParent->_pLeft->_pRight->_bf;
		Node* SubL = pParent->_pLeft;
		_RotateL(pParent->_pLeft);
		_RotateR(pParent);
		if (bs == 1)
		{
			pParent->_bf = 0;
			SubL->_bf = -1;
		}
		else if (bs == -1)
		{
			pParent->_bf = 1;
			SubL->_bf = 0;
		}

	}

	//右左旋三种情况： 
	/*	 当 正 负 进行右左旋
	(1)	    20  pParent			25		     (2)       20                (3) SubRL为空
		   /  \				   /  \				      /  \						20
	      15   30 		      20   30	            15   30                       \
      	      /  \			 /     / \			        /  \                       30
	         25   40		15	  26  40		       25  40                      /
       	      \									       /					      25 新增
	         26 新增的节点						     24
	*/
	void _RotateRL(Node* pParent) //右左旋转
	{
		int bs = pParent->_pRight->_pLeft->_bf;
		Node* SubR = pParent->_pRight;
		_RotateR(pParent->_pRight);
		_RotateL(pParent);
		if (bs == 1)
		{
			pParent->_bf = -1;
			SubR->_bf = 0;
		}
		else if (bs == -1)
		{
			pParent->_bf = 0;
			SubR->_bf = 1;
		}
	}

	void _Inorder(Node* Root)
	{
		if (Root)
		{
			_Inorder(Root->_pLeft);
			cout << Root->_data << " ";
			_Inorder(Root->_pRight);
		}
	}

	int _Height(Node* Root)
	{
		if (Root == NULL)
			return 0;
		int left = _Height(Root->_pLeft);
		int right = _Height(Root->_pRight);
		return ((left > right) ? left+1 : right+1);
	}
	bool _isBlanced(Node* Root)
	{
		if (Root = NULL)
			return true;
		int left = _Height(Root->_pLeft);
		int right = _Height(Root->_pRight);
		if (((right - left) != Root->_bf) || abs(Root->_bf) > 1)
		{
			cout << Root->_data << ": " << "平衡因子出错" << endl;
			return false;
		}
		return _isBlanced(Root->_pLeft) && _isBlanced(Root->_pRight);
	}
private:
	Node* _pRoot;
};

void TestRotateL()
{
	//int arr[] = { 20, 15, 30, 25, 40, 45 };
	int arr[] = { 20, 15, 30, 25, 40, 35 };
	//int arr[] = { 20, 30, 35 };
	BlancedBianryTree<int> bbt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		bbt.Insert(arr[i]);

	bbt.Inorder();
	int height = bbt.Height();
}

void TestRotateLR()
{
	//int arr[] = { 50, 40, 60, 30, 45, 44 };
	//int arr[] = { 50, 40, 60, 30, 45, 46 };
	int arr[] = { 50, 40, 45 };
	BlancedBianryTree<int> bbt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		bbt.Insert(arr[i]);

	bbt.Inorder();
	int height = bbt.Height();
}

void Test()
{
	int arr[] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };
	BlancedBianryTree<int> bbt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		bbt.Insert(arr[i]);

	bbt.Inorder();
	int height = bbt.Height();
}