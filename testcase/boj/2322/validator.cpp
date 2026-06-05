#include "testlib.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMaxWeight = 1LL << 30;
    constexpr long long kMaxAnswer = (1LL << 31) - 1;

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<long long> weights(n);
    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        weights[i] = inf.readLong(1LL, kMaxWeight, "weight");
        ensuref(seen.insert(weights[i]).second,
                "duplicate dumbbell weight at position %d: %lld",
                i + 1,
                weights[i]);
    }
    inf.readEoln();
    inf.readEof();

    vector<pair<long long, int>> sorted;
    sorted.reserve(n);
    for (int i = 0; i < n; ++i) {
        sorted.push_back({weights[i], i});
    }
    sort(sorted.begin(), sorted.end());

    vector<int> target(n);
    for (int sorted_pos = 0; sorted_pos < n; ++sorted_pos) {
        target[sorted[sorted_pos].second] = sorted_pos;
    }

    long long global_min = sorted.front().first;
    vector<char> visited(n, 0);
    __int128 total_cost = 0;

    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }

        int current = i;
        long long cycle_sum = 0;
        long long cycle_min = kMaxWeight;
        int cycle_size = 0;

        while (!visited[current]) {
            visited[current] = 1;
            long long weight = weights[current];
            cycle_sum += weight;
            cycle_min = min(cycle_min, weight);
            ++cycle_size;
            current = target[current];
        }

        if (cycle_size <= 1) {
            continue;
        }

        __int128 direct = static_cast<__int128>(cycle_sum) +
                          static_cast<__int128>(cycle_size - 2) * cycle_min;
        __int128 via_global = static_cast<__int128>(cycle_sum) + cycle_min +
                              static_cast<__int128>(cycle_size + 1) * global_min;
        total_cost += min(direct, via_global);
        ensuref(total_cost <= kMaxAnswer,
                "minimum required effort exceeds %lld",
                kMaxAnswer);
    }
}
