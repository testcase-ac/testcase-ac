#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

const array<array<int, 7>, 10> DIGIT = {{
    {{1, 1, 1, 0, 1, 1, 1}},
    {{0, 0, 1, 0, 0, 1, 0}},
    {{1, 0, 1, 1, 1, 0, 1}},
    {{1, 0, 1, 1, 0, 1, 1}},
    {{0, 1, 1, 1, 0, 1, 0}},
    {{1, 1, 0, 1, 0, 1, 1}},
    {{1, 1, 0, 1, 1, 1, 1}},
    {{1, 1, 1, 0, 1, 1, 1}},
    {{1, 1, 1, 1, 1, 1, 1}},
    {{1, 1, 1, 1, 0, 1, 1}},
}};

string target;

cpp_int parseUnsignedDecimal(const string& s) {
    cpp_int value = 0;
    for (char ch : s) {
        value *= 10;
        value += ch - '0';
    }
    return value;
}

string toString(const cpp_int& value) {
    return value.convert_to<string>();
}

bool isOperandToken(const string& s) {
    if (s.size() != target.size()) {
        return false;
    }
    for (char ch : s) {
        if (ch < '1' || ch > '9') {
            return false;
        }
    }
    return true;
}

struct Answer {
    bool impossible;
    cpp_int sum;
    cpp_int product;
};

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("-1|[1-9][0-9]*", "sum or -1");
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0, 0};
    }

    string countToken = stream.readToken("[1-9][0-9]*", "operand count");
    cpp_int countBig = parseUnsignedDecimal(countToken);
    if (countBig > 1000) {
        stream.quitf(_wa, "operand count is too large: %s", countToken.c_str());
    }
    int count = countBig.convert_to<int>();
    if (count < 2) {
        stream.quitf(_wa, "operand count must be at least 2, found %d", count);
    }

    vector<string> operands(count);
    for (int i = 0; i < count; ++i) {
        operands[i] = stream.readToken("[1-9]+", format("operand[%d]", i + 1).c_str());
        if (!isOperandToken(operands[i])) {
            stream.quitf(_wa,
                         "operand[%d] must have length %d and digits 1..9",
                         i + 1,
                         int(target.size()));
        }
        if (i > 0 && operands[i - 1] > operands[i]) {
            stream.quitf(_wa, "operands are not sorted at positions %d and %d", i, i + 1);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operands");
    }

    cpp_int computedSum = 0;
    cpp_int computedProduct = 1;
    for (const string& operand : operands) {
        cpp_int value = parseUnsignedDecimal(operand);
        computedSum += value;
        computedProduct *= value;
    }

    cpp_int claimedSum = parseUnsignedDecimal(first);
    if (claimedSum != computedSum) {
        stream.quitf(_wa,
                     "claimed sum %s does not match operand sum %s",
                     first.c_str(),
                     toString(computedSum).c_str());
    }

    for (int pos = 0; pos < int(target.size()); ++pos) {
        vector<int> seen(10, 0);
        int distinct = 0;
        array<int, 7> xored{};
        for (const string& operand : operands) {
            int digit = operand[pos] - '0';
            if (!seen[digit]) {
                seen[digit] = 1;
                ++distinct;
            }
            for (int seg = 0; seg < 7; ++seg) {
                xored[seg] ^= DIGIT[digit][seg];
            }
        }

        if (distinct != 1 && distinct != count) {
            stream.quitf(_wa,
                         "column %d has neither all equal nor all different digits",
                         pos + 1);
        }

        int resultDigit = target[pos] - '0';
        if (xored != DIGIT[resultDigit]) {
            stream.quitf(_wa,
                         "digital XOR at column %d is not target digit %d",
                         pos + 1,
                         resultDigit);
        }
    }

    return {false, computedSum, computedProduct};
}

int compareObjective(const Answer& lhs, const Answer& rhs) {
    if (lhs.sum != rhs.sum) {
        return lhs.sum < rhs.sum ? -1 : 1;
    }
    if (lhs.product != rhs.product) {
        return lhs.product < rhs.product ? -1 : 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    target = inf.readToken("[1-9]+", "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report no solution");
        }
        quitf(_fail, "participant found a valid witness while jury reports -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports -1 while jury has a valid witness");
    }

    int cmp = compareObjective(participant, jury);
    if (cmp < 0) {
        quitf(_fail,
              "participant has better objective: sum=%s product=%s, jury sum=%s product=%s",
              toString(participant.sum).c_str(),
              toString(participant.product).c_str(),
              toString(jury.sum).c_str(),
              toString(jury.product).c_str());
    }
    if (cmp > 0) {
        quitf(_wa,
              "jury has better objective: jury sum=%s product=%s, participant sum=%s product=%s",
              toString(jury.sum).c_str(),
              toString(jury.product).c_str(),
              toString(participant.sum).c_str(),
              toString(participant.product).c_str());
    }

    quitf(_ok, "valid witness with optimal baseline objective");
}
