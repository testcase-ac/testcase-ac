#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters for variability
    int n = rnd.next(1, 10);              // number of days
    int m = rnd.next(1, 10);              // number of members
    int p = rnd.next(1, n);               // min work days
    int p2 = rnd.next(p, n);              // max work days

    // Day requirements
    vector<pair<int,int>> qr(n);
    for (int i = 0; i < n; i++) {
        int ql = rnd.next(1, m);
        int qr2 = rnd.next(ql, m);
        qr[i] = {ql, qr2};
    }

    // Member vacation plans
    vector<vector<int>> plans(m);
    for (int j = 0; j < m; j++) {
        int maxK = min(3, n);
        int k = rnd.next(0, maxK);
        // build candidate intervals up to length 4
        vector<pair<int,int>> cand;
        int maxLen = min(n, 4);
        for (int len = 1; len <= maxLen; len++) {
            for (int s = 1; s + len - 1 <= n; s++)
                cand.emplace_back(s, s + len - 1);
        }
        shuffle(cand.begin(), cand.end());
        vector<pair<int,int>> sel;
        for (auto &iv : cand) {
            if ((int)sel.size() >= k) break;
            bool ok = true;
            for (auto &ex : sel) {
                if (!(iv.second < ex.first || iv.first > ex.second)) {
                    ok = false; break;
                }
            }
            if (ok) sel.push_back(iv);
        }
        // actual k may be less
        k = sel.size();
        // sort by start
        sort(sel.begin(), sel.end());
        // build plan line
        vector<int> line;
        line.push_back(k);
        for (auto &iv : sel) {
            int len = iv.second - iv.first + 1;
            int d = rnd.next(1, len);
            line.push_back(d);
            line.push_back(iv.first);
            line.push_back(iv.second);
        }
        plans[j] = line;
    }

    // Output input
    println(m, n, p, p2);
    for (int i = 0; i < n; i++) {
        println(qr[i].first, qr[i].second);
    }
    for (int j = 0; j < m; j++) {
        println(plans[j]);
    }
    return 0;
}
