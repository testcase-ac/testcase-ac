#include "testlib.h"

#include <array>

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
} // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");

    array<long long, 5> ways{};
    ways[0] = 1;

    for (int i = 0; i < n; ++i) {
        inf.readSpace();
        int v = inf.readInt(0, 100, "v_i");
        inf.readSpace();
        int w = inf.readInt(0, 100, "w_i");
        ensuref(v <= w, "range %d has v_i > w_i: %d > %d", i + 1, v, w);

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

    inf.readEoln();

    long long answer = 0;
    for (int residue = 0; residue < 5; ++residue) {
        answer = cappedAdd(answer, cappedMul(ways[residue], functionValue(residue)));
    }
    ensuref(answer < kAnswerLimit, "promised answer must be less than %lld", kAnswerLimit);

    inf.readEof();
}
