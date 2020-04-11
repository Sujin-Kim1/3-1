#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream inStream("input.txt");
    int t;
    inStream >> t;
    for (int i = 0; i < t; i++) {
        int a, b, n, w;
        inStream >> a >> b >> n >> w;
        if (a == b) {
            if (n == 2 && a + b == w)
                cout << 1 << " " << 1 << endl;
            else
                cout << -1 << endl;
        }
        else {
            int sheep = (w - b * n) / (a - b);
            int gott = (w - a * n) / (b - a);
            if (sheep < 1 or gott < 1 or sheep * a + gott * b != w)
                cout << -1 << endl;
            else
                cout << sheep << " " << gott << endl;
        }
    }
}