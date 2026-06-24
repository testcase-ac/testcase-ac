#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
long long targetA, lowerH, upperH;

struct Claim {
    bool possible;
};

string toString128(__int128 value) {
    if (value == 0) {
        return "0";
    }
    bool negative = value < 0;
    if (negative) {
        value = -value;
    }
    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}

__int128 maxHistogramArea(const vector<long long>& heights) {
    vector<int> stack;
    __int128 best = 0;

    for (int i = 0; i <= n; ++i) {
        long long current = (i == n ? -1 : heights[i]);
        while (!stack.empty() && heights[stack.back()] > current) {
            int at = stack.back();
            stack.pop_back();
            int left = stack.empty() ? -1 : stack.back();
            long long width = i - left - 1;
            best = max(best, (__int128)heights[at] * width);
        }
        stack.push_back(i);
    }

    return best;
}

Claim readClaim(InStream& stream, bool jury) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(jury ? _fail : _wa, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(jury ? _fail : _wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<long long> heights(n);
    for (int i = 0; i < n; ++i) {
        heights[i] = stream.readLong(lowerH, upperH, format("H[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(jury ? _fail : _wa, "extra output after height sequence");
    }

    __int128 area = maxHistogramArea(heights);
    if (area != (__int128)targetA) {
        stream.quitf(jury ? _fail : _wa,
                     "witness maximum rectangle area is %s, expected %lld",
                     toString128(area).c_str(),
                     targetA);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    targetA = inf.readLong();
    lowerH = inf.readLong();
    upperH = inf.readLong();

    Claim jury = readClaim(ans, true);
    Claim participant = readClaim(ouf, false);

    if (!jury.possible && !participant.possible) {
        quitf(_ok, "both outputs report NO");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury provides a valid witness, but participant reports NO");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provides a valid witness while jury reports NO");
    }

    quitf(_ok, "valid witness with maximum rectangle area %lld", targetA);
}
