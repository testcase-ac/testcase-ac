#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    string sequence;
};

string readInputSequence() {
    string s = inf.readLine("[()\\[\\]]{0,100}", "input sequence");
    inf.readEof();
    return s;
}

bool isOpening(char c) {
    return c == '(' || c == '[';
}

bool matches(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']');
}

bool isRegularBracketSequence(const string& sequence) {
    vector<char> stack;
    for (char c : sequence) {
        if (isOpening(c)) {
            stack.push_back(c);
        } else {
            if (stack.empty() || !matches(stack.back(), c)) {
                return false;
            }
            stack.pop_back();
        }
    }
    return stack.empty();
}

bool containsSubsequence(const string& sequence, const string& target) {
    size_t at = 0;
    for (char c : sequence) {
        if (at < target.size() && c == target[at]) {
            ++at;
        }
    }
    return at == target.size();
}

Claim readClaim(InStream& stream, const string& input) {
    string sequence = stream.readLine("[()\\[\\]]*", "bracket sequence");
    stream.readEof();

    if (!isRegularBracketSequence(sequence)) {
        stream.quitf(_wa, "output is not a regular bracket sequence");
    }
    if (!containsSubsequence(sequence, input)) {
        stream.quitf(_wa, "output does not contain the input as a subsequence");
    }
    return {sequence};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string input = readInputSequence();
    Claim jury = readClaim(ans, input);
    Claim participant = readClaim(ouf, input);

    if (participant.sequence.size() < jury.sequence.size()) {
        quitf(_fail,
              "participant found a shorter valid sequence: jury=%d participant=%d",
              static_cast<int>(jury.sequence.size()),
              static_cast<int>(participant.sequence.size()));
    }
    if (participant.sequence.size() > jury.sequence.size()) {
        quitf(_wa,
              "output is not shortest: jury length=%d participant length=%d",
              static_cast<int>(jury.sequence.size()),
              static_cast<int>(participant.sequence.size()));
    }
    quitf(_ok, "valid shortest sequence of length %d",
          static_cast<int>(participant.sequence.size()));
}
