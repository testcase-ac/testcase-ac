#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: choose small or medium V
        int V;
        if (rnd.next(2) == 0) {
            V = rnd.next(4, 10);
        } else {
            V = rnd.next(11, 20);
        }
        // For a convex polyhedron:  ceil(3V/2) <= E <= 3V-6
        int minE = (3 * V + 1) / 2;
        int maxE = 3 * V - 6;
        if (minE > maxE) minE = maxE;
        int E = rnd.next(minE, maxE);

        println(V, E);
    }

    return 0;
}
