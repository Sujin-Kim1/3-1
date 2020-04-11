#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    ifstream inStream("input.txt");
    inStream >> T;
    for (int i = 0; i < T; i++) {
        int n, tmp, a, b, max, size;
        vector<int> v;
        inStream >> n;
        for (int j = 0; j < n; j++) {
            inStream >> tmp;
            v.push_back(tmp);
        }
        size = v.size();
        sort(v.begin(), v.end());
        // 음수 음수 양수, 양수 양수 양수
        a = v[0] * v[1] * v[size -1] > v[0] * v[1] ? v[0] * v[1] * v[size -1] : v[0] * v[1];
        b = v[size - 1] * v[size - 2] * v[size - 3] > v[size - 1] * v[size - 2] ? v[size - 1] * v[size - 2] * v[size - 3] : v[size - 1] * v[size - 2];
        max = a > b? a : b;
        cout << max << endl;
    }
}