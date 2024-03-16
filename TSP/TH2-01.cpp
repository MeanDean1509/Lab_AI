#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX_N = 40;
int n;
int a[MAX_N][MAX_N];
int path[MAX_N];
int best_path[MAX_N];
int min_chiphi = INT_MAX;

void docfile(){
  ifstream file("tsp_12vertex.txt");
 file >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
        }
    }

}

void dichuyen(int pos, int chiphi, int depth, int visited) {
    if (depth == n) {
        if (chiphi + a[pos][0] < min_chiphi) {
            min_chiphi = chiphi + a[pos][0];
            copy(path, path + n, best_path);
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!(visited & (1 << i))) {
            path[depth] = i;
            dichuyen(i, chiphi + a[pos][i], depth + 1, visited | (1 << i));
        }
    }
}

int main() {
  

   
   
    docfile();
    path[0] = 0; 
    dichuyen(0, 0, 1, 1);

    cout << "Duong di ngan nhat: ";
    for (int i = 0; i < n; ++i) {
        cout << best_path[i]+1 << " -> ";
    }
    cout << "1" << endl;
    cout << "Chi phi thap nhat: " << min_chiphi << endl;

    return 0;
}
