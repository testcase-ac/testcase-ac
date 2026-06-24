#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

long long n;

long long readPositiveNumber(InStream& stream, int index) {
    string token = stream.readToken("[0-9]+", format("term[%d]", index).c_str());

    if (token.size() > 1 && token[0] == '0') {
        stream.quitf(_wa, "term[%d] has a leading zero", index);
    }
    if (token == "0") {
        stream.quitf(_wa, "term[%d] is not positive", index);
    }

    string reversed = token;
    reverse(reversed.begin(), reversed.end());
    if (token != reversed) {
        stream.quitf(_wa, "term[%d] is not palindromic", index);
    }

    __int128 value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > n) {
            stream.quitf(_wa, "term[%d] exceeds n", index);
        }
    }

    return static_cast<long long>(value);
}

void readAnswer(InStream& stream) {
    int k = stream.readInt(1, 10, "k");
    stream.readEoln();

    __int128 sum = 0;
    for (int i = 1; i <= k; ++i) {
        long long term = readPositiveNumber(stream, i);
        sum += term;
        if (sum > n) {
            stream.quitf(_wa, "partial sum after term[%d] exceeds n", i);
        }
        stream.readEoln();
    }
    stream.readEof();

    if (sum != n) {
        stream.quitf(_wa, "sum is %lld instead of %lld", static_cast<long long>(sum), n);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1LL, 999999999999999999LL, "n");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid decomposition");
}
