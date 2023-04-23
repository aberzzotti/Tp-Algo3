//Librerias
#include <iostream>
#include <vector>
//-------------VARIABLES GLOBALES-------------------
using namespace std;
using matriz = vector<vector<int> >;
int vacia = 0; //defino el 0 para cuando todavia la matriz esta vacia
//La variable del cuadrado
matriz cuadrado;
// Vector de tuplas donde tengo los numeros posibles a colocar y si fueron usados o no
vector<pair<int, bool>> NumerosXcolocar;//(numero,T/F) false= no lo use Y true= si
int numeroMagico;
int n, k;
//Suma Filas
vector<int> filas;
//Suma Columnas
vector<int> columnas;
//Suma Diagonales
vector<int> diagonales = vector<int>(2);


//***************************
//Funcion que imprime la matriz en pantalla
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
    diagonales[0] = 0;
    diagonales[1] = 0;
    //Calculo las diagonales
    for (int i = 0; i < n; ++i) {
        //Hago la suma de diagonales
        diagonales[0] += cuadrado[i][i];
        diagonales[1] += cuadrado[i][n - 1 - i];
        //si ya supero el numero magico retorno
        if (diagonales[0] > numeroMagico || diagonales[0] > numeroMagico)return false;
    }
    //Me fijo si toco suma el numero magico
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
    //La fila en la que estoy  supera al numeroMagico
    if (filas[i] > numeroMagico)return false;
    //La columna en la que estoy supera al numero magico
    if (columnas[j] > numeroMagico)return false;
    //Complete la  fila pero no suma el numero magico
    if (filas[i] != numeroMagico && cuadrado[i][n - 1] != vacia)return false;
    //Complete la  columna pero no suma el numero magico
    if (columnas[j] != numeroMagico && cuadrado[n - 1][j] != vacia)return false;
    return true;
}

//***********************************************
void AuxCuadrado(int i, int j, int numero) {
    for (int l = 0; l < NumerosXcolocar.size(); ++l) {
        if (!NumerosXcolocar[l].second) { //Chequeo que el numero no se haya usado
            cuadrado[i][j] = NumerosXcolocar[l].first; // lo pongo en el cuadrado
            filas[i] += NumerosXcolocar[l].first; //Aumento la suma de la fila
            columnas[j] += NumerosXcolocar[l].first;//Aumento la suma de la columna
            NumerosXcolocar[l].second = true;//Marco que use el numero
            if (i == n - 1 && j == n - 1) { //Si estoy en la ultima Posicon de la matriz
                if (esMagica()) {//Chequeo que se magica
                    k--;
                    if (k == 0) { // Veo que haya llegado a la kesima matriz
                        imprimirMatriz();
                        return;
                    }
                }
            } else {
                if (SigueMagico(i, j)) {//Me fijo si sigue siendo magica y sigo avanzando en la matriz
                    if (j == n - 1) {
                        //Avanzo de fila
                        AuxCuadrado(i + 1, 0, l + 1);
                    } else {
                        //Avanzo de columna
                        AuxCuadrado(i, j + 1, l + 1);
                    }
                }
            }
            NumerosXcolocar[cuadrado[i][j] - 1].second = false; //Marco como que ya no se usa el numero
            filas[i] -= NumerosXcolocar[cuadrado[i][j] - 1].first;//Resto el numero a  la suma de las filas
            columnas[j] -= NumerosXcolocar[cuadrado[i][j] - 1].first;//Resto el numero a  la suma de las columnas
            cuadrado[i][j] = vacia;//Vacio la posicion
        }


    }
    return;
}

//--------------------------
void ejercicio1() {
    //Llamo a la funcion que va hacer la recursion
    AuxCuadrado(0, 0, 0);


}

//--------------------------
int main() {
    cin >> n >> k;
    cuadrado = matriz(n, vector<int>(n)); //Inicializo el tamaño de la matriz
    filas = vector<int>(n);//Inicializo el vector de la suma de las filas
    columnas = vector<int>(n);//Inicializo el vector de la suma de las columbas
    if ((n == 3 && k > 8) || (n == 4 && k > 7040)) {//evito hacer los cuadrados si mi k supera la cantidad posible
        cout << "-1 " << endl;
        return 0;
    } else {
        for (int j = 0; j < n * n; j++) { //Asigno al vector de los numeros a colocar , los numeros y que no los use
            pair<int, bool> valor = make_pair(j + 1, false);
            NumerosXcolocar.push_back(valor);
        }
        //calculo el  numero magico
        numeroMagico = (n * ((n * n) + 1)) / 2;
        ejercicio1();

    }
    if ((k != 0)) {//Si termino y no encontre matriz imprimo -1
        cout << "-1 " << endl;
    }
    return 0;
}
