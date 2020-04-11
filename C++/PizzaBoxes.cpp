#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream inStream("input.txt");
    int t;
    inStream >> t;
    for(int i = 0; i < t; i++) {
        int n, m;
        long long output = 0;
        vector< vector<int> > pizza_boxes;
        vector<int> max_values;
        vector<int>::iterator it;

        inStream >> n >> m;

        // 2차원 pizza_boxes 초기화
        for (int i = 0; i < n; i++) {
            vector<int> element;
            for (int j = 0; j < m; j++) {
                int pizza;
                inStream >> pizza;
                output += pizza; // 모든 원소의 합
                element.push_back(pizza);
            }
            pizza_boxes.push_back(element);
        }
        // row_max 값들을 벡터 max_values 에 추가
        for (int i = 0; i < n; i++) {
            int row_max = 0;
            for (int j = 0; j < m; j++) {
                row_max = (pizza_boxes[i][j] > row_max) ? pizza_boxes[i][j] : row_max;
            }
            // 중복 값이 없도록 max_values 에 한 번만 넣음
            it = find(max_values.begin(), max_values.end(), row_max);
            if (it == max_values.end())
                max_values.push_back(row_max);
        }
        // col_max 값들을 벡터 max_values 에 추가
        for (int i = 0; i < m; i++) {
            int col_max = 0;
            for (int j = 0; j < n; j++) {
                col_max = (pizza_boxes[j][i] > col_max) ? pizza_boxes[j][i] : col_max;
            }
            it = find(max_values.begin(), max_values.end(), col_max);
            if (it == max_values.end())
                max_values.push_back(col_max);
        }
        for (it = max_values.begin(); it != max_values.end(); it++) {
            output -= *it; // max 값들을 빼준다.
        }
        cout << output << endl;
    }
}