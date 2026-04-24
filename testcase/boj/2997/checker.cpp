#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

static vector<int> a;

// This function reads an integer from the given stream (contestant or jury),
// then checks that when added to the three input numbers, the resulting
// four numbers (when sorted) form a valid arithmetic progression.
// If the sequence is invalid, it quits with _wa (for ouf) or _fail (for ans).
int readAns(InStream &stream) {
    // The missing number can in principle lie outside [-100,100],
    // so we allow a wide range.
    int x = stream.readInt(-1000000000, 1000000000, "missing number");
    vector<int> b = a;
    b.push_back(x);
    sort(b.begin(), b.end());
    int d = b[1] - b[0];
    for (int i = 2; i < 4; i++) {
        if (b[i] - b[i - 1] != d) {
            stream.quitf(_wa, "the sequence [%d, %d, %d, %d] is not an arithmetic progression",
                         b[0], b[1], b[2], b[3]);
        }
    }
    return x;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read the three known numbers.
    a.resize(3);
    for (int i = 0; i < 3; i++) {
        a[i] = inf.readInt();
    }
    // Read and check the contestant's answer.
    readAns(ouf);
    // Optionally ensure there's no extra garbage.
    ouf.skipBlanks();
    if (!ouf.eof())
        ouf.quitf(_pe, "extra data after the answer");
    // If we reach here, the contestant's answer is a valid completion.
    quitf(_ok, "valid arithmetic progression");
}
