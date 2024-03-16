#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define MAXN 1300

int n;
int a[MAXN][MAXN];
int b[MAXN][MAXN];



void docfile() {
    ifstream file("taci1.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> b[i][j];
        }
    }
}

int h1(){
    int dem=0;
    for ( int i =1; i<=n; i++){
        for ( int j =1; j<=n; j++){

        if ( a[i][j]!=0 && a[i][j]!=b[i][j] ){
            dem++;
        }
        }
    }
    return dem;
}
int h2() {
    int h2Value = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 0) {
            
                int Row, Col;
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        if (b[x][y] == a[i][j]) {
                            Row = x;
                            Col = y;
                            break;
                        }
                    }
                }
                int distance = abs(i - Row) + abs(j - Col);
                h2Value += distance;
            }
        }
    }
    return h2Value;
}
int main() {
    docfile();
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << b[i][j] << " ";
    //     }
    //     cout << endl;
    // }

   cout<<"H1: "<<h1();
   cout<<endl;
   cout<<"H2: "<<h2();
    return 0;
}


