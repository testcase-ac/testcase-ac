#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;
    const int MAX_REWARD = 2147483647;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<pair<int, int>> homework(n);
    for (int i = 0; i < n; ++i) {
        int deadline = inf.readInt(1, n, "deadline_i");
        inf.readSpace();
        int reward = inf.readInt(1, MAX_REWARD, "reward_i");
        inf.readEoln();
        homework[i] = {deadline, reward};
    }

    sort(homework.begin(), homework.end());

    priority_queue<int> rewards;
    int pos = n - 1;
    long long best = 0;
    for (int time = n; time >= 1; --time) {
        while (pos >= 0 && homework[pos].first >= time) {
            rewards.push(homework[pos].second);
            --pos;
        }

        if (!rewards.empty()) {
            best += rewards.top();
            rewards.pop();
        }
    }

    ensuref(best < (1LL << 31),
            "maximum obtainable reward must be less than 2^31, got %lld",
            best);

    inf.readEof();
}
