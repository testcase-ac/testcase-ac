#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const string AB_MAX = "100000000000000000000";
const string R_MAX = "9223372036854775807";

string toDecimal(__int128 value) {
    if (value == 0) {
        return "0";
    }

    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

bool lessOrEqualDecimal(const string& value, const string& upperBound) {
    if (value.size() != upperBound.size()) {
        return value.size() < upperBound.size();
    }
    return value <= upperBound;
}

string randomDecimalUpTo(const string& upperBound) {
    if (rnd.next(12) == 0) {
        return "0";
    }

    int length = rnd.next(1, int(upperBound.size()));
    string value;
    value.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < length; ++i) {
        value.push_back(char('0' + rnd.next(10)));
    }

    if (!lessOrEqualDecimal(value, upperBound)) {
        value = upperBound;
    }
    return value;
}

string randomNearMax(const string& upperBound) {
    string value = upperBound;
    int changes = rnd.next(1, 4);
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(int(value.size()));
        char lo = (pos == 0 ? '1' : '0');
        value[pos] = char(lo + rnd.next(value[pos] - lo + 1));
    }
    return value;
}

void printCase(const string& a, const string& b, const string& r) {
    println(a, b, r);
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);

    if (mode == 0) {
        string other = randomDecimalUpTo(AB_MAX);
        string r = randomDecimalUpTo(R_MAX);
        if (rnd.next(2) == 0) {
            printCase("0", other, r);
        } else {
            printCase(other, "0", r);
        }
    } else if (mode == 1) {
        long long a = rnd.next(1, 1000000);
        long long b = rnd.next(1, 1000000);
        __int128 product = (__int128)a * b;
        __int128 extra = rnd.next(0, 1000000);
        printCase(toDecimal(a), toDecimal(b), toDecimal(product + extra));
    } else if (mode == 2) {
        long long a = rnd.next(1, 1000000000);
        long long b = rnd.next(1, 1000000000);
        __int128 product = (__int128)a * b;
        __int128 r = product == 0 ? 0 : rnd.next(0, (int)min<__int128>(product - 1, 1000000000));
        printCase(toDecimal(a), toDecimal(b), toDecimal(r));
    } else if (mode == 3) {
        long long a = rnd.next(1LL, 3037000499LL);
        long long b = rnd.next(1LL, 3037000499LL);
        __int128 product = (__int128)a * b;
        if (product > 9223372036854775807LL) {
            product = 9223372036854775807LL;
        }
        __int128 delta = rnd.next(3) - 1;
        __int128 r = product + delta;
        if (r < 0) {
            r = 0;
        }
        if (r > 9223372036854775807LL) {
            r = 9223372036854775807LL;
        }
        printCase(toDecimal(a), toDecimal(b), toDecimal(r));
    } else if (mode == 4) {
        string a = randomNearMax(AB_MAX);
        string b = rnd.next(2) == 0 ? randomDecimalUpTo(AB_MAX) : randomNearMax(AB_MAX);
        if (b == "0") {
            b = "1";
        }
        printCase(a, b, randomDecimalUpTo(R_MAX));
    } else if (mode == 5) {
        vector<string> edgeA = {"1", "2", "9223372036854775807", "9223372036854775808", AB_MAX};
        vector<string> edgeB = {"1", "2", "10", "99999999999999999999", AB_MAX};
        printCase(rnd.any(edgeA), rnd.any(edgeB), rnd.any(vector<string>{"0", "1", R_MAX}));
    } else if (mode == 6) {
        long long divisor = rnd.next(1, 1000000);
        long long quotient = rnd.next(1, 1000000);
        __int128 r = (__int128)divisor * quotient + rnd.next(0LL, divisor - 1);
        printCase(toDecimal(divisor), toDecimal(quotient), toDecimal(r));
    } else {
        printCase(randomDecimalUpTo(AB_MAX), randomDecimalUpTo(AB_MAX), randomNearMax(R_MAX));
    }

    return 0;
}
