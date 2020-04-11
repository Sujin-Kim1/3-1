#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void palindrome(ifstream &inStream) {
    int num, base;
    bool result = false;
    inStream >> num;

    for (base = 2; base <= 64; base++) {
        int n_copy = num;
        // 진법 변환 (뒤집힌 결과임)
        vector<int> v;
        while (n_copy != 0) {
            v.push_back(n_copy % base);
            n_copy /= base;
        }
        // palindrome 판정
        bool isPalindrome = true;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != v[v.size() - i - 1]) {
                isPalindrome = false;
                break;
            }
        }
        if (isPalindrome) {
            result = true;
            break;
        }
    }
    cout << result << endl;
}

int main() {
    ifstream inStream("input.txt");
    int T;
    inStream >> T;
    for (int i = 0; i < T; i++) {
        palindrome(inStream);
    }
}