#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int numSquareSum(int n) {
    int squareSum = 0;
    while (n) {
        squareSum += (n % 10) * (n % 10);
        n /= 10;
    }
    return squareSum;
}

void HappyNumber(fstream &inStream) {
    int n;
    vector<int> s;
    vector<int>::iterator it;

    inStream >> n;
    s.push_back(n);

    while(true) {
        if (n == 1) {
            cout << "HAPPY" << endl;
            break;
        }
        n = numSquareSum(n);
        it = find(s.begin(), s.end(), n);
        if (it != s.end()) {
            cout << "UNHAPPY" << endl;
            break;
        }
        s.push_back(n);
    }

//    int slow, fast;
//    slow = fast = n;
//    do {
//        slow = numSquareSum(slow);
//        fast = numSquareSum(numSquareSum(fast));
//    } while (slow != fast);
//
//    if (slow == 1) {
//        cout << "HAPPY" << endl;
//    } else {
//        cout << "UNHAPPY" << endl;
//    }
}

int main() {
    fstream inStream("input.txt");
    int t;
    inStream >> t;
    for (int i = 0; i < t; i++) {
        HappyNumber(inStream);
    }
}