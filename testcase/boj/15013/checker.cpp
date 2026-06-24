#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<string> beats;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("impossible|-?[0-9]+", "first output token");

    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<int> schedule(n);
    vector<bool> used(n, false);

    schedule[0] = stringToLongLong(stream, first);
    if (schedule[0] < 0 || schedule[0] >= n) {
        stream.quitf(_wa, "participant[1]=%d is outside [0, %d]", schedule[0], n - 1);
    }
    used[schedule[0]] = true;

    for (int i = 1; i < n; ++i) {
        schedule[i] = stream.readInt(0, n - 1, format("participant[%d]", i + 1).c_str());
        if (used[schedule[i]]) {
            stream.quitf(_wa, "participant %d appears more than once", schedule[i]);
        }
        used[schedule[i]] = true;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after schedule");
    }

    int king = schedule[0];
    for (int i = 1; i < n; ++i) {
        int challenger = schedule[i];
        if (beats[challenger][king] == '1') {
            king = challenger;
        }
    }

    if (king != 0) {
        stream.quitf(_wa, "schedule ends with participant %d as king instead of 0", king);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    beats.resize(n);
    for (int i = 0; i < n; ++i) {
        beats[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid schedule while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid schedule");
    }

    quitf(_ok, "valid schedule makes participant 0 the final king");
}
