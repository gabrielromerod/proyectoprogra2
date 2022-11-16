#include <iostream>

using namespace std;


// Creamos una clase tablero tablero que pueda ser modificada por la clase jugador
class tablero {
    public:
        // Matrinz de strings con punteros
        string **matriz;
        // Tamaño de la matriz
        int sz;
        // Constructor
        tablero(int sz) {
            this->sz = sz;
            matriz = new string*[sz];
            for(int i=0;i<sz;i++){
                matriz[i]=new string[sz];
            }
        }
        // Destructor
        ~tablero() {
            for(int i=0;i<sz;i++){
                delete[] matriz[i];
            }
            delete[] matriz;
        }
        // Funcion para rellenar la matriz
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
        // Funcion para imprimir la matriz
        void imprimir_matriz(string** matriz,int sz){
            for(int i=0;i<sz;i++){
                for(int j=0;j<sz;j++){
                    cout<<matriz[i][j];
                }
                cout<<endl;
            }
        }
};

// Clase jugador que puede modificar la matriz del tablero
class jugador{
    string username;
    string pieza;
    public:
        jugador(string username,string pieza){
            this->username=username;
            this->pieza=pieza;
        }
        // Funcion para modificar la matriz del tablero
        string **modificar_matriz(tablero *tablero,int x0,int y0,int x,int y,string w){
            int sz = tablero->sz;
            string **matriz = tablero->matriz;
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
};

int main(){
    // Creamos un objeto tablero
    tablero tablero(11);
    // Rellenamos la matriz
    tablero.relleno_matriz(tablero.matriz,tablero.sz);
    // Imprimimos la matriz
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);

    cout << endl;

    // Creamos dos objetos jugador
    jugador jugador1("Jugador 1","X");
    jugador jugador2("Jugador 2","O");

    // Modificamos la matriz del tablero
    tablero.matriz = jugador1.modificar_matriz(&tablero,1,1,1,3,"X");
    // Imprimimos la matriz
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);

    cout << endl;

    // Modificamos la matriz del tablero
    tablero.matriz = jugador2.modificar_matriz(&tablero,1,3,3,3,"O");
    // Imprimimos la matriz
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);


    return 0;
};