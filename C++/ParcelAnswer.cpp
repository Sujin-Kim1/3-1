#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
bool chk[800001] = { 0, };
int N, W, A[5005];
void parcel() {
    for (int k = 0; k < N; k++) {
        for (int l = k + 1; l < N; l++) {
            if (A[k] + A[l] > W)
                break;
            if (chk[W - A[k] - A[l]]) {
                cout << "YES" << endl;
                return;
            }
        } for (int j = 0; j < k; j++) {
            chk[A[j] + A[k]] = true;
        }
    }
    cout << "NO" << endl;
}
int main() {
    ifstream in("input.txt");
    int T;
    in >> T;
    while (T--) {
        in >> W >> N;
        bool check = false;
        for (int i = 0; i < N; i++) {
            in >> A[i];
        }
        sort(A, A + N);
        parcel();
        memset(chk, false, sizeof(bool) * 800001);
        memset(A, 0, sizeof(int) * 5005);
    }
}