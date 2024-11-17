#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <climits>

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

int distanciaMinimaDP(const string &s1, const string &s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) dp[i][j] = j * costo_insertar(' ');
            else if (j == 0) dp[i][j] = i * costo_eliminar(' ');
            else {
                int costoSustitucion = dp[i - 1][j - 1] + costo_sub(s1[i - 1], s2[j - 1]);
                int costoInsercion = dp[i][j - 1] + costo_insertar(s2[j - 1]);
                int costoEliminacion = dp[i - 1][j] + costo_eliminar(s1[i - 1]);

                dp[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion});

                if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costo_trans(s1[i - 1], s2[j - 1]));
                }
            }
        }
    }
    return dp[m][n];
}

// Generador de cadenas aleatorias
string generarCadenaAleatoria(int longitud) {
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


string generarCadenaPalindromo(int longitud) {
    string mitad = generarCadenaAleatoria((longitud + 1) / 2);
    string cadena = mitad + string(mitad.rbegin() + (longitud % 2), mitad.rend());
    return cadena;
}

string generarCadenaRepetidos(int longitud) {
    char c = 'a' + rand() % 26;
    return string(longitud, c);
}

string generarCadenaCasiIdentica(int longitud) {
    string cadena = generarCadenaAleatoria(longitud);
    if (longitud > 1) cadena[longitud - 1] = cadena[0];
    return cadena;
}

string generarCadenaTransposicion(int longitud) {
    string cadena = generarCadenaAleatoria(longitud);
    if (longitud > 1) swap(cadena[0], cadena[1]);
    return cadena;
}

int main() {
    ofstream archivo("resultados_varios_largos.csv");
    archivo << "Caso,Tamaño_m,Tamaño_n,TiempoFB (ns),Resultado FB,TiempoDP (ns),Resultado DP\n";

    vector<string> tipos = {"Aleatorio", "Palindromo", "Repetidos", "Casi Identico", "Transposicion"};
    for (const auto &tipo : tipos) {
        for (int m = 0; m <= 15; ++m) {
            for (int n = 0; n <= 12; ++n) {
                string s1, s2;

                if (tipo == "Aleatorio") {
                    s1 = generarCadenaAleatoria(m);
                    s2 = generarCadenaAleatoria(n);
                } else if (tipo == "Palindromo") {
                    s1 = generarCadenaPalindromo(m);
                    s2 = generarCadenaPalindromo(n);
                } else if (tipo == "Repetidos") {
                    s1 = generarCadenaRepetidos(m);
                    s2 = generarCadenaRepetidos(n);
                } else if (tipo == "Casi Identico") {
                    s1 = generarCadenaCasiIdentica(m);
                    s2 = generarCadenaCasiIdentica(n);
                } else if (tipo == "Transposicion") {
                    s1 = generarCadenaTransposicion(m);
                    s2 = generarCadenaTransposicion(n);
                }

                auto inicioFB = high_resolution_clock::now();
                int resultadoFB = distanciaMinimaFB(s1, s2, 0, 0);
                auto finFB = high_resolution_clock::now();
                auto tiempoFB = duration_cast<nanoseconds>(finFB - inicioFB).count();


                auto inicioDP = high_resolution_clock::now();
                int resultadoDP = distanciaMinimaDP(s1, s2);
                auto finDP = high_resolution_clock::now();
                auto tiempoDP = duration_cast<nanoseconds>(finDP - inicioDP).count();


                archivo << tipo << "," << m << "," << n << ","
                        << tiempoFB << "," << resultadoFB << ","
                        << tiempoDP << "," << resultadoDP << "\n";

                cout << "Caso: " << tipo << ", Tamaño_m: " << m << ", Tamaño_n: " << n
                     << ", TiempoFB: " << tiempoFB << " ns, ResultadoFB: " << resultadoFB
                     << ", TiempoDP: " << tiempoDP << " ns, ResultadoDP: " << resultadoDP << endl;
            }
        }
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados_varios_largos.csv'." << endl;

    return 0;
}
