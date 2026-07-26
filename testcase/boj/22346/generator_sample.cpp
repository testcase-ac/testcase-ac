#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<long long> choices = {
        1, 2, 3, 4, 5, 7, 8, 13, 31, 32, 63, 1000000000000000000LL
    };
    long long n = rnd.any(choices);
    long long length = 1;
    for (long long x = n; x > 1; x /= 2) {
        length = length * 2 + 1;
    }

    int q = rnd.next(1, 12);
    println(n, q);
    for (int query = 0; query < q; ++query) {
        long long i;
        long long j;
        switch (query % 5) {
            case 0:
                i = 1;
                j = length;
                break;
            case 1:
                i = j = rnd.next(1LL, length);
                break;
            case 2:
                i = 1;
                j = rnd.next(1LL, length);
                break;
            case 3:
                i = rnd.next(1LL, length);
                j = length;
                break;
            default:
                i = rnd.next(1LL, length);
                j = rnd.next(i, length);
        }
        int k = query % 3 == 0 ? 0 : rnd.next(0, 10);
        println(i, j, k);
    }
}
