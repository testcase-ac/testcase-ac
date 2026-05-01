#include "testlib.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of queries: small or medium
    int M;
    if (rnd.next(0, 1) == 0) M = rnd.next(5, 15);
    else M = rnd.next(16, 50);

    map<int,int> cnt;
    cnt[0] = 1;               // initial zero in A
    vector<int> keys;         // track positive elements in A
    bool usedQ = false;       // ensure at least one type-3 query

    println(M);
    for (int i = 1; i <= M; i++) {
        int tp;
        // Force a query if none used yet at last step
        if (i == M && !usedQ) {
            tp = 3;
        } else {
            // pick operation with simple weights
            while (true) {
                double p = rnd.next();
                if (p < 0.4) tp = 1;
                else if (p < 0.7) tp = 2;
                else tp = 3;
                if (tp == 2 && keys.empty()) continue; // cannot delete if no positive keys
                break;
            }
        }

        if (tp == 1) {
            // Insert x with varied distributions
            int distType = rnd.next(0, 2);
            int x;
            if (distType == 0) {
                x = rnd.next(1, 100);
            } else if (distType == 1) {
                int t = rnd.next(-1, 1);
                x = rnd.wnext(1000000000, t) + 1;
            } else {
                x = rnd.any(vector<int>{1, 2, 4, 8, 16, 32, 64, 128});
            }
            cnt[x]++;
            if (cnt[x] == 1) keys.push_back(x);
            println(1, x);
        }
        else if (tp == 2) {
            // Delete one occurrence of a positive x
            int idx = rnd.next((int)keys.size());
            int x = keys[idx];
            cnt[x]--;
            if (cnt[x] == 0) {
                keys.erase(keys.begin() + idx);
            }
            println(2, x);
        }
        else {
            // Query max XOR with x
            int distType = rnd.next(0, 1);
            int x;
            if (distType == 0) {
                x = rnd.next(1, 100);
            } else {
                int t = rnd.next(-1, 1);
                x = rnd.wnext(1000000000, t) + 1;
            }
            println(3, x);
            usedQ = true;
        }
    }

    return 0;
}
