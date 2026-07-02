#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isPalindrome(const string& s) {
    for (int i = 0, j = static_cast<int>(s.size()) - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

string addDecimal(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i--] - '0';
        }
        if (j >= 0) {
            sum += b[j--] - '0';
        }
        result.push_back(static_cast<char>('0' + (sum % 10)));
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}

void readDecomposition(InStream& stream, const string& target, int testCase) {
    int k = stream.readInt(1, 25, format("k[%d]", testCase).c_str());
    stream.readEoln();

    string sum = "0";
    for (int i = 1; i <= k; ++i) {
        string term = stream.readToken("[1-9][0-9]{0,99999}",
                                       format("palindrome[%d][%d]", testCase, i).c_str());
        stream.readEoln();

        if (!isPalindrome(term)) {
            stream.quitf(_wa, "palindrome[%d][%d] is not a palindrome", testCase, i);
        }
        sum = addDecimal(sum, term);
        if (sum.size() > target.size() ||
            (sum.size() == target.size() && sum > target)) {
            stream.quitf(_wa,
                         "sum exceeds target in test case %d after %d terms: sum=%s target=%s",
                         testCase,
                         i,
                         sum.c_str(),
                         target.c_str());
        }
    }

    if (sum != target) {
        stream.quitf(_wa,
                     "sum mismatch in test case %d: expected %s, found %s",
                     testCase,
                     target.c_str(),
                     sum.c_str());
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int z = inf.readInt();
    vector<string> targets(z);
    for (int tc = 0; tc < z; ++tc) {
        targets[tc] = inf.readToken();
    }

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);
        readDecomposition(ans, targets[tc - 1], tc);
        readDecomposition(ouf, targets[tc - 1], tc);
    }

    ans.readEof();
    ouf.readEof();

    quitf(_ok, "all %d decomposition(s) are valid", z);
}
