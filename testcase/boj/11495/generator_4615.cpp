#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Small grid dimensions
        int n = rnd.next(2, 5);
        int m = rnd.next(2, 5);
        println(n, m);

        // Maximum cell value
        int maxv = rnd.next(5, 20);

        // Choose generation type for diversity
        int type = rnd.next(0, 3);
        double p;
        int v0, v1;
        int stripe;

        for (int i = 0; i < n; i++) {
            vector<int> row(m);
            if (type == 0) {
                // Uniform random
                for (int j = 0; j < m; j++) {
                    row[j] = rnd.next(0, maxv);
                }
            } else if (type == 1) {
                // Many zeros
                p = rnd.next(6, 9) / 10.0;
                for (int j = 0; j < m; j++) {
                    if (rnd.next() < p) row[j] = 0;
                    else row[j] = rnd.next(1, maxv);
                }
            } else if (type == 2) {
                // Many max values
                p = rnd.next(6, 9) / 10.0;
                for (int j = 0; j < m; j++) {
                    if (rnd.next() < p) row[j] = maxv;
                    else row[j] = rnd.next(0, maxv - 1);
                }
            } else {
                // Striped pattern
                bool horizontal = rnd.next(0, 1);
                stripe = horizontal ? rnd.next(1, n) : rnd.next(1, m);
                v0 = rnd.next(0, maxv);
                v1 = rnd.next(0, maxv);
                for (int j = 0; j < m; j++) {
                    int idx = horizontal ? (i / stripe) : (j / stripe);
                    row[j] = (idx % 2 == 0 ? v0 : v1);
                }
            }
            println(row);
        }
    }

    return 0;
}
