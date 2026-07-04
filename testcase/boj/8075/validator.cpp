#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxEquations = 5;
constexpr int kMaxVariables = 26;
constexpr int kMaxExpandedSideLength = 10000;
constexpr int kMaxVariableLength = 10000;

long long expandedLength(const string& side, const vector<int>& lengths) {
    long long total = 0;
    for (char ch : side) {
        if (ch == '0' || ch == '1') {
            ++total;
        } else {
            total += lengths[ch - 'a'];
        }
    }
    return total;
}

void validateSide(const string& name, int writtenLength, int k,
                  const vector<int>& lengths) {
    string side = inf.readToken("[0-9a-z]{1,10000}", name);
    inf.readEoln();

    ensuref(static_cast<int>(side.size()) == writtenLength,
            "%s has length %d, expected %d", name.c_str(),
            static_cast<int>(side.size()), writtenLength);

    for (int i = 0; i < static_cast<int>(side.size()); ++i) {
        char ch = side[i];
        ensuref(ch == '0' || ch == '1' || (ch >= 'a' && ch < 'a' + k),
                "%s[%d] uses symbol '%c' outside digits and first %d variables",
                name.c_str(), i + 1, ch, k);
    }

    long long expanded = expandedLength(side, lengths);
    ensuref(expanded <= kMaxExpandedSideLength,
            "%s expands to %lld bits, exceeding %d", name.c_str(), expanded,
            kMaxExpandedSideLength);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, kMaxEquations, "x");
    inf.readEoln();

    for (int equation = 1; equation <= x; ++equation) {
        setTestCase(equation);

        int k = inf.readInt(0, kMaxVariables, "k");
        inf.readEoln();

        vector<int> lengths(kMaxVariables, 0);
        if (k == 0) {
            inf.readEoln();
        } else {
            for (int i = 0; i < k; ++i) {
                if (i > 0) {
                    inf.readSpace();
                }
                // CHECK: The statement bounds expanded side lengths but not
                // lengths of variables that do not appear in either side.
                lengths[i] = inf.readInt(1, kMaxVariableLength, "len_i");
            }
            inf.readEoln();
        }

        int l = inf.readInt(1, kMaxExpandedSideLength, "l");
        inf.readEoln();
        validateSide("left", l, k, lengths);

        int r = inf.readInt(1, kMaxExpandedSideLength, "r");
        inf.readEoln();
        validateSide("right", r, k, lengths);
    }

    inf.readEof();
}
