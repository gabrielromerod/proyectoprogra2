#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string **punteromatriz; int nfilas, ncolumnas;


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

    cout << "Imprimiendo matriz \n";
    for (int i = 0; i < nfilas; i++){
        for (int j = 0; j < ncolumnas; j++){
            cout << setw(3) << *(*(matriz+i)+j) << setw(3);
        }
        cout << "\n";
    }
}

//Para liberar la memoria
void eliminarmatriz(string** punteromatriz, int nfilas, int ncolumnas){
    for(int i = 0; i < nfilas; i++){
        delete [] punteromatriz[i];
    }
    delete [] punteromatriz;
}

int main(){
    crearmatriz();
    anadirmatriz(nfilas, ncolumnas);
    mostrarmatriz(punteromatriz, nfilas, ncolumnas);
    eliminarmatriz(punteromatriz, nfilas, ncolumnas);
}
