#include "testlib.h"

#include <array>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

namespace {
constexpr long long kAnswerLimit = 1000000LL;

long long cappedAdd(long long a, long long b) {
    return min(kAnswerLimit, a + b);
}

long long cappedMul(long long a, long long b) {
    __int128_t value = static_cast<__int128_t>(a) * b;
    if (value >= kAnswerLimit) {
        return kAnswerLimit;
    }
    return static_cast<long long>(value);
}

array<int, 5> residueCounts(int lo, int hi) {
    array<int, 5> counts{};
    for (int value = lo; value <= hi; ++value) {
        ++counts[value % 5];
    }
    return counts;
}

int functionValue(int residue) {
    return (residue * residue * residue * residue + 2 * residue * residue) % 5 + 1;
}

bool answerIsValid(const vector<pair<int, int>>& ranges) {
    array<long long, 5> ways{};
    ways[0] = 1;

    for (auto [v, w] : ranges) {
        array<int, 5> counts = residueCounts(v, w);
        array<long long, 5> next{};
        for (int oldResidue = 0; oldResidue < 5; ++oldResidue) {
            for (int addResidue = 0; addResidue < 5; ++addResidue) {
                int newResidue = (oldResidue + addResidue) % 5;
                long long contribution = cappedMul(ways[oldResidue], counts[addResidue]);
                next[newResidue] = cappedAdd(next[newResidue], contribution);
            }
        }
        ways = next;
    }

    long long answer = 0;
    for (int residue = 0; residue < 5; ++residue) {
        answer = cappedAdd(answer, cappedMul(ways[residue], functionValue(residue)));
    }
    return answer < kAnswerLimit;
}

vector<pair<int, int>> buildRanges(int mode, int& n) {
    vector<pair<int, int>> ranges;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 100);
            ranges.push_back({v, v});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int width = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 100 - width);
            ranges.push_back({v, v + width});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 4);
            int hi = rnd.next(0, (100 - base) / 5);
            int lo = rnd.next(0, hi);
            ranges.push_back({base + 5 * lo, base + 5 * hi});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 90);
            int w = min(100, v + rnd.next(0, 10));
            ranges.push_back({v, w});
        }
    } else {
        n = rnd.next(20, 1000);
        for (int i = 0; i < n; ++i) {
            int v;
            if (rnd.next(0, 4) == 0) {
                v = rnd.any(vector<int>{0, 1, 4, 5, 95, 99, 100});
            } else {
                v = rnd.next(0, 100);
            }
            ranges.push_back({v, v});
        }
    }

    return ranges;
}
} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    vector<pair<int, int>> ranges;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int mode = rnd.next(0, 4);
        ranges = buildRanges(mode, n);
        if (answerIsValid(ranges)) {
            break;
        }
    }
    if (!answerIsValid(ranges)) {
        n = 1;
        ranges = {{rnd.next(0, 100), rnd.next(0, 100)}};
        if (ranges[0].first > ranges[0].second) {
            swap(ranges[0].first, ranges[0].second);
        }
    }

    vector<int> out;
    out.push_back(n);
    for (auto [v, w] : ranges) {
        out.push_back(v);
        out.push_back(w);
    }
    println(out);

    return 0;
}
