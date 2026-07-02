#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
long long initialValue;
vector<long long> casA, casB;
vector<int> wish;

struct Answer {
    bool possible;
};

string readVerdictToken(InStream& stream) {
    string token = stream.readToken("[A-Za-z]+", "verdict");
    if (token == "Yes" || token == "YES" || token == "yes") {
        return "Yes";
    }
    if (token == "No" || token == "NO" || token == "no") {
        return "No";
    }
    stream.quitf(_wa, "verdict must be Yes or No, found '%s'", token.c_str());
}

Answer readAnswer(InStream& stream) {
    string verdict = readVerdictToken(stream);
    if (verdict == "No") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false};
    }

    vector<int> used(n + 1, 0);
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = stream.readInt(1, n, format("p[%d]", i + 1).c_str());
        if (used[order[i]]) {
            stream.quitf(_wa, "operation %d appears more than once", order[i]);
        }
        used[order[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    long long value = initialValue;
    for (int step = 0; step < n; ++step) {
        int id = order[step];
        bool succeeds = (value == casA[id]);
        if (succeeds != (wish[id] == 1)) {
            stream.quitf(_wa,
                         "operation %d at position %d has success=%d, expected %d",
                         id,
                         step + 1,
                         succeeds ? 1 : 0,
                         wish[id]);
        }
        if (succeeds) {
            value = casB[id];
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialValue = inf.readLong();
    casA.assign(n + 1, 0);
    casB.assign(n + 1, 0);
    wish.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        casA[i] = inf.readLong();
        casB[i] = inf.readLong();
        wish[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid order while jury says No");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid order but participant says No");
    }

    quitf(_ok, jury.possible ? "valid order" : "both answers are No");
}
