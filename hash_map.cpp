#include <iostream>

using namespace std;

typedef struct HashNode
{
	int val;
	struct HashNode* next;
}HashNode;

class hash_map 
{
public:
	hash_map();
	hash_map(const int&_key);
	void insert(const int& _val); /*插入*/
	bool find(const int& _val); /*查找*/
	bool del_value(const int& _val); /*删除值*/
	bool empty(); /* 是否为空表*/
	int size(); /*返回插入元素的数量*/
	void clear(); /* 清空表*/
	void print(); /*打印表*/
	~hash_map();

private:
	HashNode* buffer;
	int _size;
	int key;

};

hash_map::hash_map()
{
	key = 13;
	_size = 0;
	buffer = new HashNode[key];
	for (int i = 0; i < key; i++)
	{
		buffer[i].next = nullptr;
	}
}

hash_map::hash_map(const int& _key) : key(_key), _size(0)
{
	buffer = new HashNode[key];
	for (int i = 0; i < key; i++)
	{
		buffer[i].next = nullptr;
	}
}

void hash_map::insert(const int& _val)
{
	HashNode* newnode = new HashNode;
	newnode->val = _val;
	newnode->next = nullptr;
	HashNode *cur = buffer[newnode->val % key].next;
	buffer[newnode->val % key].next = newnode;
	newnode->next = cur;
	_size++;
}

bool hash_map::find(const int& _val)
{
	int idx = _val % key;
	HashNode* cur = buffer[idx].next;
	while (cur)
	{
		if (cur->val == _val) return true;
		cur = cur->next;
	}
	return false;
}

bool hash_map::del_value(const int& _val)
{
	int idx = _val % key;
	HashNode* cur = &buffer[idx];
	while (cur)
	{
		if (cur->next && cur->next->val == _val)
		{ HashNode* t = cur->next; cur->next = t->next; delete t; _size--;
		}
		else cur = cur->next;
	}
	return true;
}

bool hash_map::empty()
{
	return _size == 0;
}

int hash_map::size()
{
	return _size;
}

void hash_map::clear()
{
	for (int i = 0; i < key; i++)
	{
		HashNode* cur = buffer[i].next;
		while (cur)
		{ HashNode* t = cur->next; buffer[i].next = t; delete cur; cur = t;
		}
	}
	_size = 0;
}

void hash_map::print()
{
	for (int i = 0; i < key; i++)
	{
		cout << "[" << i << "]:->";
		HashNode* cur = buffer[i].next;
		while (cur)
		{ cout << cur->val; cur = cur->next; if (cur) cout << "->";
		}
		cout << endl;
	}
}

hash_map::~hash_map()
{
	clear();
	delete[]buffer;
} 

int main()
{
	hash_map mymap(13);
	for (int i = 0; i < 39; i++)
		mymap.insert(i);
	mymap.print();
	cout << "size = " << mymap.size() << endl;
	cout << "find(10):"<< (bool)mymap.find(10) << endl;

    return 0;
}