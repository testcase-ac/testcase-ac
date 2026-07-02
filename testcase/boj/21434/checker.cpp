#include "testlib.h"

#include <vector>

using namespace std;

int rows, cols;
vector<vector<long long>> a;

struct Answer {
    long long value;
    int x1;
    int y1;
    int x2;
    int y2;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(-40000000LL, 40000000LL, "maximum sum");
    int x1 = stream.readInt(1, rows, "x1");
    int y1 = stream.readInt(1, cols, "y1");
    int x2 = stream.readInt(1, rows, "x2");
    int y2 = stream.readInt(1, cols, "y2");

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after rectangle coordinates");
    }

    if (x1 >= x2) {
        stream.quitf(_wa, "x1 must be less than x2, found x1=%d x2=%d", x1, x2);
    }
    if (y1 >= y2) {
        stream.quitf(_wa, "y1 must be less than y2, found y1=%d y2=%d", y1, y2);
    }

    long long actual = a[x1 - 1][y1 - 1] + a[x1 - 1][y2 - 1] +
                       a[x2 - 1][y1 - 1] + a[x2 - 1][y2 - 1];
    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed sum %lld does not match rectangle sum %lld for (%d,%d)-(%d,%d)",
                     claimed,
                     actual,
                     x1,
                     y1,
                     x2,
                     y2);
    }

    return {claimed, x1, y1, x2, y2};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    rows = inf.readInt();
    cols = inf.readInt();
    a.assign(rows, vector<long long>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            a[i][j] = inf.readLong();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa,
              "jury has better answer: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant found better answer: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "answer=%lld", participant.value);
}
