#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void primes(int n, vector<int> &vPrimes) {
    for (int i = 2; i < n; i++) {
        if (isPrime(i))
            vPrimes.push_back(i);
    }
}

void solving(ifstream &inStream) {
    int n, a, b;
    a = 0;
    b = 10000;
    inStream >> n;

    vector<int> vPrimes;
    vector<int>::iterator it, iter;
    primes(n, vPrimes);
    for (it = vPrimes.begin(); it != vPrimes.end(); it++) {
        for (iter = vPrimes.begin(); iter != vPrimes.end(); iter++) {
            if (*it + *iter == n && abs(*it - *iter) < abs(a - b)) {
                a = *it;
                b = *iter;
            }
        }
    }
    cout << a << " " << b << endl;
}

int main() {
    ifstream inStream("input.txt");
    int T;
    inStream >> T;
    for (int i = 0; i < T; i++) {
        solving(inStream);
    }
}