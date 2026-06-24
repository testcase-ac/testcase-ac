#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    vector<int> positions;
    vector<int> divisors;
};

vector<string> inputs;

string eraseDigit(const string& value, int position) {
    if (position == 0) {
        return value;
    }
    string result = value;
    result.erase(result.begin() + position - 1);
    return result;
}

long long decimalMod(const string& value, int divisor) {
    long long rem = 0;
    for (char digit : value) {
        rem = (rem * 10 + digit - '0') % divisor;
    }
    return rem;
}

bool decimalGreaterThanInt(const string& value, int limit) {
    string bound = to_string(limit);
    if (value.size() != bound.size()) {
        return value.size() > bound.size();
    }
    return value > bound;
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.positions.resize(inputs.size());
    claim.divisors.resize(inputs.size());

    for (int tc = 0; tc < static_cast<int>(inputs.size()); ++tc) {
        int len = static_cast<int>(inputs[tc].size());
        int position = stream.readInt(0, len, format("position[%d]", tc + 1).c_str());
        stream.readSpace();
        int divisor = stream.readInt(2, 1000000000, format("divisor[%d]", tc + 1).c_str());
        stream.readEoln();

        string result = eraseDigit(inputs[tc], position);
        if (!decimalGreaterThanInt(result, divisor)) {
            stream.quitf(_wa,
                         "divisor[%d]=%d is not smaller than the resulting number",
                         tc + 1,
                         divisor);
        }
        if (decimalMod(result, divisor) != 0) {
            stream.quitf(_wa,
                         "divisor[%d]=%d does not divide the resulting number",
                         tc + 1,
                         divisor);
        }

        claim.positions[tc] = position;
        claim.divisors[tc] = divisor;
    }

    stream.readEof();
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    inputs.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        inputs[tc] = inf.readToken();
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "all %d certificates are valid", t);
}
