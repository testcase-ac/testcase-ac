#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

using namespace std;

int n;
map<int, int> required;

struct Answer {
    bool impossible;
};

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }

    char* end = nullptr;
    long parsed = strtol(token.c_str(), &end, 10);
    if (*end != '\0') {
        return false;
    }
    if (parsed < -100000 || parsed > 100000) {
        return false;
    }

    value = static_cast<int>(parsed);
    return true;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[-0-9A-Za-z]+", "first output token");

    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<int> output(n);
    if (!parseIntToken(first, output[0])) {
        stream.quitf(_wa, "first output token is neither impossible nor a valid temperature: %s", first.c_str());
    }

    for (int i = 1; i < n; ++i) {
        output[i] = stream.readInt(-100000, 100000, format("t'_%d", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after rearrangement");
    }

    map<int, int> seen;
    for (int value : output) {
        ++seen[value];
    }
    if (seen != required) {
        stream.quitf(_wa, "output is not a rearrangement of the input temperatures");
    }

    for (int i = 1; i + 1 < n; ++i) {
        long long previous = llabs(static_cast<long long>(output[i - 1]) - output[i]);
        long long next = llabs(static_cast<long long>(output[i]) - output[i + 1]);
        if (previous > next) {
            stream.quitf(_wa,
                         "temperature differences decrease at position %d: %lld > %lld",
                         i + 1,
                         previous,
                         next);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        int value = inf.readInt();
        ++required[value];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant supplied a valid rearrangement while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid rearrangement");
    }

    quitf(_ok, "valid rearrangement");
}
