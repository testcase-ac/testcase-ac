#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: weighted between 1 and 10
    int tN = rnd.next(-2, 2); // bias parameter
    int N = rnd.wnext(10, tN) + 1;

    // Probability a person is forced
    double pFixed = rnd.next();

    // Generate constraints: 0 = free, 1 = must A, 2 = must B
    vector<int> cons(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < pFixed) {
            cons[i] = rnd.next(1, 2);
        } else {
            cons[i] = 0;
        }
    }

    // Generate symmetric sadness matrix w[i][j]
    vector<vector<int>> w(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int tW = rnd.next(-3, 3);        // bias weight sampling
            int val = rnd.wnext(1001, tW);   // yields 0..1000
            w[i][j] = w[j][i] = val;
        }
    }

    // Output
    println(N);
    println(cons);
    for (int i = 0; i < N; i++) {
        println(w[i]);
    }

    return 0;
}
