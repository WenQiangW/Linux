

//开散列，哈希桶
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include"common.h"
using namespace std;

/*
//没有实现string
template<class K,class V>
struct HashNode
{
	HashNode(const K& key, const V& value)
		:_next(NULL)
		, _key(key)
		, _value(value)
	{}
	HashNode<K, V> *_next;
	K _key;
	V _value;
};

template<class K,class V>
class HashTableBucket
{
public:
	HashTableBucket(size_t capacity = 10)
		:_size(0)
	{
		capacity = GetNextPrim(capacity);
		_HashTable.resize(capacity);
		for (size_t idx = 0; idx < capacity; ++idx)
		{
			_HashTable[idx] = NULL;
		}
	}

	HashTableBucket(HashTableBucket<K, V>& ht);
	HashTableBucket<K, V>& operator=(HashTableBucket<K, V>& ht);

	bool Insert(const K&key, const V& value)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur && pCur->_key != key)
		{
			if (key == pCur->_key)
				return false;
			pCur = pCur->_next;
		}
		HashNode<K, V> *pHead = _HashTable[index];
		HashNode<K, V> *pNewNode = new HashNode<K, V>(key, value);
		pNewNode->_next = _HashTable[index];
		_HashTable[index] = pNewNode;
		++_size;
		return true;
	}
	bool Find(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur)
		{
			if (key == pCur->_key)
				return true;
			pCur = pCur->_next;
		}
		return false;
	}
	bool Remove(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		HashNode<K, V> *prev = pCur;
		while (NULL != pCur)
		{
			if (key == pCur->_key)
			{
				if (pCur == _HashTable[index]) //删除点为头
				{
					_HashTable[index] = prev->_next;
				}
				else
				{
					prev->_next = pCur->_next;
					delete pCur;
					--_size;
					return true;
				}				
			}
			prev = pCur;
			pCur = pCur->_next;
		}
		return false;
	}
	void Clear()
	{
		for (size_t idx = 0; idx < _HashTable.capacity(); ++idx)
		{
			
			if (_HashTable[idx] != NULL)
			{				
				while (_HashTable[idx])
				{
					HashNode<K, V>* pCur = _HashTable[idx];
					_HashTable[idx] = pCur->_next;
					delete pCur;
				}
			}
		}
		_size = 0;
	}
	~HashTableBucket()
	{
		Clear();
	}

private:
	void CheckCapacity()
	{
		if (_size == _HashTable.capacity()) //当插入的元素等于vector的容量,
		{
			HashTableBucket<K, V> temp(GetNextPrim(_size));
			for (int idx = 0; idx < _HashTable.size(); ++idx)
			{
				HashNode<K, V>* pCur = _HashTable[idx];
				HashNode<K, V>* pPre = NULL;
				while (pCur)
				{
					pPre = pCur;
					pCur = pCur->_next;
					//定位新的temp的桶
					size_t hashIdx = temp.HashFun(pPre->_key);
					//链接到temp._hashTable上
					pPre->_next = temp._HashTable[hashIdx];
					temp._HashTable[hashIdx] = pPre;
					temp._size++;
				}
				_HashTable[idx] = NULL;
			}
			std::swap(_HashTable, temp._HashTable);
		}
	}
	size_t HashFun(const K& key)
	{
		return key%_HashTable.capacity();
	}
private:
	vector<HashNode<K, V>*> _HashTable;
	size_t _size;
};
*/


/*
template<class K>
class HashFunDef
{
public:
	size_t operator()(const K& key)
	{
		return key;
	}
};

//string转化为数字
static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}


template<>
class HashFunDef<string>
{
public:
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
*/

//实现string
template<class K, class V>
struct HashNode
{
	HashNode(const K& key, const V& value)
	:_next(NULL)
	, _kv(key, value)
	{}
	HashNode<K, V> *_next;
	pair<K, V> _kv;
};

template<class K, class V, class HashFunc = HashFunDef<K>>
class HashTableBucket
{
public:
	HashTableBucket(size_t capacity = 10)
		:_size(0)
	{
		capacity = GetNextPrim(capacity);
		_HashTable.resize(capacity);
		for (size_t idx = 0; idx < capacity; ++idx)
		{
			_HashTable[idx] = NULL;
		}
	}

	/*HashTableBucket(HashTableBucket<K, V>& ht);
	HashTableBucket<K, V>& operator=(HashTableBucket<K, V>& ht);*/

	bool Insert(const pair<K, V>& kv)
	{
		CheckCapacity();
		size_t index = HashFun(kv.first);
		HashNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur && pCur->_kv.first != kv.first)
		{
			if (pCur->_kv.first == kv.first)
				return false;
			pCur = pCur->_next;
		}
		HashNode<K, V> *pHead = _HashTable[index];
		HashNode<K, V> *pNewNode = new HashNode<K, V>(kv.first, kv.second);
		pNewNode->_next = _HashTable[index];
		_HashTable[index] = pNewNode;
		++_size;

		return true;
	}
	bool Find(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur)
		{
			if (pCur->_kv.first == key)
				return true;
			pCur = pCur->_next;
		}
		return false;
	}
	bool Remove(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		HashNode<K, V> *prev = pCur;
		while (NULL != pCur)
		{
			if (pCur->_kv.first == key)
			{
				if (pCur == _HashTable[index]) //删除点为头
				{
					_HashTable[index] = prev->_next;
				}
				else
				{
					prev->_next = pCur->_next;
					delete pCur;
					--_size;
					return true;
				}
			}
			prev = pCur;
			pCur = pCur->_next;
		}
		return false;
	}
	void Clear()
	{
		for (size_t idx = 0; idx < _HashTable.size(); ++idx) //vector的size == capacity
		{
			while (_HashTable[idx])
			{
				HashNode<K, V>* pDel = _HashTable[idx];
				_HashTable[idx] = pDel->_next;
				delete pDel;
			}
		}
		_size = 0;
	}
	~HashTableBucket()
	{
		Clear();
	}
	//[]操作符 返回键值对
	V& operator[](const K& key)
	{
		size_t idx = HashFun(key);
		HashNode<K, V>* pCur = _HashTable[idx];
		while (pCur)
		{
			if (pCur->_kv.first = key)
				return pCur->_kv.second;
			pCur = pCur->_next;
		}
		//跳出循环 表示没找到，可以抛出异常，
		throw::exception("ket not find");
	}
private:
	void CheckCapacity()
	{
		if (_size == _HashTable.capacity()) //当插入的元素等于vector的容量,
		{
			HashTableBucket<K, V> temp(GetNextPrim(_size));
			for (size_t idx = 0; idx < _HashTable.size(); ++idx)
			{
				HashNode<K, V>* pCur = _HashTable[idx];
				HashNode<K, V>* pPre = NULL;
				while (pCur)
				{
					pPre = pCur;
					pCur = pCur->_next;
					//定位新的temp的桶
					size_t hashIdx = temp.HashFun(pPre->_kv.first);
					//链接到temp._hashTable上
					pPre->_next = temp._HashTable[hashIdx];
					temp._HashTable[hashIdx] = pPre;
					temp._size++;
				}
				_HashTable[idx] = NULL;
			}
			_HashTable.swap(temp._HashTable);
			
		}
	}
	size_t HashFun(const K& key)
	{
		return HashFunc()(key)%_HashTable.size();
	}
private:
	vector<HashNode<K, V>*> _HashTable;
	size_t _size;
};

void Test3()
{
	HashTableBucket<int, int> ht;
	HashTableBucket<string, string> ht1;
	ht1.Insert(make_pair("11", "11"));
	ht1.Insert(make_pair("22", "22"));
	ht1.Insert(make_pair("33", "33"));
	ht1.Insert(make_pair("44", "44"));

	int ret = ht1.Find("22");
}
