#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int T;
    ifstream inStream("input.txt");
    inStream >> T;
    for (int i = 0; i < T; i++) {
        int w, n, tmp;
        inStream >> w >> n;
        // 𝐴(1 ≤ 𝑖 ≤ 𝑛)이므로 B에 들어갈 수 있는 최대값은 w - 6이다.
        // w - 6 이하인 수만 v에 삽입한다.
        vector<int> v;
        for (int j = 0; j < n; j++) {
            inStream >> tmp;
            if (tmp <= w - 6)
                v.push_back(tmp);
        }
        int size = v.size();
        if (size < 4)
            cout << "NO" << endl;
        else {
            sort(v.begin(), v.end());
            if (accumulate(v.end() - 4, v.end(), 0) < w or accumulate(v.begin(), v.begin() + 4, 0) > w) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
//                int a = size - 4, b = size - 3, c = size - 2, d = size - 1;
//                for (; v[a] + v[b] + v[c] + v[d] != w && d != 3;) {
//                    if (c == 2) {
//                        d--;
//                        c = d - 1;
//                        b = c - 1;
//                    } else {
//                        if (b == 1) {
//                            c--;
//                            b = c - 1;
//                            a = b - 1;
//                        } else {
//                            if (a == 0) {
//                                b--;
//                                a = b - 1;
//                            } else {
//                                a--;
//                            }
//                        }
//                    }
//                }
//                if (v[a] + v[b] + v[c] + v[d] == w) {
//                    cout << "YES" << endl;
//                } else {
//                    cout << "NO" << endl;
//                }
            }
        }
    }
}