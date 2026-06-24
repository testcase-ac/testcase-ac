#include "testlib.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <set>
#include <string>
#include <vector>

using boost::multiprecision::cpp_int;
using namespace std;

struct TestCase {
    int n;
    string p;
};

struct Output {
    int totalLines;
};

cpp_int parseDecimal(const string& value) {
    cpp_int result = 0;
    for (char ch : value) {
        result = result * 10 + (ch - '0');
    }
    return result;
}

Output readOutput(InStream& stream, const vector<TestCase>& tests) {
    int totalLines = 0;

    for (int tc = 0; tc < static_cast<int>(tests.size()); ++tc) {
        const int n = tests[tc].n;
        const string& p = tests[tc].p;
        set<string> seen;

        for (int i = 0; i < n; ++i) {
            string qToken = stream.readToken("[1-9][0-9]{0,99}", format("Q[%d][%d]", tc + 1, i + 1).c_str());
            stream.readSpace();
            string rToken = stream.readToken("[1-9][0-9]{0,99}", format("R[%d][%d]", tc + 1, i + 1).c_str());
            stream.readEoln();

            if (static_cast<int>(qToken.size()) != n) {
                stream.quitf(_wa, "Q[%d][%d] has %d digits, expected %d",
                             tc + 1, i + 1, static_cast<int>(qToken.size()), n);
            }
            if (!seen.insert(qToken).second) {
                stream.quitf(_wa, "Q[%d][%d]=%s is repeated in test case %d",
                             tc + 1, i + 1, qToken.c_str(), tc + 1);
            }

            int differences = 0;
            for (int pos = 0; pos < n; ++pos) {
                if (qToken[pos] != p[pos]) {
                    ++differences;
                }
            }
            if (differences != 1) {
                stream.quitf(_wa, "Q[%d][%d]=%s differs from P in %d digits, expected 1",
                             tc + 1, i + 1, qToken.c_str(), differences);
            }

            cpp_int q = parseDecimal(qToken);
            cpp_int r = parseDecimal(rToken);
            if (r < 2 || r >= q) {
                stream.quitf(_wa, "R[%d][%d]=%s is not in [2, Q)",
                             tc + 1, i + 1, rToken.c_str());
            }
            if (q % r != 0) {
                stream.quitf(_wa, "R[%d][%d]=%s does not divide Q=%s",
                             tc + 1, i + 1, rToken.c_str(), qToken.c_str());
            }

            ++totalLines;
        }
    }

    stream.readEof();
    return {totalLines};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> tests;
    tests.reserve(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        string p = inf.readToken();
        tests.push_back({n, p});
    }

    Output jury = readOutput(ans, tests);
    Output participant = readOutput(ouf, tests);
    (void)jury;

    quitf(_ok, "valid certificate output with %d lines", participant.totalLines);
}
