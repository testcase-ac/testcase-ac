#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> initialColors;

struct Answer {
    bool impossible;
    vector<int> colors;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 3, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    if (first == 0) {
        stream.quitf(_wa, "answer[1] is 0, expected a color from 1 to 3 or -1");
    }

    vector<int> colors(n);
    colors[0] = first;
    for (int i = 1; i < n; ++i) {
        colors[i] = stream.readInt(1, 3, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after coloring");
    }

    for (int i = 0; i < n; ++i) {
        if (initialColors[i] != 0 && colors[i] != initialColors[i]) {
            stream.quitf(_wa,
                         "answer[%d] is %d, expected precolored value %d",
                         i + 1,
                         colors[i],
                         initialColors[i]);
        }
        if (i > 0 && colors[i - 1] == colors[i]) {
            stream.quitf(_wa,
                         "adjacent cards %d and %d both have color %d",
                         i,
                         i + 1,
                         colors[i]);
        }
    }

    return {false, colors};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialColors.resize(n);
    for (int i = 0; i < n; ++i) {
        initialColors[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid coloring while jury output is -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant output is -1, but jury has a valid coloring");
    }

    quitf(_ok, "valid coloring");
}
