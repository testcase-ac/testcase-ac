#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(2, 10);
        println(N);
        int pattern = rnd.next(0, 4);
        vector<int> a(N);
        if (pattern == 0) {
            // Fully random with zeros and negatives
            double p0 = rnd.next(0.0, 1.0);
            double pneg = rnd.next(0.0, 1.0);
            vector<int> nz = {1, 2};
            for (int i = 0; i < N; i++) {
                double r = rnd.next();
                if (r < p0) {
                    a[i] = 0;
                } else {
                    int v = rnd.any(nz);
                    if (rnd.next() < pneg) v = -v;
                    a[i] = v;
                }
            }
        } else if (pattern == 1) {
            // All positives 1 or 2
            for (int i = 0; i < N; i++) {
                a[i] = rnd.next(1, 2);
            }
        } else if (pattern == 2) {
            // All negatives -1 or -2
            for (int i = 0; i < N; i++) {
                a[i] = -rnd.next(1, 2);
            }
        } else if (pattern == 3) {
            // Alternating sign with 1 or 2
            for (int i = 0; i < N; i++) {
                int v = rnd.next(1, 2);
                a[i] = (i % 2 == 0 ? v : -v);
            }
        } else {
            // Mostly zeros with some non-zeros
            vector<int> nz = {-2, -1, 1, 2};
            for (int i = 0; i < N; i++) {
                if (rnd.next() < 0.7) {
                    a[i] = 0;
                } else {
                    a[i] = rnd.any(nz);
                }
            }
        }
        println(a);
    }

    return 0;
}
