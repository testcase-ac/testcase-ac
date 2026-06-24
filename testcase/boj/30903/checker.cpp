#include "testlib.h"

#include <array>
#include <string>

using namespace std;

long long c, d;
string aStr, bStr;

struct Claim {
    bool possible;
    string numerator;
    string denominator;
};

string readNumberToken(InStream& stream, const char* name) {
    string value = stream.readToken("[0-9]+", name);
    if (value.size() > 1 && value[0] == '0') {
        stream.quitf(_wa, "%s has a leading zero", name);
    }
    return value;
}

long long parseBoundedPositive(InStream& stream, const string& value, const char* name) {
    if (value.size() > 18) {
        stream.quitf(_wa, "%s has too many digits", name);
    }

    long long result = 0;
    for (char ch : value) {
        int digit = ch - '0';
        if (result > (1000000000000000000LL - digit) / 10) {
            stream.quitf(_wa, "%s is too large", name);
        }
        result = result * 10 + digit;
    }
    if (result == 0) {
        stream.quitf(_wa, "%s must be positive", name);
    }
    return result;
}

array<int, 10> cancellationCounts(InStream& stream,
                                  const string& original,
                                  const string& remaining,
                                  const char* name) {
    array<int, 10> removed{};
    int pos = 0;
    for (char ch : original) {
        if (pos < int(remaining.size()) && ch == remaining[pos]) {
            ++pos;
        } else {
            ++removed[ch - '0'];
        }
    }

    if (pos != int(remaining.size())) {
        stream.quitf(_wa, "%s is not obtainable by cancelling digits", name);
    }
    return removed;
}

void validateWitness(InStream& stream, const string& numerator, const string& denominator) {
    long long num = parseBoundedPositive(stream, numerator, "a'");
    long long den = parseBoundedPositive(stream, denominator, "b'");

    array<int, 10> removedA = cancellationCounts(stream, aStr, numerator, "a'");
    array<int, 10> removedB = cancellationCounts(stream, bStr, denominator, "b'");
    if (removedA != removedB) {
        stream.quitf(_wa, "cancelled digit multisets differ");
    }

    if ((__int128)num * d != (__int128)den * c) {
        stream.quitf(_wa, "fraction %s/%s is not equal to %lld/%lld",
                     numerator.c_str(), denominator.c_str(), c, d);
    }
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");

    if (verdict == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {false, "", ""};
    }

    if (verdict != "possible") {
        stream.quitf(_wa, "expected possible or impossible, found %s", verdict.c_str());
    }

    string numerator = readNumberToken(stream, "a'");
    string denominator = readNumberToken(stream, "b'");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after witness");
    }
    validateWitness(stream, numerator, denominator);
    return {true, numerator, denominator};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long a = inf.readLong(1, 999999999999999999LL, "a");
    long long b = inf.readLong(1, 999999999999999999LL, "b");
    c = inf.readLong(1, 999999999999999999LL, "c");
    d = inf.readLong(1, 999999999999999999LL, "d");
    aStr = to_string(a);
    bStr = to_string(b);

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a possible witness but participant says impossible");
        }
        quitf(_ok, "valid witness %s/%s",
              participant.numerator.c_str(), participant.denominator.c_str());
    }

    if (participant.possible) {
        quitf(_fail, "participant found valid witness %s/%s while jury says impossible",
              participant.numerator.c_str(), participant.denominator.c_str());
    }

    quitf(_ok, "both outputs say impossible");
}
