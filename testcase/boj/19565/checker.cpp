#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Answer {
    int length;
};

Answer readAnswer(InStream& stream) {
    int maxLength = n * n + 1;
    int length = stream.readInt(2, maxLength, "length");
    stream.readEoln();

    vector<int> a(length);
    for (int i = 0; i < length; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i + 1).c_str());
        if (i + 1 < length) {
            stream.readSpace();
        }
    }
    stream.readEoln();
    stream.readEof();

    if (a.front() != 1) {
        stream.quitf(_wa, "first element is %d instead of 1", a.front());
    }
    if (a.back() != 1) {
        stream.quitf(_wa, "last element is %d instead of 1", a.back());
    }

    vector<vector<int>> seen(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i + 1 < length; ++i) {
        int x = a[i];
        int y = a[i + 1];
        if (seen[x][y] != 0) {
            stream.quitf(_wa,
                         "ordered pair (%d, %d) appears at positions %d and %d",
                         x,
                         y,
                         seen[x][y],
                         i + 1);
        }
        seen[x][y] = i + 1;
    }

    return {length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 1000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length < jury.length) {
        quitf(_wa,
              "participant sequence is shorter than jury sequence: participant=%d jury=%d",
              participant.length,
              jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail,
              "participant found a longer valid sequence: participant=%d jury=%d",
              participant.length,
              jury.length);
    }

    quitf(_ok, "valid sequence of length %d", participant.length);
}
