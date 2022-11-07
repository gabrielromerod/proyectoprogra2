#include <iostream>
#include<windows.h>
using namespace std;

// funciones matriz
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

string **modificar_matriz(string** matriz,int sz,int x0,int y0,int x,int y,string w){
    x0 = x0 * 2 - 2;y0 = y0 * 2 - 2;x = x * 2 - 2;y = y * 2 - 2;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if(x0 == x){
                if(y>y0){
                    matriz[x0][y-1] = w;
                }
                else {
                    matriz[x0][y0-1]=w;
                }
            }
            else if(y0==y){
                if(x0>x){
                    matriz[x0-1][y]=w;
                }
                else{
                    matriz[x-1][y]=w;
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

// verificadores
int verificador_exitencia_puntos(int max,int x0,int y0,int x,int y){

    if(x0>0 && x0<=max && y0>0 && y0<=max && x>0 && x<=max && y>0 && y<=max){
        return 1;
    }
    return 0;
}

int verificador_diagonales(int x0,int y0,int x,int y){
    if(x0==x || y0 == y){
        return 1;
    }
    return 0;
}

int verificador_puntos_repetidos_y_opuestos(string** matriz,int sz,int x0,int y0,int x,int y,string w,string b){
    x0 = x0 * 2 - 2;y0 = y0 * 2 - 2;x = x * 2 - 2;y = y * 2 - 2;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if(x0 == x){
                if(y>y0){
                    if(matriz[x0][y-1] == w or matriz[x0][y-1] == b){
                        return 0;
                    }
                }
                else {
                    if(matriz[x0][y0-1] == w or matriz[x0][y0-1] == b){
                        return 0;
                    }
                }
            }
            else if(y0==y){
                if(x0>x){
                    if(matriz[x0-1][y]==w or matriz[x0-1][y]==b)
                    return 0;
                }
                else{
                    if(matriz[x-1][y]==w or matriz[x-1][y]==b)
                        return 0;
                }
            }
        }
    }
    return 1;
}
int main() {
    int sz =3;// solo pongan impares falta validador (es el tamaño de la matriz)
    int n; //numero de repeticiones del juego
    int x0 = 0, y0 = 0, x = 0, y = 0;// coordenadas del juego
    int v1,v2,v3; //verificadores
    string **m; //matriz del juego
    cout << "-------------dots and boxes-----------------"<<endl<<endl;
    cout << "Modalidad predeterminada 2 jugadores"<<endl<<endl;
    //system("pause");
    cout << "Digite el tamaño del tablero:";cin>>sz;sz=sz*2+1;
    cout << endl;

    m = crear_matriz(sz);
    m = relleno_matriz(m, sz);
    print(m,sz);

    n = numero_de_repeticiones(m,sz);

    cout << endl;
    cout << "----------El juego comienza---------"<<endl;
    for(int i=0;i<n;i++){
        if (i%2==0){
            cout << endl;
            do {
                cout << "Digite los puntos jugador A ->" << endl;
                cout << "digite el punto de origen:";
                cin >> x0 >> y0;
                cout << "digite el punto destino: ";
                cin >> x >> y;cout<<endl;
                v1 = verificador_exitencia_puntos(sz - (sz-1)/2 , x0, y0, x, y);
                v2 = verificador_diagonales(x0, y0, x, y);
                v3= verificador_puntos_repetidos_y_opuestos(m,sz,x0,y0,x,y,"+","~");
                if (v1 == 0){
                    cout << "Los puntos tienen que estar dentro de las coordenadas " << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
                else if(v2 == 0){
                    cout << "La linea no puede ir en diagonal" << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
                else if(v3==0){
                    cout << "No puede colocar puntos que den la misma linea" << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
            }while(v1==0 || v2==0 || v3==0);
            m = modificar_matriz(m,sz,x0,y0,x,y,"+");
            print(m,sz);
        }
        else{
            cout << endl;
            do {
                cout << "Digite los puntos jugador B ->" << endl;
                cout << "digite el punto de origen:";
                cin >> x0 >> y0;
                cout << "digite el punto destino: ";
                cin >> x >> y;cout<<endl;
                v1 = verificador_exitencia_puntos(sz - (sz-1)/2 , x0, y0, x, y);
                v2 = verificador_diagonales(x0, y0, x, y);
                v3= verificador_puntos_repetidos_y_opuestos(m,sz,x0,y0,x,y,"+","~");
                if (v1 == 0){
                    cout << "Los puntos tienen que estar dentro de las coordenadas " << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
                if(v2 == 0){
                    cout << "La linea no puede ir en diagonal" << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
                else if(v3==0){
                    cout << "No puede colocar puntos que den la misma linea" << endl;
                    cout << "Digite denuevo los puntos "<<endl<<endl;
                }
            }while(v1==0 || v2==0 || v3==0);
            m = modificar_matriz(m,sz,x0,y0,x,y,"~");
            print(m,sz);
        }
    }

    //m = modificar_matriz(m,sz,x0,y0,x,y);
    //print(m,sz);
    //cout << endl<<n;
    }
