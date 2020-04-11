#include <iostream>
#include <fstream>

using namespace std;

void Henry(fstream &inStream);
int gcd(int a, int b);

int main() {
    fstream inStream("input.txt");
    int T;
    inStream >> T;
    for (int i = 0; i < T; i++) {
        Henry(inStream);
    }
}

void Henry(fstream &inStream) {
    int a, b;
    inStream >> a >> b;

    for (int i = 2; i <= 10000; i++) {
        if (a == 1)
            break;

        // 약분
        int g = gcd(a, b);
        a /= g;
        b /= g;

        if (a * i - b >= 0) {  // 통분했을 때 (ax1 - b) / bx1 꼴
            a = a * i - b;
            b = b * i;
        }
    }
    cout << b << endl;
}

int gcd(int a, int b) {
    while (a != 0) {
        int temp = b % a;
        b = a;
        a = temp;
    }
    return b;
}