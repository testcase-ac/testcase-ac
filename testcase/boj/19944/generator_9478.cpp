#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 3, M = 1;

    int pattern = rnd.next(1, 10);

    switch (pattern) {
        case 1:
            // Minimum N, NEWBIE (year 1)
            N = 3; M = 1;
            break;
        case 2:
            // Minimum N, NEWBIE (year 2)
            N = 3; M = 2;
            break;
        case 3:
            // Minimum N, OLDBIE boundary (M == N)
            N = 3; M = 3;
            break;
        case 4:
            // Maximum N, NEWBIE (year 1)
            N = 1000; M = 1;
            break;
        case 5:
            // Maximum N, NEWBIE (year 2)
            N = 1000; M = 2;
            break;
        case 6:
            // Maximum N, OLDBIE boundary (M == N == 1000)
            N = 1000; M = 1000;
            break;
        case 7:
            // Random OLDBIE: 3 <= M <= N
            N = rnd.next(3, 1000);
            if (N == 3) {
                M = 3;
            } else {
                M = rnd.next(3, N);
            }
            break;
        case 8:
            // TLE with M just greater than N
            N = rnd.next(3, 999);
            M = rnd.next(N + 1, 1000);
            break;
        case 9:
            // Small N, very large M -> clear TLE
            N = rnd.next(3, 10);
            M = 1000;
            break;
        case 10: {
            // Random category with N allowing all three types
            N = rnd.next(3, 999);
            int cat = rnd.next(0, 2); // 0: NEWBIE, 1: OLDBIE, 2: TLE
            if (cat == 0) {
                // NEWBIE: M = 1 or 2
                M = rnd.next(1, 2);
            } else if (cat == 1) {
                // OLDBIE: 3 <= M <= N
                if (N == 3) M = 3;
                else M = rnd.next(3, N);
            } else {
                // TLE: M > N
                M = rnd.next(N + 1, 1000);
            }
            break;
        }
    }

    println(N, M);

    return 0;
}
