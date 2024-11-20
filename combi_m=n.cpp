#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>
#include <fstream>
#include <random>

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

int main() {
    ofstream archivo("resultados_m=n.csv");
    archivo << "Caso,Tamaño,TiempoFB (ns),Resultado FB,TiempoDP (ns),Resultado DP\n";

    vector<string> tipos = {"Aleatorio", "Palindromo", "Repetidos", "Casi Identico", "Transposicion"};

    for (int n = 0; n <= 12; ++n) {
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
            } else if (tipo == "Casi Identico") {
                s1 = string("kitten").substr(0, min(n, 6));
                s2 = string("sitten").substr(0, min(n, 6));
            } else if (tipo == "Transposicion") {
                s1 = generarCadena(n);
                s2 = generarTransposicion(s1);
            }

            auto inicio_fb = high_resolution_clock::now();
            int resultado_fb = distanciaMinimaFB(s1, s2, 0, 0);
            auto fin_fb = high_resolution_clock::now();
            auto duracion_fb = duration_cast<nanoseconds>(fin_fb - inicio_fb).count();


            auto inicio_dp = high_resolution_clock::now();
            int resultado_dp = distanciaMinimaDP(s1, s2);
            auto fin_dp = high_resolution_clock::now();
            auto duracion_dp = duration_cast<nanoseconds>(fin_dp - inicio_dp).count();

            cout << "Caso: " << tipo << ", Tamaño: " << n
                 << ", TiempoFB: " << duracion_fb << " ns, Resultado FB: " << resultado_fb
                 << ", TiempoDP: " << duracion_dp << " ns, Resultado DP: " << resultado_dp << endl;

            archivo << tipo << "," << n << "," << duracion_fb << "," << resultado_fb << ","
                    << duracion_dp << "," << resultado_dp << "\n";
        }
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados_m=n.csv'." << endl;

    return 0;
}
