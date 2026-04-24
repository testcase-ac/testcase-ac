#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int n = rnd.next(10, 15);         // number of operations
    int T = rnd.next(3, 10);          // max taste value
    int Cmax = rnd.next(1, 5);        // max candies per update
    double p_retrieve = rnd.next(0.0, 1.0); // probability to retrieve

    map<int, long long> cnt;
    long long tot = 0;
    vector<tuple<int,int,long long>> ops;

    for (int i = 0; i < n; i++) {
        bool do_retrieval = false;
        if (tot > 0 && rnd.next() < p_retrieve) do_retrieval = true;
        if (tot == 0) do_retrieval = false;
        if (do_retrieval) {
            // generate a valid retrieval
            int tr = rnd.next(1, (int)tot);
            ops.emplace_back(1, tr, 0);
            // simulate retrieval to update counts
            long long acc = 0;
            for (auto it = cnt.begin(); it != cnt.end(); ++it) {
                acc += it->second;
                if (acc >= tr) {
                    it->second--;
                    tot--;
                    if (it->second == 0) cnt.erase(it);
                    break;
                }
            }
        } else {
            // generate an update
            int taste = rnd.next(1, T);
            long long exist = cnt.count(taste) ? cnt[taste] : 0;
            bool do_pos = (exist == 0) || rnd.next() < 0.7;
            long long C;
            if (do_pos) {
                C = rnd.next(1, Cmax);
            } else {
                long long mxrm = min<long long>(exist, Cmax);
                C = -rnd.next(1, (int)mxrm);
            }
            // apply
            ops.emplace_back(2, taste, C);
            cnt[taste] += C;
            tot += C;
            if (cnt[taste] == 0) cnt.erase(taste);
        }
    }

    // output
    println(n);
    for (auto &tp : ops) {
        int A = get<0>(tp), B = get<1>(tp);
        long long C = get<2>(tp);
        if (A == 1) {
            println(1, B);
        } else {
            println(2, B, C);
        }
    }
    return 0;
}
