#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Claim {
    bool impossible;
};

[[noreturn]] void invalid(InStream& stream, TResult verdict, const char* message) {
    stream.quitf(verdict, "%s", message);
}

Claim readClaim(InStream& stream, TResult invalidVerdict) {
    int first = stream.readInt(-1, n, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            invalid(stream, invalidVerdict, "extra output after -1");
        }
        return {true};
    }

    if (first == 0) {
        invalid(stream, invalidVerdict, "card value 0 is outside [1, N]");
    }

    vector<char> usedCard(n + 1, 0);
    vector<char> received(n, 0);
    vector<int> cards(n);

    cards[0] = first;
    usedCard[first] = 1;
    for (int i = 1; i < n; ++i) {
        cards[i] = stream.readInt(1, n, format("answer[%d]", i + 1).c_str());
        if (usedCard[cards[i]]) {
            stream.quitf(invalidVerdict, "card value %d is repeated", cards[i]);
        }
        usedCard[cards[i]] = 1;
    }

    if (!stream.seekEof()) {
        invalid(stream, invalidVerdict, "extra output after sequence");
    }

    int holder = 0;
    for (int i = 0; i < n; ++i) {
        holder = (holder + cards[i]) % n;
        if (received[holder]) {
            stream.quitf(
                invalidVerdict,
                "person %d receives the ball more than once at game %d",
                holder + 1,
                i + 1);
        }
        received[holder] = 1;
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "N");

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid sequence but jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid sequence but participant reports impossible");
    }

    quitf(_ok, "valid pass sequence");
}
