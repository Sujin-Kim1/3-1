#include <string>
#include <vector>
#include <iostream>

#define MAX_ELEMENTS 1000000

using namespace std;

class element {
private:
    int key;
public:
    element() { key = -1; };
    element(int val) { key = val; };
    int getKey () const { return key; };
};

class minHeap {
private:
    int n = 0;
    element heap[MAX_ELEMENTS];
public:
    bool isFull() { return n == MAX_ELEMENTS; };
    bool isEmpty() { return !isFull(); };
    void print() {
        for (int i = 0; i < n; i++) {
            cout << heap[i].getKey() << " ";
        }
        cout << endl;
    }
    void insert_minHeap(int key) {
        if (isFull()) exit(-1);
        element item(key);
        cout << item.getKey() << endl;
        int i = ++n;
        while (i != 1 && item.getKey() < heap[i/2].getKey()) {
            heap[i] = heap[i/2];
            i = i/2;
        }
        heap[i] = item;
    };
    int delete_minHeap() {
        if (isEmpty()) exit(-1);
        int parent = 1;
        int child = 2;
        element item = heap[1], temp = heap[n--];
        while (child <= n) {
            if (heap[child].getKey() > heap[child + 1].getKey()) {
                child++;   // 최소값
            }
            if (temp.getKey() <= heap[child].getKey()) {
                break;
            }
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = temp;
        return item.getKey();
    };
    int getTop() {
        cout << "getTop() " << heap[1].getKey() << endl;
        return heap[1].getKey();
    }
};


int solution(vector<int> scoville, int K) {
    int answer = 0;
    if (scoville.size() == 1) {
        if (scoville[0] > K) return 0;
        else return -1;
    }
    minHeap scoville_heap;
    for (int i = 0; i <= scoville.size(); i++) {
        scoville_heap.insert_minHeap(scoville[i]);
    }
    scoville_heap.insert_minHeap(4);
    scoville_heap.print();
    int first = scoville_heap.getTop();
    int second = -1;
    while (first < K) {
        answer++;
        first = scoville_heap.delete_minHeap();
        second = scoville_heap.delete_minHeap();
        int scoville_index = first + second * 2;
        scoville_heap.insert_minHeap(scoville_index);
        int first = scoville_heap.getTop();
        cout << "first " << first << endl;
        if(scoville_heap.isEmpty() && scoville_heap.getTop() < K){
            answer = -1;
            break;
        }
    }
    return answer;
}

int main() {
    vector<int> s = {1, 2, 3, 9, 10, 12};
    int k = 7;
    cout << solution(s, k) << endl;
}