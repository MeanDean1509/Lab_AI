#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define  MAXN  1200
int n, XuatPhat;
int a[MAXN][MAXN];

int DuongDi[MAXN];
bool DaDi[MAXN]; 


void docfile() {
    ifstream file("tsp2b.txt");
    file >> n >> XuatPhat;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
}

int GTS1() {
    int ChiPhi = 0;
    DuongDi[0] = XuatPhat;
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

int main() {
    docfile();
    int ChiPhi = GTS1();

    cout << "Chi phi nho nhat theo thuat toan tham lam la: " << ChiPhi << endl;

    return 0;
}
