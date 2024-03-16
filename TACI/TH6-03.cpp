#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;
#define MAXN 1300

int n;
int ntc=0;
int nclose=0;
int a[3][3];
int b[3][3];
int tamTren[3][3];
int tamDuoi[3][3];
int tamTrai[3][3];
int tamPhai[3][3];
struct TACI{

    int id;
    int g,h,f;
    int S[3][3];
};
 vector<TACI> tc(MAXN);
 vector<TACI> close(MAXN);

void docfile() {
    ifstream file("taci5.txt");
    file >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> b[i][j];
        }
    }
}

int h1(int arr1[3][3], int arr2[3][3]){
    int dem = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr1[i][j] != 0 && arr1[i][j] != arr2[i][j]) {
                dem++;
            }
        }
    }
    return dem;
}

void swap(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}
bool kiemtratrungSid ( int arr1[3][3]){
    for ( int i =0; i<nclose; i++){
        if (h1(arr1,close[i].S) == 0){
            return true;
        }
    }
    return false;
}
void dichuyen(){
    while(h1(a,b)!=0){

        int I, J,y,x;
        int flag=0;
        int min = INT_MAX;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] == 0) {
                    I = i;
                    J = j;
                }
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    tamTren[i][j]=a[i][j];
                    tamDuoi[i][j]=a[i][j];
                    tamTrai[i][j]=a[i][j];
                    tamPhai[i][j]=a[i][j];
                }
                
        }
        // cout<< I << J << endl;
        if (I > 0) {
            x = I - 1;
            y = J;
        
        swap(tamTren[I][J], tamTren[x][y]);

        
            if ( h1(tamTren,b) < min && !kiemtratrungSid(tamTren)){
            
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                    a[i][j]= tamTren[i][j];
                    }
                
                }
                min = h1(tamTren,b);
                flag=1;
            }
        
        } 
        if (I <2 ) {
            x = I +1;
            y = J;
        
        swap(tamDuoi[I][J], tamDuoi[x][y]);

            if ( h1(tamDuoi,b) < min && !kiemtratrungSid(tamDuoi)){
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                    a[i][j]= tamDuoi[i][j];
                    }
                
                }
                min = h1(tamDuoi,b);
                flag=1;            
            }
        
        }
        if (J>0 ) {
            x = I;
            y = J - 1;
        
        swap(tamTrai[I][J], tamTrai[x][y]);

            if ( h1(tamTrai,b) < min && !kiemtratrungSid(tamTrai)){
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                    a[i][j]= tamTrai[i][j];
                    }
                
                }
                min = h1(tamTrai,b);
                flag=1;
            }

        
        } 
        if (J <2 ) {
            x = I;
            y = J + 1;
        
        swap(tamPhai[I][J], tamPhai[x][y]);

            if ( h1(tamPhai,b) < min && !kiemtratrungSid(tamPhai)){
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                    a[i][j]= tamPhai[i][j];
                    }
                
                }
                min = h1(tamPhai,b);
                flag=1;
            }

        
        } 
        if ( flag==1){
                close[nclose].id = nclose;
            close[nclose].g = nclose;
            close[nclose].h = h1(a,b);
            close[nclose].f = close[nclose].g+close[nclose].h;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    close[nclose].S[i][j] = a[i][j];
                }
            }
            nclose++;
        }
        else{

         cout<<"Khong the di den trang thai ket thuc"<<endl;
         break;
        }
    }
  
        
    
    
}
int main() {
    docfile();
    
    tc[0].id = 0;
    tc[0].g = 0;
    tc[0].h = h1(a,b);
    tc[0].f = tc[0].h+ tc[0].g;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tc[0].S[i][j] = a[i][j];
        }
    }
   
    close[0] = tc[0];
    nclose++;
  
        dichuyen();
      
    
        
        
    
    
    for ( int i=0; i<nclose; i++){
        
            string kq = " S" + to_string(close[i].id) + "\tg= " + to_string(close[i].g) + ", h= " + to_string(close[i].h) + ", f= " + to_string(close[i].f) + "\n";
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                kq += to_string(close[i].S[j][k]) + " ";
            }
            kq += "\n";
        }
        cout<<kq;
        
    }
    cout<<"\nGia tri g: "<<close[nclose-1].g;
    return 0;
}

