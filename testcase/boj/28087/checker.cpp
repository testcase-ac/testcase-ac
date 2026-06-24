#include "testlib.h"

#include <vector>
using namespace std;

long long n;
int m;
vector<long long> credits;

struct Claim {
    long long sum;
    int count;
};

Claim readClaim(InStream& stream) {
    int count = stream.readInt(1, m, "L");
    stream.readEoln();

    vector<char> used(m + 1, 0);
    long long sum = 0;
    for (int i = 0; i < count; ++i) {
        int index = stream.readInt(1, m, format("X_%d", i + 1).c_str());
        stream.readEoln();

        if (used[index]) {
            stream.quitf(_wa, "course index %d is repeated", index);
        }
        used[index] = 1;
        sum += credits[index];
    }
    stream.readEof();

    if (sum < n || sum > 2 * n) {
        stream.quitf(_wa, "selected credits sum %lld is outside [%lld, %lld]", sum, n, 2 * n);
    }

    return {sum, count};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();
    m = inf.readInt();
    credits.assign(m + 1, 0);
    for (int i = 1; i <= m; ++i) {
        credits[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "selected %d courses with total credits %lld; jury selected %d courses with total credits %lld",
          participant.count,
          participant.sum,
          jury.count,
          jury.sum);
}
