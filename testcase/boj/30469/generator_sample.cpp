#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    const vector<int> reachableEndTens = {
        11, 13, 17, 19, 31, 37, 41, 43, 47, 71, 73, 79, 97
    };
    const vector<int> blockedEndTens = {
        23, 29, 53, 59, 61, 67, 83, 89
    };
    const vector<int> edgeN = {7, 8, 9, 10, 99, 100};

    int mode = rnd.next(0, 4);
    int a = rnd.any(primes);
    int b = rnd.any(primes);
    int n = rnd.next(7, 100);

    if (mode == 0) {
        n = rnd.any(edgeN);
    } else if (mode == 1) {
        b = rnd.any(reachableEndTens);
        n = rnd.next(7, 30);
    } else if (mode == 2) {
        b = rnd.any(blockedEndTens);
        n = rnd.next(7, 30);
    } else if (mode == 3) {
        a = rnd.any(vector<int>{19, 29, 59, 79, 89});
        b = rnd.any(reachableEndTens);
    } else {
        n = rnd.next(80, 100);
    }

    println(a, b, n);
    return 0;
}
