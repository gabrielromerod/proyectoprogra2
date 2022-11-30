#include <iostream>
#include <string>
#include <vector>
#include "tablero_jugador.h"


using namespace std;

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
    // Imprimimos el tablero usando for
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
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
        //system("clear");
        cout << "Turno de: " << jugadores[turno].get_username() << endl;
        // Mostramos el puntaje de los jugadores
        cout << jugadores[0].get_username() << ": " << jugadores[0].get_puntaje() << " - " << jugadores[1].get_username() << ": " << jugadores[1].get_puntaje() << endl;
        //tablero.imprimir_matriz(tablero.matriz,tablero.sz);
        //movimiento_jugador(&jugadores[turno],&jugadores[turno==0?1:0],&tablero, sz);
        verificar_cuadrado(&jugadores[turno],&jugadores[turno==0?1:0],&tablero, sz - (sz-1)/2);
        turno = (turno + 1) % 2;
    } while (jugadores[0].get_puntaje() + jugadores[1].get_puntaje() != (sz - (sz-1)/2) * (sz - (sz-1)/2));
    

    // Mostramos el puntaje de los jugadores
    cout << jugadores[0].get_username() << ": " << jugadores[0].get_puntaje() << " - " << jugadores[1].get_username() << ": " << jugadores[1].get_puntaje() << endl;
    tablero.imprimir_matriz(tablero.matriz,tablero.sz);

    // Mostramos el ganador
    if (jugadores[0].get_puntaje() > jugadores[1].get_puntaje()){
        cout << "El ganador es: " << jugadores[0].get_username() << endl;
    } else if (jugadores[0].get_puntaje() < jugadores[1].get_puntaje()){
        cout << "El ganador es: " << jugadores[1].get_username() << endl;
    } else {
        cout << "Empate" << endl;
    }

    // Limpiamos la memoria
    for (int i = 0; i < sz; i++){
        delete[] tablero.matriz[i];
    }
    delete[] tablero.matriz;

    // Fin del programa
    return 0;
};