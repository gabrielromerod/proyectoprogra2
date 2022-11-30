#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
                            matriz[i][j]="─";x++;
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
        // Funcion para imprimir la matriz en pantalla con las coordenadas de la matriz en la esquina superior izquierda de la matriz saltanto una linea
        void imprimir_matriz(string** matriz,int sz){
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
};

class jugador{
    string username;
    string pieza;
    int puntaje = 0;
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

        // Validar si el movimiento es valido usando un booleano
        bool validar_movimiento(tablero *tablero,int x0,int y0,int x,int y){
            int sz = tablero->sz;
            string **matriz = tablero->matriz;
            x0 = x0 * 2 - 2;y0 = y0 * 2 - 2;x = x * 2 - 2;y = y * 2 - 2;
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    if(x0 == x){
                        if(y>y0){
                            if (matriz[x0][y-1] == "$" or matriz[x0][y-1] == "X"){
                                return false;
                            }
                        }
                        else {
                            if (matriz[x0][y0-1] == "$" or matriz[x0][y0-1] == "X"){
                                return false;
                            }
                        }
                    }
                    else if(y0==y){
                        if(x0>x){
                            if (matriz[x0-1][y] == "$" or matriz[x0-1][y] == "X"){
                                return false;
                            }
                        }
                        else{
                            if (matriz[x-1][y] == "$" or matriz[x-1][y] == "X"){
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }

        // Get para obtener el nombre del jugador
        string get_username(){
            return username;
        }

        // Get para obtener la pieza del jugador
        string get_pieza(){
            return pieza;
        }

        // Get para obtener el puntaje del jugador
        int get_puntaje(){
            return puntaje;
        }

        // Suma 1 al puntaje del jugador
        void sumar_puntaje(){
            puntaje++;
        }
};