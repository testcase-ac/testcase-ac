#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

long long n, a, b;

struct Answer {
    bool possible;
};

string lowercase(string value) {
    for (char& ch : value) {
        ch = char(tolower(static_cast<unsigned char>(ch)));
    }
    return value;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readWord("[Yy][Ee][Ss]|[Nn][Oo]", "verdict");

    if (lowercase(verdict) == "no") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false};
    }

    vector<int> used(2 * n, 0);
    for (int i = 0; i < n; ++i) {
        long long x = stream.readLong(1, 3000000000000000000LL, format("pair[%d].first", i + 1).c_str());
        long long y = stream.readLong(1, 3000000000000000000LL, format("pair[%d].second", i + 1).c_str());

        if (gcd(x, y) != 1) {
            stream.quitf(_wa, "pair %d contains non-coprime values %lld and %lld", i + 1, x, y);
        }

        long long values[2] = {x, y};
        for (int j = 0; j < 2; ++j) {
            long long value = values[j];
            if (value < a) {
                stream.quitf(_wa, "pair %d value %lld is smaller than first sequence value %lld", i + 1, value, a);
            }
            if ((value - a) % b != 0) {
                stream.quitf(_wa, "pair %d value %lld is not in the arithmetic sequence", i + 1, value);
            }

            long long index = (value - a) / b;
            if (index < 0 || index >= 2 * n) {
                stream.quitf(_wa, "pair %d value %lld has sequence index %lld outside [0, %lld)",
                             i + 1, value, index, 2 * n);
            }
            if (used[index]) {
                stream.quitf(_wa, "sequence value %lld is used more than once", value);
            }
            used[index] = 1;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after construction");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();
    a = inf.readLong();
    b = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provided a valid construction while jury says No");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a construction but participant says No");
    }

    quitf(_ok, "answer is %s", participant.possible ? "Yes" : "No");
}
