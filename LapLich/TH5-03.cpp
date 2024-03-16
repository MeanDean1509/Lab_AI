// MSSV: 3121410156
// Ho va Ten : Vo Minh Dien
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define MAXN 1300
bool DaLam[MAXN];
int n;
int a[MAXN];
int b[MAXN];
struct Nhom
{
   int a;
   int b;
 
};
struct Nhom N1[MAXN];
struct Nhom N2[MAXN];
int tam1=0;
    int tam2=0;
void docfile() {
    ifstream file("Johnsona.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        file >> a[i];
    }
    for ( int i =1; i<=n; i++){
        file >> b[i];
    }
    
}

void ChiaNhom(){
    
    for ( int i =1 ; i<=n; i++){
        if ( a[i]<= b[i]){
            tam1++;
            N1[tam1].a= a[i];
            N1[tam1].b= b[i];
        }
        else {
            tam2++;
            N2[tam2].a= a[i];
            N2[tam2].b= b[i];
        }
        
    }
    
}

void merge(struct Nhom TP[], int left, int mid, int right, int order) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    struct Nhom L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = TP[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = TP[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((order == 1 && L[i].a <= R[j].a) || (order == -1 && L[i].b >= R[j].b)) {
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

void mergeSort(struct Nhom TP[], int left, int right, int order) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(TP, left, mid, order);
        mergeSort(TP, mid + 1, right, order);
        merge(TP, left, mid, right, order);
    }
}
void laplich(){
    int mayA=0;
    int mayB= 0;
    for ( int i = 1 ; i<=tam1; i++){
        mayA+=N1[i].a;
        if (mayA> mayB && N1[i].b>0){
            mayB=mayA;
        }
        mayB+=N1[i].b;
    }
    for ( int i = 1 ; i<=tam2; i++){
        mayA+=N2[i].a;
        if (mayA> mayB && N2[i].b>0){
            mayB=mayA;
        }
        mayB+=N2[i].b;
    }
    cout<<"May A: "<<mayA<<endl;
    cout<<"May B: "<<mayB<<endl;
    cout<<"Thoi gian hoan thanh: ";
    if ( mayA>=mayB) cout<<mayA;
    else cout<<mayB;
}
int main() {
    docfile();
    ChiaNhom();
    mergeSort(N1, 1, tam1,1);
     mergeSort(N2, 1, tam2,-1);
    for ( int i =1; i<=tam1; i++){
        cout<<N1[i].a<<" ";

    }
    cout<<endl;
    for ( int i =1; i<=tam1; i++){
        cout<<N1[i].b<<" ";

    }
    cout<<endl;
    for ( int i =1; i<=tam2; i++){
        cout<<N2[i].a<<" ";

    }
    cout<<endl;
    for ( int i =1; i<=tam2; i++){
        cout<<N2[i].b<<" ";

    }
    cout<<endl;
    laplich();
    return 0;
}


