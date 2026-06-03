#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> cases;

    if (rnd.next(4) == 0) cases.push_back(1);
    if (rnd.next(4) == 0) cases.push_back(1000000000);

    int t = rnd.next(6, 18);
    while ((int)cases.size() < t) {
        int mode = rnd.next(5);
        long long n = 1;

        if (mode == 0) {
            int digits = rnd.next(1, 8);
            for (int i = 0; i < digits; ++i) n *= rnd.next(2, 9);
        } else if (mode == 1) {
            vector<int> factors = {2, 3, 5, 7};
            int count = rnd.next(1, 18);
            for (int i = 0; i < count; ++i) {
                int f = rnd.any(factors);
                if (n * f > 1000000000LL) break;
                n *= f;
            }
        } else if (mode == 2) {
            vector<int> primes = {11, 13, 17, 19, 23, 29, 31};
            n = rnd.any(primes);
            int scale = rnd.next(1, 2000);
            while (scale-- > 0) {
                int f = rnd.next(2, 9);
                if (n * f > 1000000000LL) break;
                n *= f;
                if (rnd.next(3) == 0) break;
            }
        } else if (mode == 3) {
            n = rnd.next(1, 1000);
        } else {
            n = rnd.next(999000000, 1000000000);
        }

        cases.push_back((int)n);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (int n : cases) println(n);

    return 0;
}
