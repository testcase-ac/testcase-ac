#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Claim {
    int operations;
};

int n;
vector<int> target;

Claim readClaim(InStream& stream) {
    int operations = stream.readInt(0, n, "K");
    vector<int> current(n);
    for (int i = 0; i < n; ++i) {
        current[i] = i + 1;
    }

    for (int i = 0; i < operations; ++i) {
        int left = stream.readInt(1, n, format("a[%d]", i + 1).c_str());
        int right = stream.readInt(1, n, format("b[%d]", i + 1).c_str());
        if (left > right) {
            stream.quitf(_wa,
                         "operation %d has invalid interval (%d, %d)",
                         i + 1,
                         left,
                         right);
        }

        reverse(current.begin() + left - 1, current.begin() + right);
        for (int pos = left - 1; pos < right; ++pos) {
            current[pos] = -current[pos];
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation list");
    }

    if (current != target) {
        for (int i = 0; i < n; ++i) {
            if (current[i] != target[i]) {
                stream.quitf(_wa,
                             "operation list produces value %d at position %d, expected %d",
                             current[i],
                             i + 1,
                             target[i]);
            }
        }
    }

    return {operations};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    target.resize(n);
    for (int i = 0; i < n; ++i) {
        target[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.operations > jury.operations) {
        quitf(_wa,
              "participant uses more operations than jury: participant=%d jury=%d",
              participant.operations,
              jury.operations);
    }
    if (participant.operations < jury.operations) {
        quitf(_fail,
              "participant found a better operation count: participant=%d jury=%d",
              participant.operations,
              jury.operations);
    }

    quitf(_ok, "operation count %d", participant.operations);
}
