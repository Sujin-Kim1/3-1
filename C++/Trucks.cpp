#include <iostream>
#include <fstream>
#include <deque>
#include <numeric>

using namespace std;

int main() {
    int T;
    ifstream inStream("input.txt");
    inStream >> T;
    for (int i = 0; i < T; i++) {
        int n, w, l, tmp, time = 0;
        inStream >> n >> w >> l;
        int bridge[w], trucks[n];
        for (int j = 0; j < n; j++) {
            inStream >> tmp;
            trucks[j] = tmp;
        }
        for (int j = 0; j < n; j++) {

        }
//        deque<int> trucks, bridge(w, 0);
//        for (int j = 0; j < n; j++) {
//            inStream >> tmp;
//            trucks.push_back(tmp);
//        }
//        while (!bridge.empty()) {
//            time++;
//            bridge.pop_front();
//            if (!trucks.empty()) {
//                if (accumulate(bridge.begin(), bridge.end(), 0) + trucks.front() <= l) {
//                    bridge.push_back(trucks.front());
//                    trucks.pop_front();
//                } else {
//                    bridge.push_back(0);
//                }
//            }
//        }
        cout << time << endl;
    }
}