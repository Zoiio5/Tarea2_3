#include "FB.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>
#include <fstream>
#include <random>
#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

using namespace std;
using namespace chrono;

int costo_sub(char a, char b) { return (a == b) ? 0 : 2; }
int costo_insertar(char b) { return 1; }
int costo_eliminar(char a) { return 1; }
int costo_trans(char a, char b) { return 1; }


int distanciaMinimaFB(const string &s1, const string &s2, int i, int j) {
    if (i == s1.length()) return (s2.length() - j) * costo_insertar(' ');
    if (j == s2.length()) return (s1.length() - i) * costo_eliminar(' ');

    int costo_min = INT_MAX;
    if (s1[i] == s2[j]) {
        costo_min = distanciaMinimaFB(s1, s2, i + 1, j + 1);
    } else {
        costo_min = costo_sub(s1[i], s2[j]) + distanciaMinimaFB(s1, s2, i + 1, j + 1);
    }

    costo_min = min(costo_min, costo_insertar(s2[j]) + distanciaMinimaFB(s1, s2, i, j + 1));
    costo_min = min(costo_min, costo_eliminar(s1[i]) + distanciaMinimaFB(s1, s2, i + 1, j));

    if (i < s1.length() - 1 && j < s2.length() - 1 && s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
        costo_min = min(costo_min, costo_trans(s1[i], s1[i + 1]) + distanciaMinimaFB(s1, s2, i + 2, j + 2));
    }

    return costo_min;
}


string generarCadena(int longitud) {
    const string caracteres = "abcdefghijklmnopqrstuvwxyz ";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, caracteres.size() - 1);

    string resultado;
    for (int i = 0; i < longitud; ++i) {
        resultado += caracteres[dis(gen)];
    }
    return resultado;
}


string generarPalindromo(int longitud) {
    string mitad = generarCadena(longitud / 2);
    string palindromo = mitad;
    if (longitud % 2 != 0) palindromo += mitad[longitud / 2];
    reverse(mitad.begin(), mitad.end());
    palindromo += mitad;
    return palindromo;
}

string generarCaracteresRepetidos(int longitud, char c) {
    return string(longitud, c);
}

string generarTransposicion(string s) {
    if (s.length() > 1) swap(s[0], s[1]);
    return s;
}


size_t obtenerUsoMemoria() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PrivateUsage;
}

int main() {
    ofstream archivo("resultados.csv");
    archivo << "Caso,Tamaño,Tiempo (ms),Memoria Inicial (bytes),Memoria Final (bytes)\n";

    vector<pair<string, string>> casos = {
        {"Aleatorio", generarCadena(10)},
        {"Palindromo", generarPalindromo(10)},
        {"Repetidos", generarCaracteresRepetidos(10, 'a')},
        {"Casi Identico", "kitten"},
        {"Transposicion", generarTransposicion("abdc")}
    };

    for (auto &[tipo, s1] : casos) {
        string s2 = generarCadena(10);

        size_t memoria_inicial = obtenerUsoMemoria();
        auto inicio = high_resolution_clock::now();
        int resultado = distanciaMinimaFB(s1, s2, 0, 0);
        auto fin = high_resolution_clock::now();
        size_t memoria_final = obtenerUsoMemoria();

        auto duracion = duration_cast<milliseconds>(fin - inicio).count();

        cout << "Caso: " << tipo << ", Tiempo: " << duracion << " ms, Memoria Inicial: " << memoria_inicial << " bytes, Memoria Final: " << memoria_final << " bytes, Resultado: " << resultado << endl;
        archivo << tipo << "," << s1.length() << "," << duracion << "," << memoria_inicial << "," << memoria_final << "\n";
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados.csv'." << endl;

    return 0;
}
