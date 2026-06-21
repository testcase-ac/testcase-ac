#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxN = 300000;
constexpr long long kMod = 1000000007LL;

bool isNumberToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    if (token.size() > 1 && token[0] == '0') {
        return false;
    }

    long long value = 0;
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
        value = value * 10 + (ch - '0');
        if (value >= kMod) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, kMaxN, "n");
    inf.readEoln();

    vector<bool> groupHasToken;
    groupHasToken.reserve(n);
    bool hasTopLevelToken = false;

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        string token = inf.readToken("[^ ]+", "token");
        if (token == "(") {
            if (!groupHasToken.empty()) {
                groupHasToken.back() = true;
            } else {
                hasTopLevelToken = true;
            }
            groupHasToken.push_back(false);
        } else if (token == ")") {
            ensuref(!groupHasToken.empty(), "closing parenthesis at token %d has no matching opening parenthesis", i + 1);
            ensuref(groupHasToken.back(), "empty parenthesized group ending at token %d", i + 1);
            groupHasToken.pop_back();
            if (!groupHasToken.empty()) {
                groupHasToken.back() = true;
            } else {
                hasTopLevelToken = true;
            }
        } else {
            ensuref(isNumberToken(token), "token %d is neither a parenthesis nor an integer in [0, 1000000006]: %s", i + 1, token.c_str());
            if (!groupHasToken.empty()) {
                groupHasToken.back() = true;
            } else {
                hasTopLevelToken = true;
            }
        }
    }

    inf.readEoln();
    ensuref(groupHasToken.empty(), "unclosed opening parenthesis");
    ensuref(hasTopLevelToken, "bracket sequence must not be empty");
    inf.readEof();
}
