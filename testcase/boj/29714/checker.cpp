#include "testlib.h"

#include <map>

using namespace std;

const int MAX_COLOR = 1000000000;
const int MAX_FINAL_COUNT = 400000;

struct Answer {
    int count;
    map<int, int> colors;
};

Answer readAnswer(InStream& stream) {
    int m = stream.readInt(0, MAX_FINAL_COUNT, "M");
    stream.readEoln();

    map<int, int> colors;
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        int color = stream.readInt(1, MAX_COLOR, format("color[%d]", i + 1).c_str());
        ++colors[color];
    }
    stream.readEoln();
    stream.readEof();

    return {m, colors};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count != jury.count) {
        quitf(_wa, "expected %d beads, found %d", jury.count, participant.count);
    }
    if (participant.colors != jury.colors) {
        quitf(_wa, "final bead multiset differs from jury answer");
    }

    quitf(_ok, "final bead multiset has %d beads", participant.count);
}
