#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>

#include <sstream>
#include <string>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

const long long LIMIT = 1000000000000000000LL;

struct TestCase {
    int n;
    int k;
    cpp_int sum;
    cpp_int squareSum;
};

struct Answer {
    bool impossible;
    vector<long long> added;
};

long long parseLongLongToken(InStream& stream, const string& token, const string& name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }

    int pos = 0;
    bool negative = false;
    if (token[pos] == '-') {
        negative = true;
        ++pos;
    } else if (token[pos] == '+') {
        ++pos;
    }
    if (pos == (int)token.size()) {
        stream.quitf(_wa, "%s is not an integer", name.c_str());
    }

    cpp_int value = 0;
    for (; pos < (int)token.size(); ++pos) {
        if (token[pos] < '0' || token[pos] > '9') {
            stream.quitf(_wa, "%s is not an integer", name.c_str());
        }
        value = value * 10 + (token[pos] - '0');
    }
    if (negative) {
        value = -value;
    }

    if (value < -LIMIT || value > LIMIT) {
        stream.quitf(_wa, "%s=%s is outside [-10^18, 10^18]", name.c_str(), token.c_str());
    }
    return value.convert_to<long long>();
}

bool isSquaryAfterAdding(const TestCase& tc, const vector<long long>& added) {
    cpp_int sum = tc.sum;
    cpp_int squareSum = tc.squareSum;
    for (long long value : added) {
        sum += value;
        squareSum += cpp_int(value) * value;
    }
    return sum * sum == squareSum;
}

Answer readAnswer(InStream& stream, const TestCase& tc, int caseNo) {
    string caseWord = stream.readToken("Case", format("case[%d] label", caseNo).c_str());
    (void)caseWord;

    string numberToken = stream.readToken(format("#%d:", caseNo), format("case[%d] number", caseNo).c_str());
    (void)numberToken;

    string line = stream.readLine();
    istringstream iss(line);

    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        stream.quitf(_wa, "case %d has no answer", caseNo);
    }
    if (tokens[0] == "IMPOSSIBLE") {
        if (tokens.size() != 1) {
            stream.quitf(_wa, "case %d has extra output after IMPOSSIBLE", caseNo);
        }
        return {true, {}};
    }

    if ((int)tokens.size() > tc.k) {
        stream.quitf(_wa, "case %d adds %d elements, exceeding K=%d", caseNo, (int)tokens.size(), tc.k);
    }
    if (tokens.empty()) {
        stream.quitf(_wa, "case %d adds no elements", caseNo);
    }

    vector<long long> added;
    for (int i = 0; i < (int)tokens.size(); ++i) {
        added.push_back(parseLongLongToken(stream, tokens[i], format("case[%d].z[%d]", caseNo, i + 1)));
    }

    if (!isSquaryAfterAdding(tc, added)) {
        stream.quitf(_wa, "case %d witness does not make the list squary", caseNo);
    }

    return {false, added};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> tests(t);
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        TestCase& tc = tests[caseNo - 1];
        tc.n = inf.readInt();
        tc.k = inf.readInt();
        tc.sum = 0;
        tc.squareSum = 0;
        for (int i = 0; i < tc.n; ++i) {
            long long value = inf.readInt();
            tc.sum += value;
            tc.squareSum += cpp_int(value) * value;
        }
    }

    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        const TestCase& tc = tests[caseNo - 1];
        Answer jury = readAnswer(ans, tc, caseNo);
        Answer participant = readAnswer(ouf, tc, caseNo);

        if (jury.impossible) {
            if (participant.impossible) {
                continue;
            }
            quitf(_fail, "case %d: participant found a valid witness while jury reports IMPOSSIBLE", caseNo);
        }

        if (participant.impossible) {
            quitf(_wa, "case %d: participant reports IMPOSSIBLE, but jury has a valid witness", caseNo);
        }
    }

    ans.readEof();
    ouf.readEof();

    quitf(_ok, "all %d cases are valid", t);
}
