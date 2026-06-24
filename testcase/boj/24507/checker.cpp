#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    if (verdict == "No") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false};
    }
    if (verdict != "Yes") {
        stream.quitf(_wa, "expected 'Yes' or 'No', found '%s'", verdict.c_str());
    }

    vector<int> first(n, -1);
    vector<int> count(n, 0);
    for (int pos = 0; pos < 2 * n; ++pos) {
        int value = stream.readInt(0, n - 1, format("sequence[%d]", pos + 1).c_str());
        ++count[value];
        if (count[value] > 2) {
            stream.quitf(_wa, "value %d appears more than twice", value);
        }
        if (first[value] == -1) {
            first[value] = pos;
        } else if (pos - first[value] - 1 != value) {
            stream.quitf(_wa,
                         "value %d has %d numbers between occurrences, expected %d",
                         value,
                         pos - first[value] - 1,
                         value);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int value = 0; value < n; ++value) {
        if (count[value] != 2) {
            stream.quitf(_wa, "value %d appears %d times, expected 2", value, count[value]);
        }
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid sequence but participant printed No");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid sequence while jury printed No");
    }
    if (!jury.possible) {
        quitf(_ok, "both outputs say No");
    }
    quitf(_ok, "valid sequence");
}
