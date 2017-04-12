#pragma once

#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap()
	{}
	BitMap(size_t size)
	{
		_table.resize((size >> 5) + 1);
	}
	void Set(int data)
	{
		size_t ByteNo = data >> 5; //相当于除以32
		size_t BitNo = data % 32;
		_table[ByteNo] |= (1 << BitNo); //置1
	}
	void ReSet(int data)
	{
		size_t ByteNo = data >> 5; //相当于除以32
		size_t BitNo = data % 32;
		_table[ByteNo] &= ~(1 << BitNo); //置0
	}
	bool Test(int data)
	{
		size_t ByteNo = data >> 5; //相当于除以32
		size_t BitNo = data % 32;
		if (_table[ByteNo] & (1 << BitNo))
			return true;
		return false;
	}
private:
	vector<int> _table;
};

void Test()
{
	BitMap bm(100);
	bm.Set(1);
	bm.Set(20);
	bm.Set(30);
	bm.Set(40);
	bm.Set(55);
	bm.Set(65);
	bm.Set(89);

	if (bm.Test(65))
	{
		cout << "65 In" << endl;
	}

	if (bm.Test(66))
	{
		cout << "55 In" << endl;
	}
	else
	{
		cout << "55 is Not" << endl;
	}
}