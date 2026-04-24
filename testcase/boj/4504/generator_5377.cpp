#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int n = rnd.next(1, 999);          // divisor
    int L = rnd.next(1, 10);           // number of queries
    double prob = rnd.next();          // probability of multiple

    // Generate list
    vector<int> a;
    int maxK = 9999 / n;
    for (int i = 0; i < L; i++) {
        if (rnd.next() < prob && maxK >= 1) {
            // generate a multiple of n
            int k = rnd.next(1, maxK);
            a.push_back(n * k);
        } else {
            // generate a non-multiple of n
            int x;
            do {
                x = rnd.next(1, 9999);
            } while (x % n == 0);
            a.push_back(x);
        }
    }
    // Ensure at least one multiple and one non-multiple when possible
    bool hasMult = false, hasNon = false;
    for (int x : a) {
        if (x % n == 0) hasMult = true;
        else hasNon = true;
    }
    if (L >= 2) {
        if (hasMult && !hasNon) {
            // replace last with non-multiple
            int x;
            do {
                x = rnd.next(1, 9999);
            } while (x % n == 0);
            a.back() = x;
        }
        if (hasNon && !hasMult && maxK >= 1) {
            // replace last with multiple
            int k = rnd.next(1, maxK);
            a.back() = n * k;
        }
    }

    // Shuffle for randomness
    shuffle(a.begin(), a.end());

    // Output
    println(n);
    for (int x : a)
        println(x);
    println(0);

    return 0;
}
