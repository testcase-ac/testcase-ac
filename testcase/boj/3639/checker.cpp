#include "testlib.h"

#include <vector>

using namespace std;

int n, k;
vector<long long> value;
vector<long long> weight;

struct Answer {
    long long valueSum;
    long long weightSum;
};

Answer readAnswer(InStream& stream) {
    vector<int> used(n + 1, 0);
    long long valueSum = 0;
    long long weightSum = 0;

    for (int i = 0; i < k; ++i) {
        int index = stream.readInt(1, n, format("jewel[%d]", i + 1).c_str());
        if (used[index]) {
            stream.quitf(_wa, "jewel %d is listed more than once", index);
        }
        used[index] = 1;
        valueSum += value[index];
        weightSum += weight[index];
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d jewels", k);
    }
    return {valueSum, weightSum};
}

int compareRatio(const Answer& left, const Answer& right) {
    __int128 lhs = static_cast<__int128>(left.valueSum) * right.weightSum;
    __int128 rhs = static_cast<__int128>(right.valueSum) * left.weightSum;
    if (lhs < rhs) {
        return -1;
    }
    if (lhs > rhs) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    value.assign(n + 1, 0);
    weight.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        value[i] = inf.readLong();
        weight[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    int cmp = compareRatio(participant, jury);
    if (cmp < 0) {
        quitf(_wa,
              "jury has better ratio: jury=%lld/%lld participant=%lld/%lld",
              jury.valueSum,
              jury.weightSum,
              participant.valueSum,
              participant.weightSum);
    }
    if (cmp > 0) {
        quitf(_fail,
              "participant found better ratio: jury=%lld/%lld participant=%lld/%lld",
              jury.valueSum,
              jury.weightSum,
              participant.valueSum,
              participant.weightSum);
    }
    quitf(_ok, "answer ratio=%lld/%lld", participant.valueSum, participant.weightSum);
}
