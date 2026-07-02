#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>

#include <set>
#include <string>
#include <vector>

using boost::multiprecision::cpp_int;
using namespace std;

struct Output {
    vector<string> coins;
};

int n, j;

cpp_int parsePositiveInteger(const string& token, InStream& stream, const string& name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }
    if (token.size() > 1 && token[0] == '0') {
        stream.quitf(_wa, "%s has a leading zero", name.c_str());
    }

    cpp_int value = 0;
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            stream.quitf(_wa, "%s is not a base-10 integer", name.c_str());
        }
        value *= 10;
        value += ch - '0';
    }
    if (value <= 0) {
        stream.quitf(_wa, "%s must be positive", name.c_str());
    }
    return value;
}

cpp_int valueInBase(const string& coin, int base) {
    cpp_int value = 0;
    for (char ch : coin) {
        value *= base;
        value += ch - '0';
    }
    return value;
}

Output readOutput(InStream& stream) {
    string caseToken = stream.readToken("Case", "case header token");
    if (caseToken != "Case") {
        stream.quitf(_wa, "expected case header to start with Case, found '%s'", caseToken.c_str());
    }

    string caseNumber = stream.readToken("#1:", "case header number");
    if (caseNumber != "#1:") {
        stream.quitf(_wa, "expected case header number '#1:', found '%s'", caseNumber.c_str());
    }

    set<string> seen;
    vector<string> coins;
    for (int row = 1; row <= j; ++row) {
        string coin = stream.readToken(format("[01]{%d}", n).c_str(), format("coin[%d]", row).c_str());
        if (coin.front() != '1' || coin.back() != '1') {
            stream.quitf(_wa, "coin[%d] must start and end with 1", row);
        }
        if (!seen.insert(coin).second) {
            stream.quitf(_wa, "coin[%d] duplicates an earlier jamcoin", row);
        }

        for (int base = 2; base <= 10; ++base) {
            string divisorToken = stream.readToken("[0-9]+", format("divisor[%d][base=%d]", row, base).c_str());
            cpp_int divisor = parsePositiveInteger(
                divisorToken, stream, format("divisor[%d][base=%d]", row, base).c_str());
            cpp_int value = valueInBase(coin, base);
            if (divisor <= 1) {
                stream.quitf(_wa, "divisor[%d][base=%d] is trivial", row, base);
            }
            if (divisor >= value) {
                stream.quitf(_wa, "divisor[%d][base=%d] is not smaller than the represented value", row, base);
            }
            if (value % divisor != 0) {
                stream.quitf(_wa, "divisor[%d][base=%d] does not divide the represented value", row, base);
            }
        }
        coins.push_back(coin);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d jamcoins", j);
    }
    return {coins};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    if (t != 1) {
        quitf(_fail, "checker expects one test case, found %d", t);
    }
    n = inf.readInt();
    j = inf.readInt();

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    (void)jury;
    quitf(_ok, "%d valid jamcoins", static_cast<int>(participant.coins.size()));
}
