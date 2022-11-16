#include <iostream>
#include <string>
#include <vector>

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
        // Get para obtener el nombre del jugador
        string get_username(){
            return username;
        }

        // Get para obtener la pieza del jugador
        string get_pieza(){
            return pieza;
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

int inicializar_tablero(){
    // Selecionamos el tamaño del tablero
    cout << "Seleccione el tamaño del tablero: " << endl;
    cout << "1. 3x3" << endl; // int sz = 7
    cout << "2. 4x4" << endl; // int sz = 9
    cout << "3. 5x5" << endl; // int sz = 11

    int sz, opcion;
    cin >> opcion;
    switch (opcion) {
        case 1:
            sz = 7;
            break;
        case 2:
            sz = 9;
            break;
        case 3:
            sz = 11;
            break;
        default:
            sz = 7;
            break;
    }

    return sz;
};

// Funcion movimiento de jugador
void movimiento_jugador(jugador *jugador,tablero *tablero){
    int x0,y0,x,y;
    cout << "Ingrese las coordenadas del punto de inicio: " << endl;
    cin >> x0 >> y0;
    cout << "Ingrese las coordenadas del punto de fin: " << endl;
    cin >> x >> y;
    string **matriz = tablero->matriz;
    string w = jugador->get_pieza();
    matriz = jugador->modificar_matriz(tablero,x0,y0,x,y,w);
    tablero->imprimir_matriz(matriz,tablero->sz);
};

// Funcion para verificar si el algun jugador gano un cuadrado
bool verificar_cuadrado(jugador *jugador,tablero *tablero){
    string **matriz = tablero->matriz;
    string w = jugador->get_pieza();
    int sz = tablero->sz;
    int x=0;
    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            if(matriz[i][j]==w){
                if(i%2==0 and j%2==0){
                    if(matriz[i-1][j-1]==w and matriz[i-1][j+1]==w and matriz[i+1][j-1]==w and matriz[i+1][j+1]==w){
                        return true;
                    }
                }
            }
        }
    }
    return false;
};

int main(){

    // Bienvenida
    bienvenida();

    // Limpiamos la pantalla
    system("clear");

    // Creamos un objeto tablero
    tablero tablero(inicializar_tablero());

    // Rellenamos la matriz del tablero
    tablero.matriz = tablero.relleno_matriz(tablero.matriz,tablero.sz);

    // Creamos un vector de jugadores
    vector<jugador> jugadores;
    
    // Inicializamos los jugadores
    jugadores.push_back(jugador("Jugador 1","X"));
    jugadores.push_back(jugador("Jugador 2","O"));

    // Movimiento de los jugadores
    int turno = 0;
    while(true){
        system("clear");
        cout << "Turno de: " << jugadores[turno].get_username() << endl;
        tablero.imprimir_matriz(tablero.matriz,tablero.sz);
        movimiento_jugador(&jugadores[turno],&tablero);
        if(verificar_cuadrado(&jugadores[turno],&tablero)){
            cout << "Ganaste un cuadrado" << endl;
            cin.get();
        }
        turno = (turno + 1) % 2;
    }
};