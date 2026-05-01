#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias towards small/medium sizes
    int bucket = rnd.next(0, 9);
    int N;
    if (bucket == 0) {
        N = 1;
    } else if (bucket <= 3) {
        N = rnd.next(2, 3);
    } else if (bucket <= 6) {
        N = rnd.next(4, 6);
    } else {
        N = rnd.next(7, 10);
    }

    int mafia = rnd.next(0, N - 1);

    // Generate guilt values with different patterns
    int scenario = rnd.next(0, 4);
    vector<int> guilt(N);

    if (scenario == 0) {
        // All equal guilt (tie-breaking on index)
        int val = rnd.next(350, 750);
        for (int i = 0; i < N; i++) guilt[i] = val;
    } else if (scenario == 1) {
        // Strictly increasing by index
        for (int i = 0; i < N; i++) {
            guilt[i] = 300 + 30 * i; // stays within [300, 570] for N <= 10
        }
    } else if (scenario == 2) {
        // Mafia has extreme guilt (very high or very low)
        for (int i = 0; i < N; i++) {
            int base = rnd.next(400, 600);
            int delta = rnd.next(-20, 20);
            int g = base + delta;
            if (g < 300) g = 300;
            if (g > 800) g = 800;
            guilt[i] = g;
        }
        if (rnd.next(0, 1) == 0)
            guilt[mafia] = 300;
        else
            guilt[mafia] = 800;
    } else if (scenario == 3) {
        // Fully random guilt values
        for (int i = 0; i < N; i++) {
            guilt[i] = rnd.next(300, 800);
        }
    } else { // scenario == 4
        // Two groups: low-guilt and high-guilt
        int split = N / 2;
        for (int i = 0; i < N; i++) {
            if (i < split)
                guilt[i] = rnd.next(300, 400);
            else
                guilt[i] = rnd.next(700, 800);
        }
    }

    // Generate R matrix with several structural patterns
    int Rpattern = rnd.next(0, 3);
    vector<vector<int>> R(N, vector<int>(N));

    if (Rpattern == 0) {
        // Symmetric small integers
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                int val;
                do {
                    val = rnd.next(-5, 5);
                } while (val == 0);
                R[i][j] = val;
                R[j][i] = val;
            }
        }
    } else if (Rpattern == 1) {
        // Fully random in [-26, -1] U [1, 26]
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int val;
                do {
                    val = rnd.next(-26, 26);
                } while (val == 0);
                R[i][j] = val;
            }
        }
    } else if (Rpattern == 2) {
        // Each row has constant value with random sign/magnitude
        for (int i = 0; i < N; i++) {
            int sign = (rnd.next(0, 1) == 0 ? -1 : 1);
            int mag = rnd.next(1, 26);
            int val = sign * mag;
            for (int j = 0; j < N; j++) {
                R[i][j] = val;
            }
        }
    } else { // Rpattern == 3
        // Cyclic patterned matrix
        vector<int> P = {1, 4, 3, -2, 5, -3, 2, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10, 11, -11};
        int L = (int)P.size();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                R[i][j] = P[(i + j) % L];
            }
        }
    }

    // Output
    println(N);
    println(guilt);
    for (int i = 0; i < N; i++) {
        println(R[i]);
    }
    println(mafia);

    return 0;
}
