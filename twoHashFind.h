
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include"common.h"
using namespace std;

//二次探测
enum State
{
	EMPTY,
	EXIST,
	DELETE,
};

//template<class K>
//class HashFunDef
//{
//public:
//	size_t operator()(const K& key)
//	{
//		return key;
//	}
//};
//
//static size_t BKDRHash(const char * str) //字符串转成整数
//{
//	unsigned int seed = 131; // 31 131 1313 13131 131313
//	unsigned int hash = 0;
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
//	return (hash & 0x7FFFFFFF);
//}
//
////特例化
//template<>
//class HashFunDef<string>
//{
//public:
//	size_t operator()(const string& key)
//	{
//		return BKDRHash(key.c_str());
//	}
//};


template<class K, class V, class Fun = HashFunDef<K>>
class HashTable
{
public:
	// 动态--质数
	HashTable(size_t capacity = 10)
		: _capacity(capacity)
		, _size(0)
	{
		_capacity = GetNextPrim(_capacity);
		_hashTable = new pair<K, V>[_capacity];
		_state = new State[_capacity];
		memset(_state, EMPTY, sizeof(State)*_capacity);
	}

	HashTable(HashTable<K, V>& ht)
		: _hashTable(NULL)
		, _state(NULL)
	{
		HashTable<K, V> temp(ht._capacity);
		for (size_t index = 0; index < ht._capacity; ++index)
		{
			if (EXIST == ht._state[index])
				temp.Insert(ht._hashTable[index].first, ht._hashTable[index].second);

		}

		Swap(temp);
	}

	~HashTable()
	{
		if (_hashTable)
			delete[] _hashTable;

		if (_state)
			delete[] _state;
	}

	bool Insert(const K& key, const V& value)
	{
		CheckCapacity();
		// 找插入位置
		size_t hashIdx = HashFun1(key);
		size_t i = 1;
		while (_state[hashIdx] == EXIST)// 
		{
			if (_hashTable[hashIdx].first == key)
				return false;

			hashIdx = HashFun2(hashIdx, i++);
		}

		// EMPTY DELETE
		_state[hashIdx] = EXIST;
		_hashTable[hashIdx] = pair<K, V>(key, value);
		_size++;
		return true;
	}

	// 元素存在-->
	// 不存在--> DELETE
	bool Find(const K& key, size_t& index)
	{
		size_t Hashinx = HashFun1(key);
		index = Hashinx;

		size_t i = 1;
		while (_state[index] != EMPTY)//DETE 存在
		{
			// 存在
			if (_state[index] == EXIST&& _hashTable[index].first == key)
				return true;

			index = HashFun2(index, i++);
		}

		return false;
	}


	bool Remove(const K& key)
	{
		size_t index = 0;
		if (Find(key, index))
		{
			_state[index] = DELETE;
			--_size;
			return true;
		}

		return false;
	}

	void Print()
	{
		for (size_t idx = 0; idx < _capacity; ++idx)
		{
			if (_state[idx] != EMPTY)
			{
				cout << "_tables[";
				cout << _hashTable[idx].first;
				cout << "]-->_state[" << _state[idx] << "]" << endl;
			}
		}
	}

private:

	int HashFun1(const K& key)
	{
		return Fun()(key) % _capacity;
		//return key%_capacity;//10 11 质数  a>=0.6
	}

	// hash(i) = hash(0) + i^2; 
	// hash(i-1) = hash(0) +(i-1)^2;  两个相减 hash(i) = hash(i-1) +2*i-1;
	int HashFun2(size_t prevHashIdx, size_t i)
	{
		return (prevHashIdx + (i << 1) - 1) % _capacity;
	}

	void CheckCapacity()
	{
		// 0.7~0.8
		size_t capacity;
		if (_size / _capacity >= 0.7)
		{
			capacity = GetNextPrim(_capacity);

			HashTable<K, V> ht(capacity);
			for (size_t index = 0; index < _capacity; ++index)
			{
				if (EXIST == _state[index])
					ht.Insert(_hashTable[index].first, _hashTable[index].second);

			}

			Swap(ht);
		}
	}

	void Swap(HashTable<K, V>& ht)
	{
		std::swap(_hashTable, ht._hashTable);
		std::swap(_state, ht._state);
		std::swap(_capacity, ht._capacity);
		std::swap(_size, ht._size);
	}

	

private:
	pair<K, V>* _hashTable;
	State* _state;
	size_t _capacity;
	size_t _size;
};

void Test()
{
	HashTable<int, int> ht;
	ht.Insert(10, 10);
	ht.Insert(21, 20);
	ht.Insert(32, 30);
	ht.Insert(43, 10);
	ht.Insert(54, 20);
	ht.Insert(65, 30);
	ht.Insert(46, 10);
	ht.Insert(57, 20);
	ht.Insert(8, 8);
	ht.Insert(9, 10);

	ht.Remove(32);
	ht.Remove(43);
	ht.Remove(54);
	ht.Remove(8);

	ht.Print();
	cout << endl;
	HashTable<int, int> ht1(ht);
	ht1.Print();

	size_t idx = 0;
	bool ret = ht.Find(30, idx);
	ret = ht.Find(8, idx);
	ret = ht.Find(4, idx);

	ret = ht.Find(20, idx);

}

void Test2()
{
	HashTable<string, string, HashFunDef<string>> ht;
	ht.Insert("hash", "s");
	ht.Insert("ss", "hash");
	ht.Print();

	size_t idx = 0;
	ht.Find("hash", idx);
}