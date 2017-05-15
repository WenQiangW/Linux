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
	int _bf; //ƽ������:�������ĸ߶�-�������ĸ߶�
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
		//�ҵ�����ڵ㣬
		pCur = new Node(data);
		pCur->_pParent = pParent;
		if (data > pParent->_data)
			pParent->_pRight = pCur;
		else
			pParent->_pLeft = pCur;

		//����ƽ������
		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;			
			else
				pParent->_bf++;
			//ƽ�����Ӹı�
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
		//����ѭ�� pParent�����ӿ���Ϊ2 ���� -2 �������ת
		//��ת
		//����pParentΪ�գ�����Ҫ������ת
		if (pParent)
		{
			if (pParent->_bf == 2)
			{
				if (pCur->_bf == 1)//��������
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
	//����������������ң�pParent
	/*	 �� �� �� ��������
		(1)	    20  pParent			30		    (2)   20                (3) SubRLΪ��       
			   /  \				   /  \				 /  \						20     
		     15   30 SubR		 20	  40	        15   30                       \                                
		         /  \			/  \	\			    /  \                       30 
		   SubRL25   40		   15	25	45			   25   40                      \
					 \									    /					    25 ����							
					 45 �����Ľڵ�						  35                    
	*/
	void _RotateL(Node* pParent) //����
	{
		Node* SubR = pParent->_pRight; //��ǰ�ڵ�pParent������
		Node* SubRL = SubR->_pLeft; //����Ϊ��
		//�Ƚ� SubRL ���ӵ�
		pParent->_pRight = SubRL;
		if (SubRL) //���������
		{
			SubRL->_pParent = pParent;
		}
		//�޸�SubR
		Node *pPparent = pParent->_pParent;  //pParent����Ϊ���ڵ�
		SubR->_pParent = pPparent; //�޸�SubR�ĸ��ڵ�
		//��SubR���ӵ�ԭ������
		if (pPparent == NULL)//����Ϊ���ڵ�
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

		//�޸�pParent,
		SubR->_pLeft = pParent;
		pParent->_pParent = SubR;

		//����SubR��pParent��ƽ������
		SubR->_bf = pParent->_bf = 0;
	}

	//��������������� �� ��������
	/*	(1)	    50  pParent			15		    (2)   50           (3) SubRLΪ��            
		       /  \				   /  \				 /  \					 50            
		 	  40   60    		 20	   40	        40   60                 /                    
	         /  \			    /  \	 \		   /  \                    40                    
	       30   45		      15	25	 45	      30  45                   /                      
	       /									   \				      25 ����                 
������	  20                   					   35
	*/
	void _RotateR(Node* pParent) //����
	{
		Node* SubL = pParent->_pLeft;
		Node* SubLR = SubL->_pRight; //����Ϊ���������

		//�޸�SubLR
		pParent->_pLeft = SubLR;
		if (SubLR)
		{
			SubLR->_pParent = pParent;
		}
		//�޸�subL
		Node* pPparent = pParent->_pParent;
		SubL->_pParent = pPparent;
		//subL���ӵ�ԭ������
		if (pPparent == NULL)
			_pRoot = SubL;
		else
		{
			if (pPparent->_pLeft == pParent)
				pPparent->_pLeft = SubL;
			else
				pPparent->_pRight = SubL;
		}
		//�޸�pparent
		SubL->_pRight = pParent;
		pParent->_pParent = SubL;

		//����subl��pparent��ƽ������
		SubL->_bf = pParent->_bf = 0;
	}
	//����������������� �� ����������
	/*	(1)	    50  pParent			45		    (2)    50           (3) SubRLΪ��
		       /  \				   /  \				  /  \					 50
		 SubL40   60    		 40	   50	         40   60                 /
	        /  \			    /  \	 \		    /  \                    40
	      30   45		      30   44	 60        30  45                   \
				/									    \				    45 ����
	������	   44                   				    46
	*/
	void _RotateLR(Node* pParent) //������ ������
	{
		//���� subLR��ƽ�����ӣ�
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

	//��������������� 
	/*	 �� �� �� ����������
	(1)	    20  pParent			25		     (2)       20                (3) SubRLΪ��
		   /  \				   /  \				      /  \						20
	      15   30 		      20   30	            15   30                       \
      	      /  \			 /     / \			        /  \                       30
	         25   40		15	  26  40		       25  40                      /
       	      \									       /					      25 ����
	         26 �����Ľڵ�						     24
	*/
	void _RotateRL(Node* pParent) //������ת
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
			cout << Root->_data << ": " << "ƽ�����ӳ���" << endl;
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