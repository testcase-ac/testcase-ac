#include "testlib.h"

#include <string>

using namespace std;

string inputA;
int targetS;

struct Answer {
    int plusCount;
};

Answer readAnswer(InStream& stream) {
    string expr = stream.readToken("[0-9+=]+", "corrected equation");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after corrected equation");
    }

    size_t eq = expr.find('=');
    if (eq == string::npos || expr.find('=', eq + 1) != string::npos) {
        stream.quitf(_wa, "equation must contain exactly one '='");
    }
    if (eq == 0) {
        stream.quitf(_wa, "left side is empty");
    }

    string right = expr.substr(eq + 1);
    if (right != to_string(targetS)) {
        stream.quitf(_wa, "right side is '%s', expected '%d'", right.c_str(), targetS);
    }

    string digits;
    long long sum = 0;
    long long current = -1;
    int plusCount = 0;
    bool expectDigit = true;

    for (size_t i = 0; i < eq; ++i) {
        char c = expr[i];
        if (c == '+') {
            if (expectDigit) {
                stream.quitf(_wa, "empty term before position %d", int(i + 1));
            }
            sum += current;
            current = -1;
            ++plusCount;
            expectDigit = true;
            continue;
        }

        if (c < '0' || c > '9') {
            stream.quitf(_wa, "invalid character '%c' on left side", c);
        }
        digits.push_back(c);
        if (digits.size() > inputA.size()) {
            stream.quitf(_wa, "left side uses more digits than input A");
        }
        if (inputA[digits.size() - 1] != c) {
            stream.quitf(_wa,
                         "left side digit %d is '%c', expected '%c'",
                         int(digits.size()),
                         c,
                         inputA[digits.size() - 1]);
        }

        if (current < 0) {
            current = 0;
        }
        current = current * 10 + (c - '0');
        if (current > targetS && targetS <= 5000) {
            stream.quitf(_wa, "term ending at digit %d is too large", int(digits.size()));
        }
        expectDigit = false;
    }

    if (expectDigit) {
        stream.quitf(_wa, "left side ends with '+'");
    }
    sum += current;

    if (digits != inputA) {
        stream.quitf(_wa, "left side digits do not match input A");
    }
    if (sum != targetS) {
        stream.quitf(_wa, "left side sums to %lld, expected %d", sum, targetS);
    }

    return {plusCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string input = inf.readToken("[1-9][0-9]{0,999}=[1-9][0-9]*", "input equation");
    if (!inf.seekEof()) {
        quitf(_fail, "extra data after input equation");
    }

    size_t eq = input.find('=');
    inputA = input.substr(0, eq);
    targetS = stoi(input.substr(eq + 1));

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.plusCount > jury.plusCount) {
        quitf(_wa,
              "too many plus signs: participant=%d jury=%d",
              participant.plusCount,
              jury.plusCount);
    }
    if (participant.plusCount < jury.plusCount) {
        quitf(_fail,
              "participant found a better answer: participant=%d jury=%d",
              participant.plusCount,
              jury.plusCount);
    }

    quitf(_ok, "plus signs=%d", participant.plusCount);
}
