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

void bienvenida(){
    cout<<"Bienvenido a dots and boxes"<<endl;
    cout<<"El juego consiste en unir puntos para formar cuadrados"<<endl;
    cout<<"El jugador que forme mas cuadrados gana"<<endl;
    cout<<"Para unir puntos se debe ingresar la coordenada de los puntos a unir"<<endl;
    cout<<"Ejemplo: 1 1 1 2"<<endl;
    cout<<"El primer par de numeros es la coordenada del punto de inicio"<<endl;
    cout<<"El segundo par de numeros es la coordenada del punto de fin"<<endl;
    cout<<"El juego termina cuando ya no se puedan unir mas puntos"<<endl;
    cout<<"Presione enter para continuar"<<endl;
    cin.get();
};

void registro_usuarios(){
    string username;
    string pieza;
    cout<<"Ingrese su nombre de usuario: ";cin>>username;
    cout<<"Ingrese su pieza: ";cin>>pieza;
    jugador *jugador1 = new jugador(username,pieza);
    cout<<"Ingrese su nombre de usuario: ";cin>>username;
    cout<<"Ingrese su pieza: ";cin>>pieza;
    jugador *jugador2 = new jugador(username,pieza);
};

int main(){

    bienvenida();
    // Creamos un objeto tablero
    tablero tablero(11);
    // Rellenamos la matriz
    tablero.relleno_matriz(tablero.matriz,tablero.sz);
    // Imprimimos la matriz
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);

    // Limpiamos la pantalla
    system("clear");

    registro_usuarios();

    // Limpiamos la pantalla
    system("clear");

    // Imprimimos la matriz
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);

    return 0;
};