#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<int> primes;
};

vector<int> inputs;
vector<int> smallPrimes;

void buildSmallPrimes() {
    vector<bool> composite(10001, false);
    for (int i = 2; i <= 10000; ++i) {
        if (composite[i]) {
            continue;
        }
        smallPrimes.push_back(i);
        if (1LL * i * i <= 10000) {
            for (int j = i * i; j <= 10000; j += i) {
                composite[j] = true;
            }
        }
    }
}

bool isPrime(int value) {
    if (value < 2) {
        return false;
    }
    for (int prime : smallPrimes) {
        if (1LL * prime * prime > value) {
            break;
        }
        if (value % prime == 0) {
            return value == prime;
        }
    }
    return true;
}

int parsePrimeToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
        }
    }

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > 100000000LL) {
            stream.quitf(_wa, "%s is out of range: %s", name, token.c_str());
        }
    }
    if (value < 1) {
        stream.quitf(_wa, "%s is out of range: %s", name, token.c_str());
    }
    if (!isPrime(static_cast<int>(value))) {
        stream.quitf(_wa, "%s is not prime: %lld", name, value);
    }
    return static_cast<int>(value);
}

void readLineEnd(InStream& stream, int caseIndex) {
    if (!stream.seekEoln()) {
        stream.quitf(_wa, "extra output on line %d", caseIndex);
    }
}

Claim readClaim(InStream& stream, int expectedSum, int caseIndex) {
    string first = stream.readWord();
    if (first == "Impossible.") {
        readLineEnd(stream, caseIndex);
        return {true, {}};
    }

    vector<int> values(4);
    values[0] = parsePrimeToken(stream, first, format("answer[%d][1]", caseIndex).c_str());
    for (int i = 1; i < 4; ++i) {
        string token = stream.readWord();
        values[i] = parsePrimeToken(stream, token, format("answer[%d][%d]", caseIndex, i + 1).c_str());
    }
    readLineEnd(stream, caseIndex);

    long long sum = 0;
    for (int value : values) {
        sum += value;
    }
    if (sum != expectedSum) {
        stream.quitf(_wa,
                     "line %d sums to %lld instead of %d",
                     caseIndex,
                     sum,
                     expectedSum);
    }

    return {false, values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    buildSmallPrimes();

    while (!inf.seekEof()) {
        int value = inf.readInt(1, 100000000, "n");
        inputs.push_back(value);
        inf.readEoln();
    }

    for (int caseIndex = 1; caseIndex <= static_cast<int>(inputs.size()); ++caseIndex) {
        int expectedSum = inputs[caseIndex - 1];
        Claim jury = readClaim(ans, expectedSum, caseIndex);
        Claim participant = readClaim(ouf, expectedSum, caseIndex);

        if (jury.impossible) {
            if (!participant.impossible) {
                quitf(_fail, "participant found a valid witness on line %d but jury says impossible", caseIndex);
            }
            continue;
        }

        if (participant.impossible) {
            quitf(_wa, "line %d says impossible but jury provides a valid witness", caseIndex);
        }
    }

    ans.readEof();
    ouf.readEof();
    quitf(_ok, "%d line(s) checked", static_cast<int>(inputs.size()));
}
