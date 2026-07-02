#include "testlib.h"

#include <cctype>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
};

long long parseLongLongToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }

    int pos = 0;
    if (token[0] == '-') {
        pos = 1;
    }
    if (pos == (int)token.size()) {
        stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
    }
    for (int i = pos; i < (int)token.size(); ++i) {
        if (!isdigit((unsigned char)token[i])) {
            stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
        }
    }

    errno = 0;
    char* end = nullptr;
    long long value = strtoll(token.c_str(), &end, 10);
    if (errno == ERANGE || *end != '\0') {
        stream.quitf(_wa, "%s is outside signed 64-bit range: %s", name, token.c_str());
    }
    return value;
}

Claim readClaim(InStream& stream, int n, long long targetSum) {
    string first = stream.readToken();
    if (first == "NIE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NIE");
        }
        return {true};
    }

    vector<long long> sequence(n);
    sequence[0] = parseLongLongToken(stream, first, "a[1]");
    if (sequence[0] < -n || sequence[0] > n) {
        stream.quitf(_wa, "a[1] is outside valid one-sequence range: %lld", sequence[0]);
    }
    for (int i = 1; i < n; ++i) {
        sequence[i] = stream.readLong((long long)-n, (long long)n, format("a[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    if (sequence[0] != 0) {
        stream.quitf(_wa, "a[1] is %lld instead of 0", sequence[0]);
    }

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if ((sequence[i] > 0 && sum > LLONG_MAX - sequence[i]) ||
            (sequence[i] < 0 && sum < LLONG_MIN - sequence[i])) {
            stream.quitf(_wa, "sequence sum overflows signed 64-bit range");
        }
        sum += sequence[i];

        if (i > 0) {
            long long diff = sequence[i] - sequence[i - 1];
            if (diff != 1 && diff != -1) {
                stream.quitf(_wa,
                             "|a[%d] - a[%d]| is %lld instead of 1",
                             i,
                             i + 1,
                             llabs(diff));
            }
        }
    }

    if (sum != targetSum) {
        stream.quitf(_wa, "sequence sum is %lld instead of %lld", sum, targetSum);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    long long targetSum = inf.readLong();

    Claim jury = readClaim(ans, n, targetSum);
    Claim participant = readClaim(ouf, n, targetSum);

    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid sequence while jury says NIE");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury has a valid sequence but participant says NIE");
    }

    quitf(_ok, jury.impossible ? "both outputs say NIE" : "valid one-sequence");
}
