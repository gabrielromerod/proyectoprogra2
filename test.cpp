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
    cout << "En caso de seleccionar otro numero el tablero sera de 3x3" << endl;

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

bool verificador_exitencia_puntos(int max,int x0,int y0,int x,int y){

    if(x0>0 && x0<=max && y0>0 && y0<=max && x>0 && x<=max && y>0 && y<=max){
        return true;
    }
    return false;
}

// Funcion movimiento de jugador
void movimiento_jugador(jugador *jugador1,jugador *jugador2, tablero *tablero, int sz){
    int x0,y0,x,y;
    cout << "Ingrese las coordenadas del punto de inicio: " << endl;
    cin >> x0 >> y0;
    cout << "Ingrese las coordenadas del punto de fin: " << endl;
    cin >> x >> y;
    string **matriz = tablero->matriz;
    string w = jugador1->get_pieza();
    string w2 = jugador2->get_pieza();
    // Verificamos que las coordenadas ingresadas no esten fuera del tablero
        if (!(x0==x || y0 == y)){
            cout << "Movimiento diagonal invalido" << endl;
            movimiento_jugador(jugador1,jugador2,tablero,sz);
        } else {
            // Verificamos que el movimiento sea valido
            if ((verificador_exitencia_puntos(sz - (sz-1)/2 ,x0,y0,x,y)) && (jugador1->validar_movimiento(tablero,x0,y0,x,y))){
                matriz = jugador1->modificar_matriz(tablero,x0,y0,x,y, w);
                tablero->matriz = matriz;
            } else {
                cout << "Movimiento invalido" << endl;
                movimiento_jugador(jugador1,jugador2,tablero,sz);
            }
        }
    };

// Funcion para verificar si el algun jugador gano un cuadrado en caso de que si se suma 1 al puntaje del jugador
void verificar_cuadrado(jugador *jugador1,jugador *jugador2, tablero *tablero, int sz){
    string **matriz = tablero->matriz;
    string w = jugador1->get_pieza();
    string w2 = jugador2->get_pieza();
    // El punto se gana si se forma un cuadrado con 4 lineas sin importar si las fichas son del mismo jugador o no
    for (int i = 1; i < sz; i+=2){
        for (int j = 1; j < sz; j+=2){
            if (matriz[i][j] == "0"){
                if ((matriz[i-1][j] == w || matriz[i-1][j] == w2) && (matriz[i+1][j] == w || matriz[i+1][j] == w2) && (matriz[i][j-1] == w || matriz[i][j-1] == w2) && (matriz[i][j+1] == w || matriz[i][j+1] == w2)){
                    jugador1->sumar_puntaje();
                    cout << "El jugador " << jugador1->get_username() << " gano un cuadrado" << endl;
                    matriz[i][j] = w;
                    tablero->matriz = matriz;
                }
            }
        }
    }
};

int main(){

    // Bienvenida
    bienvenida();

    // Limpiamos la pantalla
    system("clear");

    int sz = inicializar_tablero();

    // Creamos un objeto tablero
    tablero tablero(sz);

    // Rellenamos la matriz del tablero
    tablero.matriz = tablero.relleno_matriz(tablero.matriz,tablero.sz);

    // Creamos un vector de jugadores
    vector<jugador> jugadores;
    
    // Inicializamos los jugadores
    jugadores.push_back(jugador("Jugador 1","X"));
    jugadores.push_back(jugador("Jugador 2","$"));

    // Movimiento de los jugadores
    int turno = 0;
    do{
        system("clear");
        cout << "Turno de: " << jugadores[turno].get_username() << endl;
        // Mostramos el puntaje de los jugadores
        cout << jugadores[0].get_username() << ": " << jugadores[0].get_puntaje() << " - " << jugadores[1].get_username() << ": " << jugadores[1].get_puntaje() << endl;
        tablero.imprimir_matriz(tablero.matriz,tablero.sz);
        movimiento_jugador(&jugadores[turno],&jugadores[turno==0?1:0],&tablero, sz);
        verificar_cuadrado(&jugadores[turno],&jugadores[turno==0?1:0],&tablero, sz - (sz-1)/2);
        turno = (turno + 1) % 2;
    } while (jugadores[0].get_puntaje() + jugadores[1].get_puntaje() != (sz - (sz-1)/2) * (sz - (sz-1)/2));
    

    // Mostramos el puntaje de los jugadores
    cout << jugadores[0].get_username() << ": " << jugadores[0].get_puntaje();
    cout << " - " << jugadores[1].get_username() << ": " << jugadores[1].get_puntaje() << endl;
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);
    // Mostramos el ganador
    if (jugadores[0].get_puntaje() > jugadores[1].get_puntaje()){
        cout << "El ganador es: " << jugadores[0].get_username() << endl;
    } else if (jugadores[0].get_puntaje() < jugadores[1].get_puntaje()){
        cout << "El ganador es: " << jugadores[1].get_username() << endl;
    } else {
        cout << "Empate" << endl;
    }
};