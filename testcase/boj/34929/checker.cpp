#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int n;
vector<long long> initialValues;

struct Answer {
    long long value;
};

void takeValue(InStream& stream, map<long long, int>& counts, long long value, int op, int pos) {
    auto it = counts.find(value);
    if (it == counts.end() || it->second == 0) {
        stream.quitf(_wa, "operation %d value %d (%lld) is not present on the board", op, pos, value);
    }
    --it->second;
    if (it->second == 0) {
        counts.erase(it);
    }
}

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(-1000000000LL, 1000000000LL, "claimed final value");
    stream.readEoln();

    map<long long, int> counts;
    for (long long value : initialValues) {
        ++counts[value];
    }

    int operations = (n - 1) / 2;
    for (int i = 0; i < operations; ++i) {
        long long x = stream.readLong(-1000000000LL, 1000000000LL, format("operation[%d].x", i + 1).c_str());
        long long y = stream.readLong(-1000000000LL, 1000000000LL, format("operation[%d].y", i + 1).c_str());
        long long z = stream.readLong(-1000000000LL, 1000000000LL, format("operation[%d].z", i + 1).c_str());
        stream.readEoln();

        takeValue(stream, counts, x, i + 1, 1);
        takeValue(stream, counts, y, i + 1, 2);
        takeValue(stream, counts, z, i + 1, 3);

        vector<long long> triple = {x, y, z};
        sort(triple.begin(), triple.end());
        ++counts[triple[1]];
    }

    stream.readEof();

    if (counts.size() != 1 || counts.begin()->second != 1) {
        stream.quitf(_wa, "operation sequence leaves %d distinct values on the board", (int)counts.size());
    }
    long long actual = counts.begin()->first;
    if (claimed != actual) {
        stream.quitf(_wa, "claimed final value %lld differs from simulated final value %lld", claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialValues = inf.readLongs(n);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa, "jury has better final value: jury=%lld participant=%lld", jury.value, participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant found better final value: jury=%lld participant=%lld", jury.value, participant.value);
    }
    quitf(_ok, "final value %lld", participant.value);
}
