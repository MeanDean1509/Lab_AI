#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits> 
using namespace std;
#define  MAXN  1300
int n;
int a[MAXN][MAXN];
int Color[MAXN];
int DaDi[MAXN];
int Somau = 0;
struct Thanhpho {
    int SoLuongTPKe;
    int Ten;
};
void docfile() {
    ifstream file("color1b.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
}
void merge(struct Thanhpho TP[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    struct Thanhpho L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = TP[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = TP[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].SoLuongTPKe >= R[j].SoLuongTPKe) {
            TP[k++] = L[i++];
        } else {
            TP[k++] = R[j++];
        }
    }
    while (i < n1) {
        TP[k++] = L[i++];
    }
    while (j < n2) {
        TP[k++] = R[j++];
    }
}

void mergeSort(struct Thanhpho TP[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(TP, left, mid);
        mergeSort(TP, mid + 1, right);
        merge(TP, left, mid, right);
    }
}
bool CoTheToMau(int TP_hienTai, int mau) {
    for (int i = 1; i <= n; i++) {
        if (a[TP_hienTai][i] == 1 && Color[i] == mau) {
            return false;
        }
    }
    return true;
}

void ToMau(struct Thanhpho TP[]) {
    for (int i = 1; i <= n; i++) {
        Color[i] = -1;
    }

    int Somau = 1;
    for (int i = 1; i <= n; i++) {
        for (int mau = 1; mau <= Somau; mau++) {
            if (CoTheToMau(TP[i].Ten, mau)) {
                Color[TP[i].Ten] = mau;
                Somau = max(Somau, mau + 1);
                break;
            }
        }
    }
    int dem=0;
    cout<<Somau-1<<endl;
    for (int i = 1; i <= n; i++) {
        dem++;
        cout << Color[i]<< " ";
        if (dem==20){
            cout<<endl;
            dem=0;
        }   
    }
}

void DFS(int v) {
    DaDi[v] = true;
    for (int i = 1; i <= n; i++) {
        if (a[v][i] == 1 && !DaDi[i]) {
            DFS(i);
        }
    }
}

bool LienThong() {
   
    memset(DaDi, false, sizeof(DaDi));
    DFS(1);

    
    for (int i = 1; i <= n; i++) {
        if (!DaDi[i]) {
            return false; 
        }
    }

    return true; 
}

int main() {
    docfile();
    struct Thanhpho TP[n+1];
    for ( int i=1; i<=n; i++){
        int dem=0;
        for ( int j =1; j<=n; j++){
            if (a[i][j]==1){
                dem++;
            }
            
        }
        TP[i].SoLuongTPKe=dem;
        TP[i].Ten=i;

    }
    mergeSort(TP, 1, n);
    

    ToMau(TP);
    cout<<endl;
      int vertexWithMaxDegree = TP[1].Ten;

    cout << "Dinh co bac cao nhat: " << vertexWithMaxDegree << endl;
    cout << "So bac cua dinh cao nhat: " << TP[1].SoLuongTPKe << endl;

    cout<<endl;
    if (LienThong()) {
        cout << "Do thi lien thong." << endl;
    } else {
        cout << "Do thi khong lien thong." << endl;
    }


    return 0;
}

