#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

struct DoanThang
{
    int trai;
    int phai;
};

bool kiemtragiaonhau(const DoanThang &a, const DoanThang &b) {
    return a.trai < b.phai && b.trai < a.phai;
}

void merge(DoanThang TP[], int left, int mid, int right, int order) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    DoanThang *L = new DoanThang[n1];
    DoanThang *R = new DoanThang[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = TP[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = TP[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((order == 1 && L[i].trai <= R[j].trai) || (order == 2 && L[i].phai <= R[j].phai)) {
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

void mergeSort(DoanThang TP[], int left, int right, int order) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(TP, left, mid, order);
        mergeSort(TP, mid + 1, right, order);
        merge(TP, left, mid, right, order);
    }
}

int main() {
    ifstream file("line5.txt");
    int n;
    file >> n;

    vector<DoanThang> DT(n);

    for (int i = 0; i < n; i++) {
        file >> DT[i].trai;
        file >> DT[i].phai;
    }
    file.close();

    mergeSort(DT.data(), 0, n - 1, 1);

    vector<DoanThang> Pass(n);
    int nPass = 0;
    Pass[0] = DT[0];

    for (int i = 1; i < n; i++) {
        if (!kiemtragiaonhau(Pass[nPass], DT[i])) {
            nPass++;
            Pass[nPass] = DT[i];
        }
    }

    cout << "Tap cac doan thang khong giao nhau:" << endl;
    for (int i = 0; i <= nPass; i++) {
        cout << Pass[i].trai << ", " << Pass[i].phai << endl;
    }
    cout << endl;
    cout << "So luong cac doan thang khong giao nhau: " << nPass + 1 << endl;

    return 0;
}
