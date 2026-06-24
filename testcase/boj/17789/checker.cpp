#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
};

int p, v;
vector<pair<int, int>> pedestals;
vector<int> vases;

string toLower(string s) {
    for (char& ch : s) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return s;
}

int parseIndexToken(InStream& stream, const string& token, const char* name) {
    char* end = nullptr;
    long value = strtol(token.c_str(), &end, 10);
    if (*end != '\0') {
        stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
    }
    if (value < 1 || value > p) {
        stream.quitf(_wa, "%s is out of range: %ld", name, value);
    }
    return static_cast<int>(value);
}

Claim readClaim(InStream& stream) {
    if (v == 0) {
        if (stream.seekEof()) {
            return {false};
        }

        string token = stream.readToken();
        if (toLower(token) == "impossible") {
            if (!stream.seekEof()) {
                stream.quitf(_wa, "extra output after impossible");
            }
            return {true};
        }

        stream.quitf(_wa, "expected empty output or impossible for zero vases");
    }

    string first = stream.readToken();
    if (toLower(first) == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<int> used(p + 1, 0);
    for (int i = 0; i < v; ++i) {
        string token = (i == 0) ? first : stream.readToken();
        int pedestal = parseIndexToken(
            stream, token, format("x_%d", i + 1).c_str());

        if (used[pedestal]) {
            stream.quitf(_wa, "pedestal %d is used more than once", pedestal);
        }
        used[pedestal] = 1;

        int vase = vases[i];
        int a = pedestals[pedestal].first;
        int b = pedestals[pedestal].second;
        if (a != vase && b != vase) {
            stream.quitf(_wa,
                         "vase %d has diameter %d but pedestal %d has sides %d and %d",
                         i + 1, vase, pedestal, a, b);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    p = inf.readInt();
    v = inf.readInt();

    pedestals.assign(p + 1, {0, 0});
    for (int i = 1; i <= p; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        pedestals[i] = {a, b};
    }

    vases.resize(v);
    for (int i = 0; i < v; ++i) {
        vases[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both answers report impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid assignment while jury says impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury has a valid assignment but participant reports impossible");
    }

    quitf(_ok, "valid assignment");
}
