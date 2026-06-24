#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    vector<string> multiples;
};

vector<int> cases;

int remainderOf(const string& value, int divisor) {
    int remainder = 0;
    for (char digit : value) {
        remainder = (remainder * 10 + (digit - '0')) % divisor;
    }
    return remainder;
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.multiples.reserve(cases.size());

    for (int i = 0; i < int(cases.size()); ++i) {
        string value = stream.readToken();
        if (value.empty()) {
            stream.quitf(_wa, "answer[%d] is empty", i + 1);
        }
        if (int(value.size()) > 100) {
            stream.quitf(_wa, "answer[%d] has length %d, expected at most 100", i + 1, int(value.size()));
        }
        if (value[0] == '0') {
            stream.quitf(_wa, "answer[%d] is not positive", i + 1);
        }
        for (char digit : value) {
            if (digit != '0' && digit != '1') {
                stream.quitf(_wa, "answer[%d] contains digit '%c', expected only 0 or 1", i + 1, digit);
            }
        }
        if (remainderOf(value, cases[i]) != 0) {
            stream.quitf(_wa, "answer[%d]=%s is not divisible by n=%d", i + 1, value.c_str(), cases[i]);
        }
        claim.multiples.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", int(cases.size()));
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while (true) {
        int n = inf.readInt();
        if (n == 0) {
            break;
        }
        cases.push_back(n);
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);
    (void)jury;

    quitf(_ok, "%d valid binary multiples", int(participant.multiples.size()));
}
