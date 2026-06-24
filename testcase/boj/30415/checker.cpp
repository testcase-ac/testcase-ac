#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int n, m;

struct Answer {
    bool impossible;
    long long sum;
};

long long lcmValue(long long a, long long b) {
    return a / gcd(a, b) * b;
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n - 1, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }

    vector<int> values(m);
    vector<bool> used(n, false);
    values[0] = first;

    for (int i = 1; i < m; ++i) {
        values[i] = stream.readInt(1, n - 1, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after team values");
    }

    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        int value = values[i];
        if (value < 1 || value >= n) {
            stream.quitf(_wa, "answer[%d]=%d is outside [1, %d]", i + 1, value, n - 1);
        }
        if (used[value]) {
            stream.quitf(_wa, "value %d is repeated", value);
        }
        used[value] = true;
        sum += value;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            long long lcm = lcmValue(values[i], values[j]);
            if (lcm != n) {
                stream.quitf(_wa,
                             "lcm(answer[%d]=%d, answer[%d]=%d) is %lld instead of %d",
                             i + 1,
                             values[i],
                             j + 1,
                             values[j],
                             lcm,
                             n);
            }
        }
    }

    return {false, sum};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid team with sum %lld while jury says impossible", participant.sum);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible while jury has a valid team with sum %lld", jury.sum);
    }

    if (participant.sum < jury.sum) {
        quitf(_fail, "participant found a better valid team: jury=%lld participant=%lld", jury.sum, participant.sum);
    }
    if (participant.sum > jury.sum) {
        quitf(_wa, "participant team is not optimal: jury=%lld participant=%lld", jury.sum, participant.sum);
    }

    quitf(_ok, "valid optimal team with sum %lld", participant.sum);
}
