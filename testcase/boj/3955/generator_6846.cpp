#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 4);
        long long K, C;
        switch (type) {
            // 0: small random pair
            case 0:
                K = rnd.next(2, 20);
                C = rnd.next(2, 20);
                break;
            // 1: guaranteed gcd > 1 => IMPOSSIBLE
            case 1: {
                long long f = rnd.next(2, 10);
                long long m1 = rnd.next(1, 10);
                long long m2 = rnd.next(1, 10);
                K = f * m1;
                C = f * m2;
                break;
            }
            // 2: C == 1 special
            case 2:
                C = 1;
                if (rnd.next(0, 1) == 0)
                    K = rnd.next(2, 20);
                else
                    K = rnd.next(1000000, 1000000000);
                break;
            // 3: K == 1 special
            case 3:
                K = 1;
                if (rnd.next(0, 1) == 0)
                    C = rnd.next(2, 20);
                else
                    C = rnd.next(1000000, 1000000000);
                break;
            // 4: large random coprime
            default:
                K = rnd.next(1000000, 1000000000);
                do {
                    C = rnd.next(1000000, 1000000000);
                } while (std::gcd(K, C) != 1);
                break;
        }
        println(K, C);
    }
    return 0;
}
