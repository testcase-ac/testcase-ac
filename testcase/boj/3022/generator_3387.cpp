#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of food takings
    int N = rnd.next(1, 10);
    // Number of distinct children
    int maxK = min(N, 5);
    int K = rnd.next(1, maxK);

    // Generate K unique random names
    set<string> nameSet;
    while ((int)nameSet.size() < K) {
        int len = rnd.next(1, 5);
        string s;
        for (int i = 0; i < len; i++) {
            s += char('a' + rnd.next(0, 25));
        }
        nameSet.insert(s);
    }
    vector<string> names(nameSet.begin(), nameSet.end());
    shuffle(names.begin(), names.end());

    // Prepare counts and sequence
    vector<int> count(K, 0);
    vector<string> seq;
    // Hyper-parameter to bias warnings
    int warningBias = rnd.next(-1, 1);

    for (int i = 0; i < N; i++) {
        int idx;
        double p = rnd.next();
        if (warningBias > 0 && p < 0.7) {
            // pick the current leader more often
            idx = max_element(count.begin(), count.end()) - count.begin();
        } else if (warningBias < 0 && p < 0.7) {
            // avoid the leader
            int leader = max_element(count.begin(), count.end()) - count.begin();
            vector<int> others;
            for (int j = 0; j < K; j++) {
                if (j != leader) others.push_back(j);
            }
            if (others.empty()) idx = leader;
            else idx = rnd.any(others);
        } else {
            // uniform pick
            idx = rnd.next(0, K - 1);
        }
        seq.push_back(names[idx]);
        count[idx]++;
    }

    // Output the test case
    println(N);
    for (auto &s : seq) println(s);

    return 0;
}
