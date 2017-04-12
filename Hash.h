#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


//线性探测
enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template<class T>
class HashTable
{
public:
	HashTable(size_t capacity = 10)
		:_capacity(capacity)
		, _size(0)
	{
		_hashTable = new T[_capacity];
		_state = new State[_capacity];
		memset(_state, EMPTY, sizeof(_state)*_capacity);
	}
	bool Insert(const T& key)
		// 首先判断是否为满了可以插入
		// 再判断是否存在：是否为key值
		//如果为key值的话，返回true 
		//如果不为key值的话，接着向后查找：直到遇到为空的位置或者删除 然后直接插入
	{
		if (_size >= _capacity)
			return false;
		size_t index = HashFuncation(key);
		while (_state[index] == EXIST)
		{
			if (_hashTable[index] == key)
				return true;

			index++;
			index %= _capacity;
		}
		_state[index] = EXIST;
		_hashTable[index] = key;
		_size++;
		return true;
	}
	bool Find(const T& key, size_t& hashIdx)
		//hashIdx相当于作为返回值返回
	{
		size_t index = HashFuncation(key);
		size_t startIdx = index;//标记起始位置，防止找一圈，陷入死循环
		while (_state[index] != EMPTY)
			//这里循环条件不能是 判断是否存在，因为还有delete状态，如果遇到delete就跳出循环，delete后面的元素就没查找
		{
			if (_hashTable[index] == key && _state[index] == EXIST)
			{
				hashIdx = index;
				return true;
			}
			index++;
			index %= _capacity;
			if (index == startIdx) //找了一圈了
				break;
		}
		return false;
	}
	bool Remove(const T& key)
		//查找当前index是否为key值，如果不是向后查找
	{
		size_t index = 0;
		if (Find(key, index))
		{
			_state[index] = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	~HashTable()
	{
		if (_hashTable)
		{
			delete[] _hashTable;
			_hashTable = NULL;
		}
		if (_state)
		{
			delete[] _state;
			_state = NULL;
		}
	}
private:
	int HashFuncation(const T& key)
	{
		return key % 10;
	}
private:
	T* _hashTable;
	State * _state;
	size_t _capacity;
	size_t _size;
};

void TestHash()
{
	HashTable<int> ht;
	size_t index = 0;
	ht.Insert(10);
	ht.Insert(20);
	ht.Insert(30);
	ht.Insert(40);
	ht.Insert(50);
	ht.Insert(60);
	ht.Insert(70);
	ht.Insert(80);
	ht.Insert(90);
	ht.Insert(9);
	ht.Remove(20);
	ht.Insert(3);
	ht.Find(3, index);
	bool res = ht.Insert(20);
}