// MSSV: 3121410156
// Ho va Ten : Vo Minh Dien
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define MAXN 13000
bool DaLam[MAXN];
int n;
int a[MAXN];

void docfile() {
    ifstream file("schedulea.txt");
    file >> n;
    for (int i = 1; i <= n; i++) {
        file >> a[i];
    }
}

void phancong(){
    int may1 = 0;
    int may2 =0;
    int may3 = 0;
    for ( int i= 1; i<=n; i++){
        if (may1 <= may2 && may1 <= may3){
            may1+=a[i];
        }
        else if (may2<= may3)
        {
            may2+=a[i];
        }
        else {
            may3+=a[i];
        }
        
    }
   
    // cout<< may1<<" "<<may2<<" "<<may3<<endl;
    if (may1>= may2 && may1 >= may3){
        cout<<may1;
    }
    else if ( may2 >= may3){
        cout<<may2;
    }
    else cout<<may3;
}

int main() {
    docfile();
    phancong();
    return 0;
}


