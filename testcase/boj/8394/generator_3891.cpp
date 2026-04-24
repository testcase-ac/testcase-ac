#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXN = 10000000;
    int type = rnd.next(0, 3);
    int n;
    switch (type) {
        case 0:
            // smallest boundary
            n = 1;
            break;
        case 1:
            // small n for hand-checking
            n = rnd.next(2, 20);
            break;
        case 2: {
            // near Fibonacci mod-10 period (60)
            int kmax = MAXN / 60;
            int k = rnd.next(0, kmax);
            int r = rnd.next(0, 59);
            long long tmp = 1LL * k * 60 + r + 1;
            if (tmp > MAXN) tmp = MAXN;
            n = int(tmp);
            break;
        }
        default:
            // fully random in range
            n = rnd.next(1, MAXN);
    }

    println(n);
    return 0;
}
