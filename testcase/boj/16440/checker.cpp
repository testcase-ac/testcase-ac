#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
string cake;

struct Answer {
    int cuts;
    vector<int> positions;
};

int countStrawberries(int left, int right) {
    int result = 0;
    for (int i = left; i <= right; ++i) {
        if (cake[i] == 's') {
            ++result;
        }
    }
    return result;
}

void validateMiddlePiece(InStream& stream, int leftCut, int rightCut) {
    int length = rightCut - leftCut;
    if (length != n / 2) {
        stream.quitf(_wa,
                     "middle piece length must be N/2: left cut=%d, right cut=%d, length=%d, N/2=%d",
                     leftCut,
                     rightCut,
                     length,
                     n / 2);
    }

    int strawberries = countStrawberries(leftCut, rightCut - 1);
    if (strawberries != n / 4) {
        stream.quitf(_wa,
                     "middle piece must contain N/4 strawberries: found=%d, expected=%d",
                     strawberries,
                     n / 4);
    }
}

Answer readAnswer(InStream& stream) {
    int cuts = stream.readInt(1, n - 1, "k");
    stream.readEoln();

    vector<int> positions(cuts);
    for (int i = 0; i < cuts; ++i) {
        positions[i] = stream.readInt(1, n - 1, format("c_%d", i + 1).c_str());
        if (i > 0 && positions[i - 1] >= positions[i]) {
            stream.quitf(_wa,
                         "cut positions must be strictly increasing: c_%d=%d, c_%d=%d",
                         i,
                         positions[i - 1],
                         i + 1,
                         positions[i]);
        }
    }
    stream.readEoln();
    stream.readEof();

    if (cuts == 1) {
        if (positions[0] != n / 2) {
            stream.quitf(_wa,
                         "single cut must split the cake by length: cut=%d, expected=%d",
                         positions[0],
                         n / 2);
        }
        validateMiddlePiece(stream, 0, positions[0]);
    } else if (cuts == 2) {
        validateMiddlePiece(stream, positions[0], positions[1]);
    } else {
        stream.quitf(_wa, "this output format only gives an unambiguous split for 1 or 2 cuts: k=%d", cuts);
    }

    return {cuts, positions};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    cake = inf.readToken();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cuts > jury.cuts) {
        quitf(_wa, "participant uses more cuts than jury: participant=%d, jury=%d", participant.cuts, jury.cuts);
    }
    if (participant.cuts < jury.cuts) {
        quitf(_fail, "participant found fewer cuts than jury: participant=%d, jury=%d", participant.cuts, jury.cuts);
    }

    quitf(_ok, "valid split with %d cut(s)", participant.cuts);
}
