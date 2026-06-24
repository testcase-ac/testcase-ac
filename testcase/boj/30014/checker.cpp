#include "testlib.h"

#include <map>
#include <vector>

using namespace std;

int n;
map<int, int> requiredCount;

struct Answer {
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0, 4000000000LL, "X");
    stream.readEoln();

    vector<int> a(n);
    map<int, int> seenCount;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        a[i] = stream.readInt(1, 1000, format("A[%d]", i + 1).c_str());
        ++seenCount[a[i]];
    }
    stream.readEoln();
    stream.readEof();

    if (seenCount != requiredCount) {
        stream.quitf(_wa, "arrangement is not a permutation of the input values");
    }

    long long actual = 0;
    for (int i = 0; i < n; ++i) {
        actual += 1LL * a[i] * a[(i + 1) % n];
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed X=%lld but arrangement value is %lld", claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        int p = inf.readInt();
        ++requiredCount[p];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa, "jury has better value: jury=%lld participant=%lld",
              jury.value, participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant found better value: jury=%lld participant=%lld",
              jury.value, participant.value);
    }

    quitf(_ok, "answer=%lld", participant.value);
}
