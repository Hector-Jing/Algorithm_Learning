#include <iostream>
#include <vector>

using namespace std;

class MaxPQ{
private:
    vector<int> pq;
    int N;

    // void buildMaxPQ(); // 建最大堆
    void swim(int k); // 上浮
    void sink(int k); // 下沉
    

public:
    MaxPQ(int capacity) : pq(capacity), N(0){};
    // void buildMaxPQ(vector<int>& nums);
    // void sink_nums(vector<int>& nums, int k);
    // bool isEmpty() const;
    // void insert(const int x);
    // void delMax();

};



// void MaxPQ::buildMaxPQ(){
//     for(int i = N / 2; i >= 0; --i){
//         sink(i);
//     }
// }

void MaxPQ::swim(int k){
    while(k > 1 && (pq[k/2] < pq[k])){
        swap(pq[k/2], pq[k]);
        k = k/2;
    }
}

void MaxPQ::sink(int k){
    while(2 * k <= N){
        int older = 2 * k;
        if(older < N && (pq[older] < pq[older+1])) older++;
        if(pq[older] < pq[k]) break;
        swap(pq[older], pq[k]);
        k = older; 
    }
}

void maxHeapify(vector<int>& a, int i, int heapSize) {
    int l = i * 2 + 1, r = i * 2 + 2, largest = i;
    if (l < heapSize && a[l] > a[largest]) {
        largest = l;
    } 
    if (r < heapSize && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, largest, heapSize);
    }
}

void buildMaxHeap(vector<int>& a, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
        maxHeapify(a, i, heapSize);
    } 
}

int findKthLargest(vector<int>& nums, int k) {
    int heapSize = nums.size();
    buildMaxHeap(nums, heapSize);
    for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
        swap(nums[0], nums[i]);
        --heapSize;
        maxHeapify(nums, 0, heapSize);
    }
    return nums[0];
}

void heapSort(vector<int>& nums, int heapSize){
    for (int i = heapSize / 2; i >= 0; --i) {
        maxHeapify(nums, i, heapSize);
    }

    for(int i = heapSize - 1; i >= 1; --i){
        swap(nums[i], nums[0]);
        maxHeapify(nums, 0, i);
    }
}

int main(){
    int a[6] = {1,4,0,3,5,2};
    vector<int> nums(a, a+6);
    int n = nums.size();
    heapSort(nums, n);
    for(int i = 0; i < nums.size();++i){
        cout << nums[i] << endl;
    }

}