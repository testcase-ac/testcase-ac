#include "testlib.h"

#include <vector>

using namespace std;

int n;

void readSequence(InStream& stream) {
    vector<int> a(n);
    vector<int> seen(100001, 0);
    vector<long long> prefix(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(1, 100000, format("a[%d]", i + 1).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        seen[a[i]] = 1;
        prefix[i + 1] = prefix[i] + a[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            long long sum = prefix[l + len] - prefix[l];
            if (sum % len != 0) {
                stream.quitf(_wa,
                             "sum of subarray [%d, %d] is %lld, not divisible by %d",
                             l + 1,
                             l + len,
                             sum,
                             len);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "N");
    inf.readEoln();
    inf.readEof();

    readSequence(ans);
    readSequence(ouf);

    quitf(_ok, "valid sequence");
}
