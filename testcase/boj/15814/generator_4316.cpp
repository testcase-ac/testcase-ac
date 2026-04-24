#include "testlib.h"
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: string length
    int n = rnd.next(1, 10);

    // Hyper-parameter: character pool type
    int type = rnd.next(0, 4);
    string pool;
    if (type == 0) {
        // lowercase only
        pool = "abcdefghijklmnopqrstuvwxyz";
    } else if (type == 1) {
        // uppercase only
        pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else if (type == 2) {
        // lowercase and hyphen
        pool = "abcdefghijklmnopqrstuvwxyz-";
    } else if (type == 3) {
        // uppercase and hyphen
        pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ-";
    } else {
        // full mix
        pool = "abcdefghijklmnopqrstuvwxyz"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ-";
    }

    // Build the string S
    string S;
    S.reserve(n);
    for (int i = 0; i < n; i++) {
        S.push_back(rnd.any(pool));
    }

    // Hyper-parameter: number of swaps T
    bool useLargeT = (rnd.next(0, 3) == 0);
    int maxSmall = max(1, min(10, n * 3));
    int maxLarge = max(1, min(50, n * 5));
    int T = useLargeT ? rnd.next(1, maxLarge) : rnd.next(1, maxSmall);

    // Output
    println(S);
    println(T);
    for (int i = 0; i < T; i++) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        println(a, b);
    }
    return 0;
}
