#include <iostream>
#include <ios>
#include <algorithm>
#include <fstream>
using namespace std;

int binary[3] = { 0, };
void search(int* arr, int k, int* min, int* count, int s, int e);

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int min = 0, total_min = 0;
    int count = 0, total_count = 0;

    int t = 0;
    int n = 0, k = 0;

    int key = 0, start = 0, end = 0;

    ifstream in("input.txt");
    in >> t;
    for (int m = 0; m < t; m++) {
        in >> n >> k;

        int *arr = new int[n];

        for (int i = 0; i < n; i++) {
            in >> arr[i];
        }

        sort(arr, arr + n);


        for (int i = 0; i < n - 1; i++) {
            key = k - arr[i];
            start = i + 1;
            end = n - 1;

            search(arr, key, &min, &count, start, end);

            if (i == 0) {
                total_min = min;
                total_count = count;
            }
            else {
                if (min == total_min) {
                    total_count += count;
                }

                if (min < total_min) {
                    total_min = min;
                    total_count = count;
                }
            }
        }
        cout << total_count << endl;
    }
}

void search(int* arr, int k, int* min, int* count, int s, int e) {
    int r = e, l = s, m = 0;

    while (l <= r) {
        m = (l + r) / 2;
        if (arr[m] == k) {
            break;
        }
        else if (k > arr[m]) {
            l = m + 1;
            continue;
        }
        else {
            r = m - 1;
            continue;
        }
    }

    binary[0] = abs(k - arr[m]);

    if (m - 1 >= s) binary[1] = abs(k - arr[m - 1]);
    else binary[1] = 0;

    if (m + 1 <= e) binary[2] = abs(k - arr[m + 1]);
    else binary[2] = 0;

    *min = binary[0];
    if (arr[m] == k) {
        *count = 1;
        return;
    }
    else {
        *count = 0;
        for (int i = 0; i < 3; i++) {
            if (binary[i] != 0)  {
                if (binary[i] < *min) {
                    *min = binary[i];
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (binary[i] == *min) {
                (*count)++;
            }
        }
    }
}