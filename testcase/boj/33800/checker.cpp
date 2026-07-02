#include "testlib.h"

#include <cctype>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool possible;
};

struct Pack {
    char brand;
    long long size;
    long long cups;
};

Pack parsePackToken(InStream& stream, const string& token, int caseIndex, int packIndex) {
    if (token.size() < 2) {
        stream.quitf(_wa, "case %d pack %d is too short", caseIndex, packIndex);
    }
    char brand = token[0];
    if (brand != 'A' && brand != 'B') {
        stream.quitf(_wa, "case %d pack %d has invalid brand '%c'", caseIndex, packIndex, brand);
    }
    long long size = 0;
    for (size_t i = 1; i < token.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(token[i]))) {
            stream.quitf(_wa, "case %d pack %d has invalid size token '%s'",
                         caseIndex, packIndex, token.c_str());
        }
        int digit = token[i] - '0';
        if (size > 1000000000LL / 10) {
            stream.quitf(_wa, "case %d pack %d size is too large", caseIndex, packIndex);
        }
        size = size * 10 + digit;
    }
    if (size <= 0) {
        stream.quitf(_wa, "case %d pack %d size must be positive", caseIndex, packIndex);
    }

    __int128 cups = static_cast<__int128>(size) * size;
    if (brand == 'B') {
        cups *= 2;
    }
    if (cups > static_cast<__int128>(1000000000LL) * 1000000000LL * 2) {
        stream.quitf(_wa, "case %d pack %d contribution is too large", caseIndex, packIndex);
    }
    return {brand, size, static_cast<long long>(cups)};
}

vector<Claim> readClaims(InStream& stream, const vector<int>& targets, const char* streamName) {
    vector<Claim> claims;
    for (int tc = 0; tc < static_cast<int>(targets.size()); ++tc) {
        int k = stream.readInt(0, 100000, format("%s case %d pack count", streamName, tc + 1).c_str());
        if (k == 0) {
            claims.push_back({false});
            continue;
        }

        long long sum = 0;
        set<pair<char, long long>> used;
        for (int i = 0; i < k; ++i) {
            string token = stream.readToken(format("[AB][0-9]+"), format("%s case %d pack %d",
                                           streamName, tc + 1, i + 1).c_str());
            Pack pack = parsePackToken(stream, token, tc + 1, i + 1);
            if (!used.insert({pack.brand, pack.size}).second) {
                stream.quitf(_wa, "%s case %d repeats pack type %c%lld",
                             streamName, tc + 1, pack.brand, pack.size);
            }
            if (sum > targets[tc] || pack.cups > targets[tc] || sum + pack.cups > targets[tc]) {
                stream.quitf(_wa, "%s case %d pack sum exceeds target %d",
                             streamName, tc + 1, targets[tc]);
            }
            sum += pack.cups;
        }
        if (sum != targets[tc]) {
            stream.quitf(_wa, "%s case %d pack sum is %lld instead of %d",
                         streamName, tc + 1, sum, targets[tc]);
        }
        claims.push_back({true});
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "%s output has extra tokens", streamName);
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    vector<int> targets(t);
    for (int i = 0; i < t; ++i) {
        targets[i] = inf.readInt(1, 1000000000, format("n[%d]", i + 1).c_str());
    }

    vector<Claim> jury = readClaims(ans, targets, "jury");
    vector<Claim> participant = readClaims(ouf, targets, "participant");
    for (int i = 0; i < t; ++i) {
        if (jury[i].possible && !participant[i].possible) {
            quitf(_wa, "case %d: jury has a valid purchase but participant printed 0", i + 1);
        }
        if (!jury[i].possible && participant[i].possible) {
            quitf(_fail, "case %d: participant found a valid purchase while jury printed 0", i + 1);
        }
    }
    quitf(_ok, "all %d case(s) contain valid pack selections", t);
}
