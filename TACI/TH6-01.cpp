#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
void randomarr(int n, int m[]) {
    srand(time(0));
    for (int i = n * n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(m[i], m[j]);
    }

}

int main() {
    int n;
    cout << "Nhap so hang va cot cua mang: ";
    cin >> n;


    int a[100][100];
    int b[100][100];
    int m[10000];

    for (int i = 0; i < n * n; ++i) {
        m[i] = i;
    }

   randomarr(n, m);
    
    int index = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = m[index++];
        }
    }
    randomarr(n, m);
     index = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i][j] = m[index++];
        }
    }
 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    ofstream outfile("taci.txt");
    outfile <<n<< endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << a[i][j] << " ";
        }
        outfile << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << b[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
    return 0;
}
