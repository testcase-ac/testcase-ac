#include "testlib.h"

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int n;
vector<long long> values;

struct Claim {
    bool impossible;
    int left;
    int right;
};

string lowerToken(string token) {
    for (char& ch : token) {
        ch = char(tolower(static_cast<unsigned char>(ch)));
    }
    return token;
}

int parseIndexToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }

    char* end = nullptr;
    errno = 0;
    long value = strtol(token.c_str(), &end, 10);
    if (errno == ERANGE || end == token.c_str() || *end != '\0') {
        stream.quitf(_wa, "%s must be an integer, found '%s'", name, token.c_str());
    }
    if (value < 1 || value > n) {
        stream.quitf(_wa, "%s=%ld is outside [1, %d]", name, value, n);
    }
    return int(value);
}

bool sortsAfterReverse(int left, int right) {
    auto atAfterReverse = [&](int index) -> long long {
        if (left <= index && index <= right) {
            return values[left + right - index];
        }
        return values[index];
    };

    for (int i = 2; i <= n; ++i) {
        if (atAfterReverse(i - 1) > atAfterReverse(i)) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();
    string normalized = lowerToken(first);

    if (normalized == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true, -1, -1};
    }

    int left = parseIndexToken(stream, first, "left");
    int right = stream.readInt(1, n, "right");
    if (left > right) {
        stream.quitf(_wa, "left index %d is greater than right index %d", left, right);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after segment");
    }

    if (!sortsAfterReverse(left, right)) {
        stream.quitf(_wa, "reversing [%d, %d] does not sort the deck", left, right);
    }
    return {false, left, right};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "n");
    values.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        values[i] = inf.readLong(1LL, 1000000000LL, format("v[%d]", i).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail,
              "participant found a valid segment [%d, %d] while jury says impossible",
              participant.left,
              participant.right);
    }

    if (participant.impossible) {
        quitf(_wa,
              "jury has valid segment [%d, %d], but participant says impossible",
              jury.left,
              jury.right);
    }

    quitf(_ok, "valid segment [%d, %d]", participant.left, participant.right);
}
