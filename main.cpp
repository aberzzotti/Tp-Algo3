//Librerias
#include <vector>
#include <iostream>

using namespace std;
//----------VARIABLES GLOBALES-----------
vector<int64_t> vn;
vector<int64_t> vr;
vector<int64_t> vm;
vector<vector<int64_t>> vv;
//------------------------------------------
//Funcion sacada del taller 1  ejercicio 0
int64_t mod_bin_exp(int64_t x, int64_t y, int64_t n) {
    //Caso base
    if(y ==0){
        return 1;
    }else if (y%2==0){
        return (mod_bin_exp(x,y/2,n)*mod_bin_exp(x,y/2,n))%n;
    }else{
        return (((mod_bin_exp(x,y/2,n)*mod_bin_exp(x,y/2,n))%n)*x)%n;
    }
}
//--------------------------------------------------------
bool ejercicio2(vector<int64_t>& v, int64_t m, int64_t r, int64_t n) {// Uso bottom up
    vector<vector<bool>> dp(n, vector<bool>(m, false)); // DP es la matriz con la cual hago Dynamic Programming, los inicializo en false
    dp[0][v[0] % m] = true;
    for (int64_t i = 1; i < n; i++) {
        for (int64_t j = 0; j < m; j++) {
            for (char op : {'+', '-', '*', '^'}) {
                int64_t val = 0; //Inicializo el valor en 0 y pruebo todas las posibilidades
                if (op == '+') {//OPERACION SUMA
                    val = (j + v[i]) % m;
                } else if (op == '-') {//OPERACION RESTA
                    val = (j - v[i] + m) % m;
                } else if (op == '*') {//OPERACION MULTIPLICACION
                    val = (j * v[i]) % m;
                } else if (op == '^') {//OPERACION POTENCIA
                    val = mod_bin_exp(j,v[i],m);
                }
                dp[i][val] = dp[i][val] || dp[i - 1][j];
            }
        }
    }
    return dp[n - 1][r];
}
//-----------------------------------------------------
int main() {
    int64_t c; cin >> c;
    int64_t f = 0;
    for (int64_t j = 0; j < c; ++j) {
        int n, r, m; cin >> n >> r >> m;
        vn.push_back(n);
        vr.push_back(r);
        vm.push_back(m);
        vector<int64_t> v(n);
        for (int64_t i = 0; i < n ; ++i) {
            cin >> v[i];
        }
        vv.push_back(v);
    }
    for(int64_t h = 0; h < c; ++h){
        f = 0;
        if (ejercicio2(vv[h], vm[h], vr[h], vn[h])) {//Si devuelvo true imprimo SI
            cout << "Si" << endl;
            f = 1;
        }
        if(f==0){
            cout << "No" << endl;//SINO IMPRIMO NO
        }
    }
    return 0;
}
