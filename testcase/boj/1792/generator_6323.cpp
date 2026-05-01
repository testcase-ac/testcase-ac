#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of queries
    int n = rnd.next(10, 20);
    println(n);
    for (int i = 0; i < n; i++) {
        int typ = rnd.next(0, 6);
        int a, b, d;
        switch (typ) {
            case 0: {
                // small a, b
                a = rnd.next(1, 10);
                b = rnd.next(1, 10);
                d = rnd.next(1, min(a, b));
                break;
            }
            case 1: {
                // medium a, b
                a = rnd.next(50, 1000);
                b = rnd.next(50, 1000);
                d = rnd.next(1, min(a, b));
                break;
            }
            case 2: {
                // large a, b
                a = rnd.next(10000, 50000);
                b = rnd.next(10000, 50000);
                d = rnd.next(1, min(a, b));
                break;
            }
            case 3: {
                // special d = 1
                a = rnd.next(1, 50000);
                b = rnd.next(1, 50000);
                d = 1;
                break;
            }
            case 4: {
                // special d close to min(a,b)
                a = rnd.next(1, 50000);
                b = rnd.next(1, 50000);
                {
                    int mn = min(a, b);
                    int lo = mn / 2 + 1;
                    d = rnd.next(lo, mn);
                }
                break;
            }
            case 5: {
                // a == b
                a = rnd.next(1, 50000);
                b = a;
                d = rnd.next(1, a);
                break;
            }
            case 6: {
                // one dimension = 1
                if (rnd.next(0, 1) == 0) {
                    a = 1;
                    b = rnd.next(1, 50000);
                } else {
                    b = 1;
                    a = rnd.next(1, 50000);
                }
                d = rnd.next(1, min(a, b));
                break;
            }
        }
        println(a, b, d);
    }
    return 0;
}
