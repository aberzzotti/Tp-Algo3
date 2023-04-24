//Librerias
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Definición de una actividad
struct Actividad {
    int64_t s;   // Momento inicial
    int64_t t;   // Momento final
    int64_t orden; //Numero de orden de llegada
};
//Variables Globales
vector<Actividad> vectorAct;
vector<int64_t> res;
//++++++++++++++++++++++++++++++++++++++++++++
bool comparacion(const Actividad& a, const Actividad& b) {
    return a.t < b.t;
}
// Funcion principal
void ejercicio3() {
    // Ordenar las actividades por momento t
    int ultimoT = 0; // Momento t de la última actividad seleccionada, recordar que estan ordenadas por t, lo cual hace que tambien sea la mayor
    // Iterar sobre las actividades
    for (int64_t i = 0; i < vectorAct.size(); i++) {
        if (vectorAct[i].t >= ultimoT && vectorAct[i].s>=ultimoT) {
            // La actividad actual no se solapa con las actividades ya seleccionadas, por lo tanto la inserto a mi respuesta
            res.push_back(vectorAct[i].orden);
            ultimoT = vectorAct[i].t; //Actualizo mi ultimo momento t
        }
    }
    cout << res.size() << endl;
    //Imprimo resultado
    for (int64_t i = 0; i <res.size() ; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;
}
int64_t Ubicacion(int64_t t){
    if(t<vectorAct[0].t){
        return 0;
    }
    if(t>vectorAct[vectorAct.size()-1].t){
        return vectorAct.size();
    }
    for (int i = 0; i <vectorAct.size() ; ++i) {
        if(vectorAct[i].t>t) return i;
    }
}

int main() {
    // Cantidad de tuplas que representan las actividades
    int64_t n; cin >> n;
    Actividad actividadActual;
    for(int64_t i = 0; i < n; i ++){
        // Guardo la actividad
        int64_t s, t; cin >> s >>t;
        actividadActual.s = s;
        actividadActual.t = t;
        actividadActual.orden = i+1;
        vectorAct.push_back(actividadActual);
    }
    sort(vectorAct.begin(),vectorAct.end(), comparacion);
    ejercicio3();
    return 0;
}
