#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(5, 30);
        int k = rnd.next(1, 10);
        int l = rnd.next(1, 10);
        println(n, k, l);

        // Generate k ships
        for (int i = 0; i < k; i++) {
            int orient = rnd.next(-1, 1);
            int x1, y1, x2, y2;
            if (orient == 0) {
                // horizontal
                y1 = rnd.next(1, n);
                x1 = rnd.next(1, n);
                do {
                    x2 = rnd.next(1, n);
                } while (x2 == x1);
                y2 = y1;
            } else if (orient == 1) {
                // vertical
                x1 = rnd.next(1, n);
                y1 = rnd.next(1, n);
                do {
                    y2 = rnd.next(1, n);
                } while (y2 == y1);
                x2 = x1;
            } else {
                // diagonal
                do {
                    x1 = rnd.next(1, n);
                    y1 = rnd.next(1, n);
                    x2 = rnd.next(1, n);
                    y2 = rnd.next(1, n);
                } while (x1 == x2 || y1 == y2);
            }
            int w = rnd.next(1, 100);
            println(x1, y1, x2, y2, w);
        }

        // Generate l queries with bias
        int bias = rnd.next(-2, 2);
        double p = (bias > 0 ? 0.7 : (bias < 0 ? 0.3 : 0.5));
        for (int i = 0; i < l; i++) {
            int b = (rnd.next() < p ? 0 : 1);
            int a = rnd.next(1, n);
            println(a, b);
        }
    }
    return 0;
}
