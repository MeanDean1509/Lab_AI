#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <bitset>
using namespace std;

const int MAX_N = 40;
int n;
vector<vector<int>> a;
vector<int> path;
vector<int> best_path;
int min_chiphi = INT_MAX;
bitset<MAX_N> visited;

void dichuyen(int pos, int chiphi, int depth) {
    visited[pos] = true;
    path[depth] = pos;

    if (depth == n - 1) {
        if (chiphi + a[pos][0] < min_chiphi) {
            min_chiphi = chiphi + a[pos][0];
            best_path = path;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && chiphi + a[pos][i] < min_chiphi) {
                dichuyen(i, chiphi + a[pos][i], depth + 1);
            }
        }
    }

    visited[pos] = false;
}

int main() {
    ifstream file("tsp1b.txt");

    // Đọc dữ liệu từ file test
    file >> n;
    a.resize(n, vector<int>(n));
    path.resize(n);
    best_path.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
        }
    }

    path[0] = 0;
    visited.reset();
    dichuyen(0, 0, 0);

    cout << "Duong di ngan nhat: ";
    for (int i = 0; i < n; ++i) {
        cout << best_path[i] + 1 << " -> ";
    }
    cout << "1" << endl;
    cout << "Chi phi thap nhat: " << min_chiphi << endl;

    return 0;
}
