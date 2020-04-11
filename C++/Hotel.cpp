//
// Created by Sujin Kim on 16/09/2019.
//

#include <iostream>
#include <fstream>

using namespace std;

void hotel(ifstream &inStream);

int main() {
    ifstream inStream("input.txt");
    if (inStream.fail()) {
        cerr << "input file opening failed\n";
    }

    int T;
    inStream >> T;

    for (int i = 0; i < T; i++) {
        hotel(inStream);
    }
    inStream.close();

    return 0;
}

void hotel(ifstream &inStream) {
    int H, W, N, output;
    int count = 0;
    inStream >> H >> W >> N;
    while (N > H) {
        N -= H;
        count++;
    }
    output = N * 100; // 층
    output += count + 1; // 호

    cout << output << endl;
}
