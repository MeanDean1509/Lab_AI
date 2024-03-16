// MSSV: 3121410156
// Ho va Ten : Vo Minh Dien
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define MAXN 1300
bool DaLam[MAXN];
int n;
int a[MAXN][MAXN];

void docfile() {
    ifstream file("assignmentd.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
}

 void findMaxInRow() {
    int sum=0;
    for ( int i =1; i<=n; i++){
         int max_row = INT_MIN; 
        int max_col = -1; 
    for (int j = 1; j <= n; j++) {
        if (a[i][j] > max_row  && DaLam[j]==false) {
           
            max_row = a[i][j];
            max_col = j;
          
        }
    }
         DaLam[max_col] = true;
    
    // cout << "Max tren dong " << i << ": " << max_row << " tai cot " << max_col << endl;
    sum+= max_row;
    
 }
  cout<<endl<<sum;
}

int main() {
    docfile();
    for (int i=1; i<=n; i++){
        DaLam[i]= false;
    }
    
        findMaxInRow();
    
    return 0;
}


