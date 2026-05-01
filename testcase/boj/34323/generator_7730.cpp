#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);
    int N, M;
    int S;
    switch (scenario) {
        case 0:
            // No percentage discount
            N = 0;
            M = rnd.next(0, 100);
            S = rnd.next(100, 1000);
            break;
        case 1:
            // Full percentage discount
            N = 100;
            M = rnd.next(0, 100);
            S = rnd.next(100, 1000);
            break;
        case 2:
            // No M+1 discount (M = 0)
            M = 0;
            N = rnd.next(0, 100);
            S = rnd.next(100, 100000000);
            break;
        case 3:
            // Max M+1 discount (M = 100)
            M = 100;
            N = rnd.next(0, 100);
            S = rnd.next(100, 100000000);
            break;
        default:
            // Force a case where decimal truncation matters
            do {
                N = rnd.next(1, 99);
                M = rnd.next(1, 99);
                S = rnd.next(101, 999);
            } while (((long long)(M + 1) * S * (100 - N)) % 100 == 0);
            break;
    }

    println(N, M, S);
    return 0;
}
