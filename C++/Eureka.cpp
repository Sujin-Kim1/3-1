#include <iostream>
#include <fstream>

using namespace std;

void eureka(ifstream &inStream);

int main() {
    ifstream inStream("input.txt");
    if (inStream.fail()) {
        cerr << "input file opening failed\n";
    }

    int T;
    inStream >> T;

    for (int i = 0; i < T; i++) {
        eureka(inStream);
    }
    inStream.close();

    return 0;
}

void eureka(ifstream &inStream) {
    int K;
    inStream >> K;
    int n1, n2, n3;
    bool flag = false;
    for (int i = 1; i <= 44; i++) {  // T44 = 990
        n1 = i * (i + 1) / 2;
        for (int j = 1; j <= 44; j++) {
            n2 = j * (j + 1) / 2;
            for (int k = 1; k <= 44; k++) {
                n3 = k * (k + 1) / 2;
                if (n1 + n2 + n3 == K) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            break;
    }
    cout << flag << endl;
}