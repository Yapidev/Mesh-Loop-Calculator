#include <stdio.h>
#include <math.h>

#define MAX_LOOP 10

// Fungsi untuk eliminasi Gauss dengan pivoting
void gaussElimination(int n, double a[MAX_LOOP][MAX_LOOP + 1], double result[MAX_LOOP]) {
    for (int i = 0; i < n; i++) {
        // Partial pivoting
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[j][i]) > fabs(a[maxRow][i])) {
                maxRow = j;
            }
        }

        // Tukar baris jika diperlukan
        if (maxRow != i) {
            for (int k = 0; k <= n; k++) {
                double temp = a[i][k];
                a[i][k] = a[maxRow][k];
                a[maxRow][k] = temp;
            }
        }

        // Eliminasi Gauss
        for (int j = i + 1; j < n; j++) {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++) {
                a[j][k] -= factor * a[i][k];
            }
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; i--) {
        result[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            result[i] -= a[i][j] * result[j];
        }
        result[i] /= a[i][i];
    }
}

int main() {
    int n;
    double a[MAX_LOOP][MAX_LOOP + 1];
    double result[MAX_LOOP];

    printf("=== Mesh Loop Calculator ===\n");
    printf("Masukkan jumlah loop: ");
    scanf("%d", &n);

    if (n > MAX_LOOP) {
        printf("Jumlah loop maksimum adalah %d.\n", MAX_LOOP);
        return 1;
    }

    printf("Masukkan koefisien persamaan untuk masing-masing loop.\n");
    printf("Format input: R11 R12 ... R1n V1 (untuk persamaan pertama)\n");

    for (int i = 0; i < n; i++) {
        printf("Persamaan loop %d: ", i + 1);
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    gaussElimination(n, a, result);

    printf("\nHasil arus (I) untuk setiap loop:\n");
    for (int i = 0; i < n; i++) {
        printf("I%d = %.2lf A\n", i + 1, result[i]);
    }

    return 0;
}
