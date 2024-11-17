#include "PD.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;
using namespace chrono;

int costo_sub(char a, char b) { return (a == b) ? 0 : 2; }
int costo_ins(char b) { return 1; }
int costo_del(char a) { return 1; }
int costo_trans(char a, char b) { return 1; }


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
    if (longitud % 2 != 0) palindromo += generarCadena(1);
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


template<typename Func>
long long medirTiempo(Func funcion, const string &s1, const string &s2) {
    auto inicio = high_resolution_clock::now();
    funcion(s1, s2);
    auto fin = high_resolution_clock::now();
    return duration_cast<microseconds>(fin - inicio).count();
}


int distanciaMinimaDP(const string &s1, const string &s2, size_t &memoriaTotalUsada) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    memoriaTotalUsada = 0;

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) dp[i][j] = j * costo_ins(' ');
            else if (j == 0) dp[i][j] = i * costo_del(' ');
            else {
                int costoSustitucion = dp[i - 1][j - 1] + costo_sub(s1[i - 1], s2[j - 1]);
                int costoInsercion = dp[i][j - 1] + costo_ins(s2[j - 1]);
                int costoEliminacion = dp[i - 1][j] + costo_del(s1[i - 1]);

                dp[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion});

                if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costo_trans(s1[i - 1], s2[j - 1]));
                }
            }

            memoriaTotalUsada += sizeof(dp[i][j]);
        }
    }
    return dp[m][n];
}

int main() {
    ofstream archivo("resultados_dp.csv");
    archivo << "Caso,Tamaño,TiempoDP (µs),MemoriaTotal (bytes)\n";

    vector<string> tipos = {"Aleatorio", "Palindromo", "Repetidos", "Casi Idéntico", "Transposicion"};

    for (int n = 0; n <= 10; ++n) {
        for (const auto &tipo : tipos) {
            string s1, s2;
            if (tipo == "Aleatorio") {
                s1 = generarCadena(n);
                s2 = generarCadena(n);
            } else if (tipo == "Palindromo") {
                s1 = generarPalindromo(n);
                s2 = generarPalindromo(n);
            } else if (tipo == "Repetidos") {
                s1 = generarCaracteresRepetidos(n, 'a');
                s2 = generarCaracteresRepetidos(n, 'a');
            } else if (tipo == "Casi Idéntico") {
                s1 = string("kitten").substr(0, min(n, 6));
                s2 = string("sitten").substr(0, min(n, 6));
            } else if (tipo == "Transposicion") {
                s1 = generarCadena(n);
                s2 = generarTransposicion(s1);
            }

            size_t memoriaTotalUsada = 0;
            long long tiempoDP = medirTiempo([&](const string &a, const string &b) {
                return distanciaMinimaDP(a, b, memoriaTotalUsada);
            }, s1, s2);

            cout << "Caso: " << tipo << ", Tamaño: " << n
                 << ", TiempoDP: " << tiempoDP << " µs, MemoriaTotal: " << memoriaTotalUsada << " bytes" << endl;
            archivo << tipo << "," << n << "," << tiempoDP << "," << memoriaTotalUsada << "\n";
        }
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados_dp.csv'." << endl;
    return 0;
}
