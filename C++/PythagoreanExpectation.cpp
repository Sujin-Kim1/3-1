#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

struct Player {
    int win;
    int lose;
    double W;
    Player()
        : win(0), lose(0), W(0.0)
    {}
};

double pythagoreanExpectation(int S, int A) {
    double w = double(S * S) / double(S * S + A * A);
    w *= 1000;
    return (int)w;
}

void solving(ifstream &inStream) {
    // n = 팀 개수, m = 전체 경기 수
    int n, m;
    int a, b, p, q;
    int min, max;
    min = INT_MAX;
    max = INT_MIN;
    inStream >> n >> m;
    struct Player player[n + 1]; // index 를 1부터 시작하게 하기 위해 배열의 크기를 n + 1로 함
    for (int i = 0; i < m; i++) {
        inStream >> a >> b >> p >> q;
        player[a].win += p;
        player[a].lose += q;
        player[b].win += q;
        player[b].lose += p;
    }
    for (int i = 1; i <= n; i++) {
        player[i].W = pythagoreanExpectation(player[i].win, player[i].lose);
//        cout << player[i].win << " " << player[i].lose << " " << player[i].W << endl;
        if (min > player[i].W) {
            min = player[i].W;
        }
        if (max < player[i].W) {
            max = player[i].W;
        }
    }
    cout << max << endl;
    cout << min << endl;
}

int main() {
    ifstream inStream("input.txt");
    int T;
    inStream >> T;
    for (int i = 0; i < T; i++) {
        solving(inStream);
    }
}