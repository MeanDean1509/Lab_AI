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
    int Mauduocto;
    int MauKhongDuocTo[MAXN];
    int nMauKDT;
};
struct Thanhpho TP[MAXN];
void docfile() {
    ifstream file("color2b.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            file >> a[i][j];
        }
    }
}

int DinhCoBacCaoNhat(){
    Thanhpho Max=TP[1];
    for ( int i =1; i<=n; i++){
        if (TP[i].SoLuongTPKe > Max.SoLuongTPKe){
            Max = TP[i];
        }
    }
    return Max.Ten;
}

bool DemBac0() {
    int dem = 0;
    for (int i = 1; i <= n; i++) {
        if (TP[i].SoLuongTPKe == 0) {
            dem++;
        }
    }
    if (dem == n) {
        return true;
    }
    return false;
}


void chonmau(){
    int mau=1;
    int flag = DinhCoBacCaoNhat();
    // cout<< DinhCoBacCaoNhat()<<endl;
    TP[flag].SoLuongTPKe = 0;
    while (TP[flag].Mauduocto == 0){
        int dem =0;
        for ( int i =0; i<TP[flag].nMauKDT; i++){
            // cout<<TP[flag].MauKhongDuocTo[i]<<" ";
            if ( mau == TP[flag].MauKhongDuocTo[i]){
                dem++;
            }
        }
        cout<<endl;
        if ( dem>0){
            mau++;
        }
        if (dem==0){
            TP[flag].Mauduocto = mau;
            if (mau>Somau){
                Somau= mau;
            }

        }
    }
    for ( int j = 1; j<=n; j++){
        if (a[flag][j]==1 && TP[j].SoLuongTPKe>0){
            TP[j].SoLuongTPKe--;
            TP[j].MauKhongDuocTo[TP[j].nMauKDT] = TP[flag].Mauduocto;
            TP[j].nMauKDT++;
        }

    }

}
void ToMauDinhConSot(){
    for ( int i =0; i<=n; i++){
        if (TP[i].Mauduocto==0){
            int mau=1;
            while (TP[i].Mauduocto==0)
            {
                
                int dem =0;
                for ( int j =0; j<TP[i].nMauKDT; j++){
                    if (mau == TP[i].MauKhongDuocTo[j]){
                        dem++;
                    }
                }
                if ( dem>0){
                    mau++;
                }
                if (dem==0){
                    TP[i].Mauduocto = mau;
                    if (mau>Somau){
                        Somau= mau;
                    }

                }
            }
        }
    }

}
// void Tomau(){
    
//     // while(!DemBac0){
//     //     chonmau();
//     // }
//     // chonmau();
//     cout<<DinhCoBacCaoNhat()<<endl;
//     chonmau();
//     cout<<DinhCoBacCaoNhat()<<endl;
//     chonmau();
//     // for( int i=1; i<=n; i++){
//     //     cout<<TP[i].SoLuongTPKe<<" ";
//     // }
//     chonmau();
//     chonmau();
//     chonmau();
//     chonmau();
//    for( int i=1; i<=n; i++){
//         cout<<TP[i].SoLuongTPKe<<" ";
//     }
// }

int main() {
    docfile();
   
    for ( int i=1; i<=n; i++){
        int dem=0;
        for ( int j =1; j<=n; j++){
            if (a[i][j]==1){
                dem++;
            }
            
        }
        TP[i].SoLuongTPKe=dem;
        TP[i].Ten=i;
        TP[i].MauKhongDuocTo[0]=0;
        TP[i].nMauKDT=1;
        TP[i].Mauduocto = 0;

    }
    while(!DemBac0()){
        chonmau();
    }
    // chonmau();
    // chonmau();
    // chonmau();
    ToMauDinhConSot();
    cout<<endl;
    cout<<"So mau: "<< Somau<<endl;
    int demdong=0;
    for ( int i=1; i<=n; i++){
        cout<< TP[i].Mauduocto<<" ";
        demdong++;
        if ( demdong==20){
            cout<<endl;
            demdong=0;
        }

    }
    return 0;
}

