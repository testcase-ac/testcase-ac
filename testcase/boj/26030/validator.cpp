#include "testlib.h"

#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;

bool isProbabilityToken(const string& token) {
    if (token.empty()) {
        return false;
    }

    int pos = 0;
    if (!isdigit(static_cast<unsigned char>(token[pos]))) {
        return false;
    }

    if (token[pos] == '0') {
        ++pos;
        if (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
            return false;
        }
    } else if (token[pos] == '1') {
        ++pos;
        if (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
            return false;
        }
    } else {
        return false;
    }

    if (pos == int(token.size())) {
        return true;
    }

    if (token[pos] != '.') {
        return false;
    }
    ++pos;

    int fractionalStart = pos;
    while (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
        ++pos;
    }

    int fractionalDigits = pos - fractionalStart;
    return pos == int(token.size()) && 1 <= fractionalDigits && fractionalDigits <= 6;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string name = "p_" + to_string(i);
        string token = inf.readToken("[^ ]{1,16}", name.c_str());
        ensuref(isProbabilityToken(token),
                "%s must be canonical real number with at most 6 digits after decimal: %s",
                name.c_str(), token.c_str());

        long double value = strtold(token.c_str(), nullptr);
        ensuref(0.5L <= value && value <= 1.0L,
                "%s must be in [0.5, 1.0]: %s",
                name.c_str(), token.c_str());

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
