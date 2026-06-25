#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> factorial(21, 1);
    for (int i = 1; i <= 20; ++i) {
        factorial[i] = factorial[i - 1] * i;
    }

    vector<int> boundaryN = {1, 2, 3, 5, 10, 20};
    int n = rnd.next() < 0.45 ? rnd.any(boundaryN) : rnd.next(1, 20);
    int k = rnd.next(4, 18);

    println(n, k);

    vector<int> ascending(n), descending(n);
    iota(ascending.begin(), ascending.end(), 1);
    descending = ascending;
    reverse(descending.begin(), descending.end());

    for (int query = 0; query < k; ++query) {
        bool askRank = rnd.next(2) == 0;
        if (query == 0 || query == 1) {
            askRank = query == 1;
        }

        if (!askRank) {
            println("P");

            int mode = rnd.next(5);
            long long rank;
            if (mode == 0) {
                rank = 1;
            } else if (mode == 1) {
                rank = factorial[n];
            } else if (mode == 2) {
                rank = (factorial[n] + 1) / 2;
            } else {
                rank = rnd.next(1LL, factorial[n]);
            }
            println(rank);
            continue;
        }

        println("Q");

        vector<int> perm = ascending;
        int mode = rnd.next(5);
        if (mode == 0) {
            perm = ascending;
        } else if (mode == 1) {
            perm = descending;
        } else if (mode == 2 && n >= 2) {
            swap(perm[n - 2], perm[n - 1]);
        } else {
            shuffle(perm.begin(), perm.end());
        }
        println(perm);
    }

    return 0;
}
