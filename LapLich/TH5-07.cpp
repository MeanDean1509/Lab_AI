#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

struct CongViec
{
    int p;
    int d;
};

void merge(CongViec TP[], int left, int mid, int right, int order) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    CongViec *L = new CongViec[n1];
    CongViec *R = new CongViec[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = TP[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = TP[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((order == 1 && L[i].p <= R[j].p)) {
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
    delete[] L;
    delete[] R;
}

void mergeSort(CongViec TP[], int left, int right, int order) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(TP, left, mid, order);
        mergeSort(TP, mid + 1, right, order);
        merge(TP, left, mid, right, order);
    }
}

void SapXepCV(vector<CongViec> &CV, int n) {
    int DemDH = 0;
    int DemTH = 0;
    int c = 0;
    cout << "Cac cong viec tre han la: " << endl;
    for (int i = 0; i < n; i++) {
        c += CV[i].p;
        // cout << "(" << CV[i].p << "; " << CV[i].d << ")" <<" "<<c<< endl;
        if (c > CV[i].d) {
            DemTH++;
             cout << "(" << CV[i].p << "; " << CV[i].d << ")" <<" "<<c<<" Tre"<< endl;
        } else{
            cout << "(" << CV[i].p << "; " << CV[i].d << ")" <<" "<<c<<" Dung"<< endl;
            DemDH++;
        }
    }
    cout << "So luong cong viec tre han: " << DemTH << endl;
    cout << "So luong cong viec dung han: " << DemDH << endl;
}

int main() {
    ifstream file("schedule5.txt");
    int n;
    file >> n;

    vector<CongViec> CV(n);

    for (int i = 0; i < n; i++) {
        file >> CV[i].p;
        file >> CV[i].d;
    }
    file.close();

    mergeSort(CV.data(), 0, n - 1, 1);

    SapXepCV(CV, n);
    return 0;
}
