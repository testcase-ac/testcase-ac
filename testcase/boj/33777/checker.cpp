#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    string parity;
};

struct Answer {
    vector<bool> possible;
};

string upperToken(const string& token) {
    string result = token;
    for (char& ch : result) {
        ch = (char)toupper((unsigned char)ch);
    }
    return result;
}

Answer readAnswer(InStream& stream, const vector<TestCase>& cases) {
    Answer answer;
    answer.possible.resize(cases.size());

    for (int tc = 0; tc < (int)cases.size(); ++tc) {
        const int n = cases[tc].n;
        const string& parity = cases[tc].parity;

        string verdict = upperToken(stream.readToken("[A-Za-z]+", format("verdict[%d]", tc + 1).c_str()));
        if (verdict != "YES" && verdict != "NO") {
            stream.quitf(_wa, "case %d has verdict '%s', expected YES or NO", tc + 1, verdict.c_str());
        }

        if (verdict == "NO") {
            answer.possible[tc] = false;
            continue;
        }
        answer.possible[tc] = true;

        vector<int> used(2 * n + 1, 0);
        long long previousSum = -1;
        for (int i = 0; i < n; ++i) {
            int first = stream.readInt(1, 2 * n, format("dish[%d][1]", i + 1).c_str());
            int second = stream.readInt(1, 2 * n, format("dish[%d][2]", i + 1).c_str());

            if (used[first]) {
                stream.quitf(_wa, "case %d repeats dish %d", tc + 1, first);
            }
            if (used[second]) {
                stream.quitf(_wa, "case %d repeats dish %d", tc + 1, second);
            }
            used[first] = used[second] = 1;

            long long sum = (long long)first + second;
            int expectedParity = parity[i] == 'O' ? 1 : 0;
            if ((sum & 1LL) != expectedParity) {
                stream.quitf(_wa,
                             "case %d beaver %d has satisfaction %lld with wrong parity",
                             tc + 1,
                             i + 1,
                             sum);
            }
            if (sum < previousSum) {
                stream.quitf(_wa,
                             "case %d satisfaction decreases at beaver %d: previous=%lld current=%lld",
                             tc + 1,
                             i + 1,
                             previousSum,
                             sum);
            }
            previousSum = sum;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after all test cases");
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> cases(t);
    for (int tc = 0; tc < t; ++tc) {
        cases[tc].n = inf.readInt();
        cases[tc].parity = inf.readToken();
    }

    Answer jury = readAnswer(ans, cases);
    Answer participant = readAnswer(ouf, cases);

    for (int tc = 0; tc < t; ++tc) {
        if (!jury.possible[tc]) {
            if (participant.possible[tc]) {
                quitf(_fail, "case %d: participant found a valid assignment while jury answered NO", tc + 1);
            }
            continue;
        }

        if (!participant.possible[tc]) {
            quitf(_wa, "case %d: jury has a valid assignment but participant answered NO", tc + 1);
        }
    }

    quitf(_ok, "valid assignment");
}
