#include <iostream>

using namespace std;

class Tablero {
    // Creamos la matriz del tablero con punteros y el tamaño del tablero
    string **matriz;
    int sz;
public:
    // Constructor de la clase
    Tablero(int sz) {
        this->sz = sz;
        matriz = new string*[sz];
        for(int i=0;i<sz;i++){
            matriz[i]=new string[sz];
        }
    }

    // Destructor de la clase
    ~Tablero() {
        for(int i=0;i<sz;i++){
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    // Función para rellenar la matriz
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
};

int main(){
    Tablero tablero(5);
    tablero.relleno_matriz(tablero, 5);
    return 0;
}