#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 10);

    // Hyper-parameters for cost distribution
    int lowB = rnd.next(1, 50);
    int highB = rnd.next(lowB + 1, 100);
    double pLow = rnd.next(); // probability to pick a low cost

    // Build symmetric distance matrix
    vector<vector<int>> dist(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int c;
            if (rnd.next() < pLow) {
                c = rnd.next(1, lowB);
            } else {
                c = rnd.next(lowB + 1, highB);
            }
            dist[i][j] = dist[j][i] = c;
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(dist[i]);
    }

    return 0;
}
