#include <iostream>
#include<windows.h>
using namespace std;
string** crear_matriz(int sz){
    string **matriz;
    matriz = new string*[sz];
    for(int i=0;i<sz;i++){
        matriz[i]=new string[sz];
    }
    return matriz;
}

string** relleno_matriz(string** matriz,int sz){
    int x=0;
    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            matriz[i][j]="0";
            if(i==0 or i%2==0){
                matriz[i][j]="*";
                if(j%2!=0){
                    matriz[i][j]="-";x++;
                }
            }
            else{
                if(j==0 or j%2==0){
                    matriz[i][j]="|";x++;
                }
            }
        }
    }
    return matriz;
}

string **modificar_matriz(string** matriz,int sz,int x0,int y0,int x,int y){
    x0 = x0 * 2 - 2;y0 = y0 * 2 - 2;x = x * 2 - 2;y = y * 2 - 2;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if(x0 == x){
                if(y>y0){
                    matriz[x0][y-1] = "M";
                }
                else {
                    matriz[x0][y0-1]="M";
                }
            }
            else if(y0==y){
                if(x0>x){
                    matriz[x0-1][y]="M";
                }
                else{
                    matriz[x-1][y]="M";
                }
            }
        }
    }
    return matriz;
}

int numero_de_repeticiones(string** matriz,int sz){
    int x=0;
    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            if(i==0 or i%2==0){if(j%2!=0){x++;}}
            else{if(j==0 or j%2==0){x++;}}
        }
    }
    return x;
}

void print(string **matriz,int sz){
    int x=0;
    cout << " ";
    for(int i=0;i<sz;i = i + 2){
        cout <<" "<<x+1 << "";
        x++;
    }
    x=0;
    cout << endl;
    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            if(j==0){
                if (i==0 or i%2==0){
                    cout <<x+1;
                    x++;
                }
                else{cout << " ";}
                cout << " ";
            }
            cout <<matriz[i][j];
        }
        cout << endl;
    }
}


int main() {
    int sz =3;// solo pongan impares falta validador (es el tamaño de la matriz)
    int n; //numero de repeticiones del juego
    int x0 = 0, y0 = 0, x = 0, y = 0;// coordenadas del juego
    string **m; //matriz del juego
    cout << "Digite el tamaño del tablero:";cin>>sz;sz=sz*2+1;
    m = crear_matriz(sz);
    n = numero_de_repeticiones(m,sz);
    m = relleno_matriz(m, sz);
    print(m,sz);

    for(int i=0;i<n;i++){
        cout << "digite el punto de origen:";cin>>x0>>y0;
        cout << "digite el punto destino: ";cin>>x>>y;
        m = modificar_matriz(m,sz,x0,y0,x,y);
        print(m,sz);
    }
    //m = modificar_matriz(m,sz,x0,y0,x,y);
    //print(m,sz);
    //cout << endl<<n;
    }
