#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct DLinkedNode {
    int key;
    int val;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _val) : key(_key), val(_val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity; // LRUCache的容量
    int size;  // 链表大小
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode *head; // 伪头部
    DLinkedNode *tail; // 伪尾部
    void addToHead(DLinkedNode *node) {
        head->next->prev = node;
        node->next = head->next;
        node->prev = head;
        head->next = node;
    };
    void removeNode(DLinkedNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    };
    void moveToHead(DLinkedNode *node) {
        removeNode(node);
        addToHead(node);
    };
    DLinkedNode* removeTail() {
        DLinkedNode *node = tail->prev;
        removeNode(node);
        return node;
    };

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        moveToHead(cache[key]);
        return cache[key]->val;
    }

    void put(int key, int value) {
        if (get(key) != -1) {
            cache[key]->val = value;
            return ;
        }

        if (size == capacity) {
            DLinkedNode *deleteNode = removeTail();
            size--;
            cache.erase(deleteNode->key);
            delete deleteNode;
        }
        DLinkedNode *newNode = new DLinkedNode(key, value);
        addToHead(newNode);
        size++;
        cache[key] = newNode;
    }

};


