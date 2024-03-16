#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const int MAX = 1000;

struct Toado {
    double x;  // Thay đổi kiểu dữ liệu từ int sang double
    double y;  // Thay đổi kiểu dữ liệu từ int sang double
};

Toado* diem;
Toado* cum;
int* cum_assignment;
int n, k;

void docfile() {
    ifstream file("input.txt");
    file >> n >> k;

    diem = new Toado[n];
    cum = new Toado[k];
    cum_assignment = new int[n];

    for (int i = 0; i < n; i++) {
        file >> diem[i].x >> diem[i].y;
    }

    for (int i = 0; i < k; i++) {
        file >> cum[i].x >> cum[i].y;
    }
}

double tinhKhoangCachManhattan(Toado diem, Toado trungTam) {
    return abs(diem.x - trungTam.x) + abs(diem.y - trungTam.y);
}

int ganVaoCum(Toado diem, Toado* cum, int k) {
    double khoangCachNhoNhat = numeric_limits<double>::max();
    int indexCum = -1;

    for (int i = 0; i < k; i++) {
        double khoangCach = tinhKhoangCachManhattan(diem, cum[i]);
        if (khoangCach < khoangCachNhoNhat) {
            khoangCachNhoNhat = khoangCach;
            indexCum = i;
        }
    }

    return indexCum;
}

void kMeans() {
    const int soLanLapToiDa = 100; 
    for (int lanLap = 0; lanLap < soLanLapToiDa; lanLap++) {
       
        for (int i = 0; i < n; i++) {
            cum_assignment[i] = ganVaoCum(diem[i], cum, k);
        }

       
        vector<int> kichThuocCum(k, 0);
        vector<Toado> tongCum(k, {0.0, 0.0});  // Thay đổi kiểu dữ liệu từ int sang double

        for (int i = 0; i < n; i++) {
            int indexCum = cum_assignment[i];
            kichThuocCum[indexCum]++;
            tongCum[indexCum].x += diem[i].x;
            tongCum[indexCum].y += diem[i].y;
        }

        for (int i = 0; i < k; i++) {
            if (kichThuocCum[i] > 0) {
                cum[i].x = tongCum[i].x / kichThuocCum[i];
                cum[i].y = tongCum[i].y / kichThuocCum[i];
            }
        }
    }
}

int main() {
    docfile();
    kMeans();

    cout << "Toa do cuoi cung cua cum:\n";
    for (int i = 0; i < k; i++) {
        cout << "Cum " << i + 1 << ": (" << cum[i].x << ", " << cum[i].y << ")\n";
    }

    cout << "Ket qua:\n";
    for (int i = 0; i < k; i++) {
        cout << "Cum " << i + 1 << ": \n";
        
        cout << "Cac diem thuoc cum " << i + 1 << ":\n";
        for (int j = 0; j < n; j++) {
            if (cum_assignment[j] == i) {
                cout << "Diem " << j + 1 << ": (" << diem[j].x << ", " << diem[j].y << ")\n";
            }
        }
        cout << "\n";
    }

    delete[] diem;
    delete[] cum;
    delete[] cum_assignment;

    return 0;
}
