#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits> 
using namespace std;

#define  MAXN  1200
int n, m;
int a[MAXN][MAXN];
int ListHanhTrinh[MAXN];


void docfile() {
    ifstream file("tsp3b.txt");
    file >> n >> m;
    
    for ( int i=0; i<m; i++){
        file >> ListHanhTrinh[i];
       
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
}

int GTS1(int XuatPhat) {
    int ChiPhi = 0;
    bool DaDi[MAXN];
    int DuongDi[MAXN];
    DuongDi[0] = XuatPhat;

    for (int i = 1; i <= n; i++) {
        DaDi[i] = false; 
    }
    DaDi[XuatPhat] = true;

    for (int i = 2; i <= n; i++) {
        int MinChiPhi = INT_MAX;
        int ThanhPhoKeTiep = 0;

        for (int j = 1; j <= n; j++) {
            if (!DaDi[j] && a[XuatPhat][j] < MinChiPhi) {
                MinChiPhi = a[XuatPhat][j];
                ThanhPhoKeTiep = j;
            }
        }

        DuongDi[i] = ThanhPhoKeTiep; 
        DaDi[ThanhPhoKeTiep] = true;
        ChiPhi += MinChiPhi;
        XuatPhat = ThanhPhoKeTiep;
    }

    ChiPhi += a[XuatPhat][DuongDi[0]];

    return ChiPhi;
}

int GTS2() {
    int BestChiPhi = INT_MAX; 

    for (int i = 0; i < m; i++) {
        int cp = GTS1(ListHanhTrinh[i]);
        // cout<<cp<<endl;
        if (BestChiPhi > cp) {
            BestChiPhi = cp;
        }
    }

    return BestChiPhi;
}

void WriteGTS2() {
    

    for (int i = 0; i < m; i++) {
        int cp = GTS1(ListHanhTrinh[i]);
        cout<<cp<<endl;
        
    }

   
}
int main() {
    docfile();

    cout << "Chi phi cua hanh trinh tot nhat la: " <<GTS2()<<endl;
    WriteGTS2();
    return 0;
}
