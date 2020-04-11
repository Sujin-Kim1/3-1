#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

int minimum(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

/*
 * ***** variables *****
 * error : 현재까지 최소 error 값
 * len : 배열의 길이
 * target : error 가 0 이 되는 내가 찾으려는 값 (k - S[j])
 * midLeftError, midRightError : S[mid - 1], S[mid + 1] 값과 target 의 차. 최소 에러 값을 찾기 위해 필요하다.
 * ***** function *****
 * 최소 에러 값을 찾아 반환한다.
 * */
int binaryMinError(int *S, int error, int len, int target) {
    int mid, midError, midLeftError = INT_MAX, midRightError = INT_MAX;
    int l = 0, r = len - 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (S[mid] == target) return 0;
        else if (S[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    midError = abs(S[mid] - target);
    if (midError == error) return error; // S[mid] - target 이 최소 에러 값과 같으면 에러 반환
    if (mid + 1 != len) midRightError = abs(S[mid + 1] - target);
    if (mid - 1 >= 0) midLeftError = abs(S[mid - 1] - target);
    return minimum(midLeftError, midError, midRightError);
}

bool binarySearch(int *S, int len, int target) {
    int l = 0, r = len - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (S[mid] == target) return true;
        else if (S[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

int main() {
    int T;
    ifstream inStream("input.txt");
    inStream >> T;
    for (int i = 0; i < T; i++) {
        int n, k, error = INT_MAX, count = 0;
        inStream >> n >> k;
        int S[n];
        for (int j = 0; j < n; j++) {
            inStream >> S[j];
        }
        sort(S, S + n);
        if (n == 2) cout << 1 << endl;
        else {
            for (int j = 0; j < n; j++) {
                if (k != 2 * S[j]) {
                    if (binaryMinError(S, error, n, k - S[j]) < error) {
                        error = binaryMinError(S, error, n, k - S[j]);;
                        if (error == 0)
                            break;
                    }
                }
            }
            for (int j = 0; j < n; j++) {
                count += binarySearch(S, n, k - S[j] - error);
                if (error != 0) count += binarySearch(S, n, k - S[j] + error);
            }
            cout << count / 2 << endl;
        }
    }
    inStream.close();
}