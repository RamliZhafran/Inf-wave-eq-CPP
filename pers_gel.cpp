#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Konstanta dan parameter
double pi = M_PI;
double dx = 0.1;
double dt = 0.05;
double c = 2.0;         // Karena c^2 = 4
int Nx = 11;            // Jumlah titik di x (0 sampai 1, step 0.1)
int Nt = 11;            // t dari 0-0.5 dgn step 0.05
const double r = (c * dt / dx) * (c * dt / dx);  // rasio stabilitas = 1

int main() {
    // Matriks solusi u[i][j] → i = posisi x, j = waktu t
    vector<vector<double>> u(Nx, vector<double>(Nt, 0.0));

    // Inisialisasi kondisi awal u(x,0)
    for (int i = 0; i < Nx; ++i) {
        double x = i * dx;
        u[i][0] = sin(pi * x) + sin(2 * pi * x);
    }

    // Inisialisasi untuk waktu ke-1 (j = 1) menggunakan rumus:
    for (int i = 1; i < Nx - 1; ++i) {
        u[i][1] = 0.5 * (u[i - 1][0] + u[i + 1][0]);  // karena u_t(x,0) = 0
    }

    // Iterasi finite difference untuk j >= 2
    for (int j = 1; j < Nt - 1; ++j) {
        for (int i = 1; i < Nx - 1; ++i) {
            u[i][j + 1] = r * (u[i + 1][j] + u[i - 1][j]) + 2 * (1 - r) * u[i][j] - u[i][j - 1];
        }
    }

    // Print hasil
    cout << fixed << setprecision(6);
    cout << "Solusi u(x,t):\n";
    for (int j = 0; j < Nt; ++j) {
        cout << "t = " << j * dt << ": ";
        for (int i = 0; i < Nx; ++i) {
            cout << setw(8) << u[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
