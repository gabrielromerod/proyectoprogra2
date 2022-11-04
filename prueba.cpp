#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string **punteromatriz; int nfilas, ncolumnas;

void crearmatriz(){
    cout << "num. filas: "; cin >> nfilas; cout << "num. columnas: " ; cin >> ncolumnas;
    nfilas *= 2; nfilas++; ncolumnas *= 2; ncolumnas++;
    punteromatriz = new string*[nfilas]; //reservando memoria para filas
    for(int i = 0; i < nfilas; i++){
        punteromatriz[i] = new string[ncolumnas]; //reservando memoria para columnas
    }
}
void anadirmatriz(int nfilas, int ncolumnas) {
    for (int i = 0; i < nfilas; i++) {
        for (int j = 0; j < ncolumnas; j++) {
            if (i%2 == 0 && j%2 == 0)
                *(*(punteromatriz + i) + j) = '*';
            else if (i%2 == 0 && j%2 != 0)
                *(*(punteromatriz + i) + j) = '-';
            else if (i%2 != 0 && j%2 == 0)
                *(*(punteromatriz + i) + j) = '|';
        }
    }
}

void mostrarmatriz(string** matriz, int nfilas, int ncolumnas){

    cout << "Imprimiendo matriz \n\n";
    for (int i = 0; i < nfilas; i++){
        for (int j = 0; j < ncolumnas; j++){
            cout << *(*(matriz+i)+j) << setw(2);
        }
        cout << "\n";
    }
    cout << endl;
}

//Para liberar la memoria
void eliminarmatriz(string** punteromatriz, int nfilas, int ncolumnas){
    for(int i = 0; i < nfilas; i++){
        delete [] punteromatriz[i];
    }
    delete [] punteromatriz;
}

// Conectar puntos con lineas
void conectar(string** punteromatriz, int nfilas, int ncolumnas){
    int x1, y1, x2, y2;
    cout << "Punto 1: " << endl; cin >> x1 >> y1;
    cout << "Punto 2: " << endl; cin >> x2 >> y2;

    // Verificamos si es que el punto esta dentro de la matriz
    if (x1 > nfilas || x2 > nfilas || y1 > ncolumnas || y2 > ncolumnas){
        cout << "Punto fuera de la matriz" << endl;
        return;
    }

    // Verificamos si es que los puntos son iguales
    if (x1 == x2 && y1 == y2){
        cout << "Puntos iguales" << endl;
        return;
    }

    // Verificamos si es que los puntos estan en la misma fila
    if (x1 == x2){
        if (y1 < y2){
            // El elemento del medio de y1 y y2 es un guion
            for (int i = y1; i <= y2; i++){
                if (i%2 != 0)
                    *(*(punteromatriz + x1) + i) = 'M';
            }
        }
        else{
            for (int i = y2; i <= y1; i++){
                if (i%2 != 0)
                    *(*(punteromatriz + x1) + i) = 'M';
            }
        }
    }

    // Verificamos si es que los puntos estan en la misma columna
    if (y1 == y2){
        if (x1 < x2){
            for (int i = x1; i <= x2; i++){
                *(*(punteromatriz + i) + y1) = '*';
            }
        }
        else{
            for (int i = x2; i <= x1; i++){
                *(*(punteromatriz + i) + y1) = '*';
            }
        }
    }
}

int main(){
    crearmatriz();
    anadirmatriz(nfilas, ncolumnas);
    mostrarmatriz(punteromatriz, nfilas, ncolumnas);
    conectar(punteromatriz, nfilas, ncolumnas);
    mostrarmatriz(punteromatriz, nfilas, ncolumnas);
    eliminarmatriz(punteromatriz, nfilas, ncolumnas);
}
