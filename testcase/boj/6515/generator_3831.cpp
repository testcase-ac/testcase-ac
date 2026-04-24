#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);

    for (int tc = 0; tc < T; tc++) {
        // Small sequence length and queries
        int n = rnd.next(1, 10);
        int q = rnd.next(1, 20);

        // Number of distinct values
        int d = rnd.next(1, n);

        // Choose d unique values in [-10,10], sorted
        vector<int> pool;
        for (int v = -10; v <= 10; v++) pool.push_back(v);
        shuffle(pool.begin(), pool.end());
        pool.resize(d);
        sort(pool.begin(), pool.end());

        // Random composition of n into d positive parts
        vector<int> cuts;
        cuts.push_back(0);
        cuts.push_back(n);
        for (int i = 0; i < d - 1; i++) {
            cuts.push_back(rnd.next(1, n - 1));
        }
        sort(cuts.begin(), cuts.end());
        vector<int> block;
        for (int i = 0; i + 1 < (int)cuts.size(); i++) {
            block.push_back(cuts[i+1] - cuts[i]);
        }

        // Build the sorted array a of length n
        vector<int> a;
        for (int i = 0; i < d; i++) {
            for (int cnt = 0; cnt < block[i]; cnt++) {
                a.push_back(pool[i]);
            }
        }

        // Generate queries with varied lengths
        vector<pair<int,int>> queries;
        for (int i = 0; i < q; i++) {
            int typ = rnd.next(0, 2);
            int L;
            if (typ == 0) {
                // small length
                L = rnd.next(1, min(2, n));
            } else if (typ == 1) {
                // medium length
                L = rnd.next(1, max(1, n / 2));
            } else {
                // large length
                L = rnd.next(1, n);
            }
            int start = rnd.next(1, n - L + 1);
            int end = start + L - 1;
            queries.emplace_back(start, end);
        }

        // Output this test case
        println(n, q);
        println(a);
        for (auto &qr : queries) {
            println(qr.first, qr.second);
        }
    }

    // Terminate input
    println(0);
    return 0;
}
