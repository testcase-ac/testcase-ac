#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

vector<bool> buildPrimeTable() {
    vector<bool> prime(100001, true);
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i * i <= 100000; ++i) {
        if (!prime[i]) {
            continue;
        }
        for (int j = i * i; j <= 100000; j += i) {
            prime[j] = false;
        }
    }
    return prime;
}

bool hasPrimeSubstring(const string& s, const vector<bool>& prime) {
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        int value = 0;
        for (int len = 1; len <= 6 && i + len <= static_cast<int>(s.size()); ++len) {
            value = value * 10 + (s[i + len - 1] - '0');
            if (value > 100000) {
                break;
            }
            if (prime[value]) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<bool> prime = buildPrimeTable();

    int cases = 0;
    while (true) {
        string s = inf.readLine("[0-9]{1,255}", "s");
        if (s == "0") {
            break;
        }

        setTestCase(cases + 1);
        ++cases;
        ensuref(cases <= 1000, "number of test cases exceeds 1000");
        ensuref(hasPrimeSubstring(s, prime), "case %d has no prime substring", cases);
    }

    inf.readEof();
}
