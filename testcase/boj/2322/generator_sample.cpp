#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static long long MinimumEffort(const vector<long long>& weights) {
    vector<pair<long long, int>> sorted;
    sorted.reserve(weights.size());
    for (int i = 0; i < static_cast<int>(weights.size()); ++i) {
        sorted.push_back({weights[i], i});
    }
    sort(sorted.begin(), sorted.end());

    vector<int> target(weights.size());
    for (int sorted_pos = 0; sorted_pos < static_cast<int>(sorted.size()); ++sorted_pos) {
        target[sorted[sorted_pos].second] = sorted_pos;
    }

    const long long global_min = sorted.front().first;
    vector<char> visited(weights.size(), 0);
    __int128 total = 0;

    for (int i = 0; i < static_cast<int>(weights.size()); ++i) {
        if (visited[i]) {
            continue;
        }

        int current = i;
        long long cycle_sum = 0;
        long long cycle_min = weights[i];
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
        total += min(direct, via_global);
    }

    return static_cast<long long>(total);
}

static vector<long long> BuildDistinctWeights(int n) {
    int mode = rnd.next(5);
    vector<long long> weights;
    weights.reserve(n);

    if (mode == 0) {
        long long start = rnd.next(1, 12);
        long long step = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            weights.push_back(start + step * i);
        }
    } else if (mode == 1) {
        vector<int> values;
        for (int i = 1; i <= max(30, n * 5); ++i) {
            values.push_back(i);
        }
        shuffle(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            weights.push_back(values[i]);
        }
        sort(weights.begin(), weights.end());
    } else if (mode == 2) {
        long long current = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(1, 20);
            weights.push_back(current);
        }
    } else if (mode == 3) {
        long long high = rnd.next(1000000000LL, 1073741824LL - n);
        for (int i = 0; i < n; ++i) {
            weights.push_back(high + i);
        }
    } else {
        long long small_count = min(n, rnd.next(1, min(n, 4)));
        for (int i = 1; i <= small_count; ++i) {
            weights.push_back(i);
        }
        long long base = rnd.next(30, 200);
        while (static_cast<int>(weights.size()) < n) {
            weights.push_back(base);
            base += rnd.next(1, 25);
        }
    }

    return weights;
}

static void ApplyPermutationMode(vector<long long>& weights) {
    int n = static_cast<int>(weights.size());
    if (n <= 1) {
        return;
    }

    int mode = rnd.next(7);

    if (mode == 0) {
        return;
    }
    if (mode == 1) {
        reverse(weights.begin(), weights.end());
        return;
    }
    if (mode == 2) {
        rotate(weights.begin(), weights.begin() + rnd.next(n), weights.end());
        return;
    }
    if (mode == 3) {
        shuffle(weights.begin(), weights.end());
        return;
    }
    if (mode == 4) {
        for (int i = 0; i + 1 < n; i += 2) {
            swap(weights[i], weights[i + 1]);
        }
        return;
    }
    if (mode == 5) {
        int left = rnd.next(n);
        int right = rnd.next(left, n - 1);
        reverse(weights.begin() + left, weights.begin() + right + 1);
        return;
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());
    int cycle_len = rnd.next(2, n);
    vector<long long> original = weights;
    for (int i = 0; i < cycle_len; ++i) {
        weights[order[(i + 1) % cycle_len]] = original[order[i]];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr long long kMaxAnswer = (1LL << 31) - 1;

    vector<long long> weights;
    do {
        int size_mode = rnd.next(5);
        int n = 1;
        if (size_mode == 0) {
            n = 1;
        } else if (size_mode == 1) {
            n = rnd.next(2, 5);
        } else if (size_mode == 2) {
            n = rnd.next(6, 12);
        } else if (size_mode == 3) {
            n = rnd.next(13, 25);
        } else {
            n = rnd.next(26, 40);
        }

        weights = BuildDistinctWeights(n);
        ApplyPermutationMode(weights);
    } while (MinimumEffort(weights) > kMaxAnswer);

    println(static_cast<int>(weights.size()));
    println(weights);

    return 0;
}
