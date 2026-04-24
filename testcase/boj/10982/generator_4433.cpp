#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 2);
    println(T);
    int Nmax = (T == 1 ? 7 : 4);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, Nmax);
        println(N);

        // Hyper-parameters for this case
        bool equal_times = (rnd.next(0, 4) == 0); // ~20% all a_i == b_i
        int maxT = (rnd.next(0, 1) == 0 ? 10 : 100);
        int bias = rnd.next(0, 2); // 0=no bias, 1=prefer oven1 slow, 2=prefer oven2 slow

        for (int i = 0; i < N; ++i) {
            int a, b;
            if (equal_times) {
                a = b = rnd.next(1, maxT);
            } else if (bias == 0) {
                a = rnd.next(1, maxT);
                b = rnd.next(1, maxT);
            } else if (bias == 1) {
                b = rnd.next(1, max(1, maxT / 4));
                a = rnd.next(b, maxT);
            } else {
                a = rnd.next(1, max(1, maxT / 4));
                b = rnd.next(a, maxT);
            }
            println(a, b);
        }
    }

    return 0;
}
