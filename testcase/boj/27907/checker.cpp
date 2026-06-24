#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 3825123056546413051LL;

int n;

using u64 = unsigned long long;
using u128 = __uint128_t;

struct Claim {
    bool impossible;
};

long long parseIntegerToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }

    int pos = 0;
    bool negative = false;
    if (token[pos] == '-') {
        negative = true;
        ++pos;
    }
    if (pos == (int)token.size()) {
        stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
    }
    for (int i = pos; i < (int)token.size(); ++i) {
        if (!isdigit((unsigned char)token[i])) {
            stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
        }
    }

    u64 value = 0;
    const u64 positiveLimit = (u64)LLONG_MAX;
    const u64 negativeLimit = positiveLimit + 1ULL;
    const u64 bound = negative ? negativeLimit : positiveLimit;
    for (int i = pos; i < (int)token.size(); ++i) {
        int digit = token[i] - '0';
        if (value > (bound - digit) / 10ULL) {
            stream.quitf(_wa, "%s is out of signed 64-bit range: %s", name, token.c_str());
        }
        value = value * 10ULL + (u64)digit;
    }

    if (negative) {
        if (value == negativeLimit) {
            return LLONG_MIN;
        }
        return -(long long)value;
    }
    return (long long)value;
}

u64 modPow(u64 base, u64 exp, u64 mod) {
    u64 result = 1;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = (u64)((u128)result * base % mod);
        }
        base = (u64)((u128)base * base % mod);
        exp >>= 1ULL;
    }
    return result;
}

bool isPrime(long long x) {
    if (x < 2) {
        return false;
    }
    u64 value = (u64)x;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (value == p) {
            return true;
        }
        if (value % p == 0) {
            return false;
        }
    }

    u64 d = value - 1;
    int s = 0;
    while ((d & 1ULL) == 0) {
        d >>= 1ULL;
        ++s;
    }

    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (a % value == 0) {
            continue;
        }
        u64 cur = modPow(a, d, value);
        if (cur == 1 || cur == value - 1) {
            continue;
        }
        bool maybePrime = false;
        for (int r = 1; r < s; ++r) {
            cur = (u64)((u128)cur * cur % value);
            if (cur == value - 1) {
                maybePrime = true;
                break;
            }
        }
        if (!maybePrime) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string firstToken = stream.readToken("[+-]?[0-9]+", "answer[1]");
    long long first = parseIntegerToken(stream, firstToken, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> sequence(n);
    sequence[0] = first;
    for (int i = 1; i < n; ++i) {
        string token = stream.readToken("[+-]?[0-9]+", format("answer[%d]", i + 1).c_str());
        sequence[i] = parseIntegerToken(stream, token, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after arithmetic progression");
    }

    for (int i = 0; i < n; ++i) {
        if (sequence[i] < 2 || sequence[i] > LIMIT) {
            stream.quitf(_wa, "answer[%d]=%lld is outside the allowed prime range", i + 1, sequence[i]);
        }
        if (!isPrime(sequence[i])) {
            stream.quitf(_wa, "answer[%d]=%lld is not prime", i + 1, sequence[i]);
        }
    }

    long long diff = sequence[1] - sequence[0];
    for (int i = 2; i < n; ++i) {
        if (sequence[i] - sequence[i - 1] != diff) {
            stream.quitf(_wa, "sequence is not arithmetic at answer[%d]", i + 1);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 30, "n");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid arithmetic progression while jury claims impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid arithmetic progression but participant claims impossible");
    }

    quitf(_ok, "valid arithmetic progression");
}
