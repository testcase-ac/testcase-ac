#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool possible;
};

string readDecision(InStream& stream, TResult verdict) {
    string token = stream.readToken("[A-Za-z]+", "decision");
    for (char& ch : token) {
        ch = char(toupper(ch));
    }
    if (token != "YES" && token != "NO") {
        stream.quitf(verdict, "decision must be YES or NO, found '%s'", token.c_str());
    }
    return token;
}

Answer readAnswer(InStream& stream, TResult verdict) {
    string decision = readDecision(stream, verdict);
    if (decision == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(verdict, "extra output after NO");
        }
        return {false};
    }

    vector<int> card(n + 1);
    vector<int> seenCard(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        card[i] = stream.readInt(1, n, format("b[%d]", i).c_str());
        if (seenCard[card[i]]) {
            stream.quitf(verdict, "card value %d appears more than once", card[i]);
        }
        seenCard[card[i]] = 1;
    }

    vector<int> order(n + 1);
    vector<int> flipped(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        order[i] = stream.readInt(1, n, format("c[%d]", i).c_str());
        if (flipped[order[i]]) {
            stream.quitf(verdict, "position %d is flipped more than once", order[i]);
        }

        if (i > 1) {
            int previous = order[i - 1];
            int expectedDistance = card[previous];
            int actualDistance = abs(order[i] - previous);
            if (actualDistance != expectedDistance) {
                stream.quitf(verdict,
                             "flip %d moves from position %d to %d, distance %d instead of %d",
                             i,
                             previous,
                             order[i],
                             actualDistance,
                             expectedDistance);
            }
        }

        flipped[order[i]] = 1;
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after construction");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 200000, "N");

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant found a valid construction while jury says NO");
        }
        quitf(_ok, "both outputs say NO");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a construction but participant says NO");
    }

    quitf(_ok, "valid construction");
}
