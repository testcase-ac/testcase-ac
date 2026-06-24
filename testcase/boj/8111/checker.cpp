#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct CaseAnswer {
    bool brak;
    string value;
};

vector<int> inputNumbers;

void quitInvalid(TResult verdict, const char* streamName, int caseIndex, const char* message) {
    quitf(verdict, "%s output for case %d is invalid: %s", streamName, caseIndex, message);
}

CaseAnswer readCaseAnswer(InStream& stream, TResult invalidVerdict, const char* streamName, int caseIndex) {
    string token = stream.readToken();
    int n = inputNumbers[caseIndex - 1];

    if (token == "BRAK") {
        return {true, token};
    }

    if (token.empty()) {
        quitInvalid(invalidVerdict, streamName, caseIndex, "empty token");
    }
    if (token.size() > 100) {
        quitf(invalidVerdict,
              "%s output for case %d is invalid: length %d exceeds 100",
              streamName,
              caseIndex,
              static_cast<int>(token.size()));
    }
    if (token[0] == '0') {
        quitInvalid(invalidVerdict, streamName, caseIndex, "number starts with zero");
    }

    bool hasOne = false;
    int remainder = 0;
    for (char c : token) {
        if (c != '0' && c != '1') {
            quitf(invalidVerdict,
                  "%s output for case %d is invalid: unexpected character '%c'",
                  streamName,
                  caseIndex,
                  c);
        }
        if (c == '1') {
            hasOne = true;
        }
        remainder = (remainder * 10 + (c - '0')) % n;
    }
    if (!hasOne) {
        quitInvalid(invalidVerdict, streamName, caseIndex, "number contains no digit one");
    }
    if (remainder != 0) {
        quitf(invalidVerdict,
              "%s output for case %d is invalid: %s is not divisible by %d",
              streamName,
              caseIndex,
              token.c_str(),
              n);
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    inputNumbers.resize(t);
    for (int i = 0; i < t; ++i) {
        inputNumbers[i] = inf.readInt();
    }

    vector<CaseAnswer> jury;
    jury.reserve(t);
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        jury.push_back(readCaseAnswer(ans, _fail, "jury", caseIndex));
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        CaseAnswer participant = readCaseAnswer(ouf, _wa, "participant", caseIndex);
        const CaseAnswer& expected = jury[caseIndex - 1];

        if (expected.brak && participant.brak) {
            continue;
        }
        if (expected.brak && !participant.brak) {
            quitf(_fail,
                  "participant found a valid answer for case %d, but jury says BRAK",
                  caseIndex);
        }
        if (!expected.brak && participant.brak) {
            quitf(_wa, "participant says BRAK for case %d, but jury has an answer", caseIndex);
        }
    }

    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all %d answers are valid", t);
}
