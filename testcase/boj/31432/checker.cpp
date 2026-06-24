#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000LL;

vector<int> allowedDigits;

bool isAllowedDigit(int digit) {
    return find(allowedDigits.begin(), allowedDigits.end(), digit) != allowedDigits.end();
}

bool isPrime(long long value) {
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (long long divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

struct Answer {
    bool possible;
    string witness;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");

    for (char& ch : verdict) {
        ch = char(toupper(ch));
    }
    stream.readEoln();

    if (verdict == "NO") {
        stream.readEof();
        return {false, ""};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    string valueText = stream.readToken("[0-9]+", "witness");
    stream.readEoln();
    stream.readEof();

    if (valueText.size() > 1 && valueText[0] == '0') {
        stream.quitf(_wa, "witness has unnecessary leading zero: '%s'", valueText.c_str());
    }

    long long value = 0;
    for (char ch : valueText) {
        int digit = ch - '0';
        if (!isAllowedDigit(digit)) {
            stream.quitf(_wa, "witness uses unavailable digit %d", digit);
        }

        if (value > (LIMIT - digit) / 10) {
            stream.quitf(_wa, "witness exceeds 10^12");
        }
        value = value * 10 + digit;
    }

    if (value > LIMIT) {
        stream.quitf(_wa, "witness %lld exceeds 10^12", value);
    }
    if (isPrime(value)) {
        stream.quitf(_wa, "witness %lld is prime", value);
    }

    return {true, valueText};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    allowedDigits.resize(n);
    for (int i = 0; i < n; ++i) {
        allowedDigits[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail,
              "participant found valid witness '%s' while jury says NO",
              participant.witness.c_str());
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid witness but participant says NO");
    }

    quitf(_ok, jury.possible ? "valid witness '%s'" : "both outputs say NO",
          participant.witness.c_str());
}
