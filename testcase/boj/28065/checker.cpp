#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n;

vector<int> readAnswer(InStream& stream) {
    vector<int> a(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i + 1).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d is repeated", a[i]);
        }
        seen[a[i]] = 1;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int i = 1; i + 1 < n; ++i) {
        int left = abs(a[i] - a[i - 1]);
        int right = abs(a[i + 1] - a[i]);
        if (left <= right) {
            stream.quitf(_wa,
                         "condition fails at i=%d: |%d-%d|=%d <= |%d-%d|=%d",
                         i + 1,
                         a[i],
                         a[i - 1],
                         left,
                         a[i + 1],
                         a[i],
                         right);
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 5000, "N");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid SW sequence");
}
