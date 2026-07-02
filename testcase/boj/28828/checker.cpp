#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

const long long TOLERANCE = 1000000LL;

struct Answer {
    string digits;
};

Answer readAnswer(InStream& stream) {
    string token = stream.readToken("[0-9]+", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    size_t firstNonZero = token.find_first_not_of('0');
    if (firstNonZero == string::npos) {
        return {"0"};
    }
    return {token.substr(firstNonZero)};
}

bool withinTolerance(const string& a, const string& b) {
    const string* larger = &a;
    const string* smaller = &b;
    if (a.size() < b.size() || (a.size() == b.size() && a < b)) {
        larger = &b;
        smaller = &a;
    }

    if (larger->size() > smaller->size() + 7) {
        return false;
    }

    long long diff = 0;
    int i = (int)larger->size() - 1;
    int j = (int)smaller->size() - 1;
    int borrow = 0;
    long long place = 1;

    while (i >= 0) {
        int digit = (*larger)[i] - '0' - borrow;
        int subtrahend = j >= 0 ? (*smaller)[j] - '0' : 0;
        if (digit < subtrahend) {
            digit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        int resultDigit = digit - subtrahend;
        if (place <= TOLERANCE + 1) {
            diff += resultDigit * place;
            if (diff > TOLERANCE) {
                return false;
            }
        } else if (resultDigit != 0) {
            return false;
        }

        if (place <= TOLERANCE + 1) {
            place *= 10;
        }
        --i;
        --j;
    }

    return diff <= TOLERANCE;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!withinTolerance(jury.digits, participant.digits)) {
        quitf(_wa,
              "answer differs from jury answer by more than %lld: jury=%s participant=%s",
              TOLERANCE,
              jury.digits.c_str(),
              participant.digits.c_str());
    }

    quitf(_ok, "answer is within %lld of jury answer", TOLERANCE);
}
