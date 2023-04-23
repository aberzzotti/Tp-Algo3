//Librerias
#include <iostream>
#include <vector>
//--------------------------
using namespace std;
using matriz = vector<vector<int> >;
int vacia = 0; //defino el 0 para cuando todavia la matriz esta vacia
matriz cuadrado;
vector<pair<int, bool>> NumerosXcolocar;//(numero,puesto o no) false no lo use true si
int numeroMagico;
int n, k;
//Filas
vector<int> filas;
//Columnas
vector<int> columnas;
//Diagonales
vector<int> diagonales = vector<int>(2);


//***************************
void imprimirMatriz() {
    //Imprimo la matriz por filas
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << cuadrado[i][j] << " ";
        }
        cout << endl;
    }
}

//***********************************************
bool esMagica() {
    // ReinciarVariables();
    diagonales[0] = 0;
    diagonales[1] = 0;
    for (int i = 0; i < n; ++i) {
        //Hago la suma de filas columnas y diagonales
        diagonales[0] += cuadrado[i][i];
        diagonales[1] += cuadrado[i][n - 1 - i];
        if (diagonales[0] > numeroMagico || diagonales[0] > numeroMagico)return false;
    }
    if (n == 4) {
        //Caso que es magico n=4
        if (filas[0] == numeroMagico && filas[1] == numeroMagico && filas[2] == numeroMagico &&
            filas[3] == numeroMagico &&
            diagonales[0] == numeroMagico && diagonales[1] == numeroMagico &&
            columnas[0] == numeroMagico && columnas[1] == numeroMagico && columnas[2] == numeroMagico &&
            columnas[3] == numeroMagico) {
            return true;
        } else {
            return false;
        }

    } else {
        //caso magico con n igual 3
        if (filas[0] == numeroMagico && filas[1] == numeroMagico && filas[2] == numeroMagico &&
            diagonales[0] == numeroMagico && diagonales[1] == numeroMagico &&
            columnas[0] == numeroMagico && columnas[1] == numeroMagico && columnas[2] == numeroMagico) {
            return true;
        } else {
            return false;
        }

    }
}


//***********************************************
bool SigueMagico(int i, int j) {
    //ReinciarVariables();
    //Las filas superan al numeroMagico
    if (filas[i] > numeroMagico)return false;
    //Las columnas superan al numero magico
    if (columnas[j] > numeroMagico)return false;
    //Las diagonales superan 15
    //if (diagonales[0] > numeroMagico || diagonales[1] > numeroMagico)return false;
    //Complete la primera fila pero no suma el numero magico
    if (filas[i] != numeroMagico && cuadrado[i][n - 1] != vacia)return false;
    //Complete la primera columna pero no suma el numero magico
    if (columnas[j] != numeroMagico && cuadrado[n - 1][j] != vacia)return false;
    //Completo la diagonal 2 columna y no suma el numero magico
    //if (diagonales[1] != numeroMagico && cuadrado[n -1][0] != vacia)return false;
    return true;
}
//***********************************************

//***********************************************
void AuxCuadrado(int i, int j, int numero) {

    for (int l = 0; l < NumerosXcolocar.size(); ++l) {
        //Pongo el nunero en la posicion
        if (!NumerosXcolocar[l].second) {
            cuadrado[i][j] = NumerosXcolocar[l].first;
            filas[i] += NumerosXcolocar[l].first;
            columnas[j] += NumerosXcolocar[l].first;
            NumerosXcolocar[l].second = true;
            if (i == n - 1 && j == n - 1) {
                if (esMagica()) {
                    k--;
                    if (k == 0) {
                        imprimirMatriz();
                        return;
                    }
                }
            } else {
                if (SigueMagico(i, j)) {//Sigo avanzando en la matriz
                    if (j == n - 1) {
                        //Avanzo de fila
                        AuxCuadrado(i + 1, 0, l + 1);
                    } else {
                        //Avanzo de columna
                        AuxCuadrado(i, j + 1, l + 1);
                    }
                }
            }
            NumerosXcolocar[cuadrado[i][j] - 1].second = false;
            filas[i] -= NumerosXcolocar[cuadrado[i][j] - 1].first;
            columnas[j] -= NumerosXcolocar[cuadrado[i][j] - 1].first;
            cuadrado[i][j] = vacia;
        }


    }
    return;
}

//--------------------------
void ejercicio1() {
    AuxCuadrado(0, 0, 0);


}

//--------------------------
int main() {
    cin >> n >> k;
    cuadrado = matriz(n, vector<int>(n));
    filas = vector<int>(n);
    columnas = vector<int>(n);
    if ((n == 3 && k > 8) || (n == 4 && k > 7040)) {//evito hacer los cuadrados si mi k supera la cantidad posible
        cout << "-1 " << endl;
        return 0;
    } else {
        for (int j = 0; j < n * n; j++) {
            pair<int, bool> valor = make_pair(j + 1, false);
            NumerosXcolocar.push_back(valor);
        }
        //asigno numero magico
        numeroMagico = (n * ((n * n) + 1)) / 2;
        ejercicio1();

    }
    if ((k != 0)) {//evito hacer los cuadrados si mi k supera la cantidad posible
        cout << "-1 " << endl;
    }
    return 0;
}
