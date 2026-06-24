#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    vector<int> stack;
};

struct Answer {
    vector<vector<int>> flips;
};

static vector<CaseData> cases;

static int maxFlips(int n) {
    return max(0, 2 * n - 3);
}

static Answer readAnswer(InStream& stream) {
    Answer answer;

    for (int tc = 1; tc <= int(cases.size()); ++tc) {
        const CaseData& data = cases[tc - 1];
        setTestCase(tc);

        int k = stream.readInt(0, maxFlips(data.n), "K");
        vector<int> stack = data.stack;
        vector<int> flips;

        for (int i = 0; i < k; ++i) {
            stream.readSpace();
            int flip = stream.readInt(1, data.n, format("flip[%d]", i + 1).c_str());
            reverse(stack.begin(), stack.begin() + flip);
            flips.push_back(flip);
        }
        stream.readEoln();

        for (int i = 0; i < data.n; ++i) {
            if (stack[i] != i + 1) {
                stream.quitf(_wa,
                             "case %d is not sorted after %d flips: position %d has %d",
                             tc,
                             k,
                             i + 1,
                             stack[i]);
            }
        }

        answer.flips.push_back(flips);
    }

    stream.readEof();
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);

    for (int tc = 1; tc <= t; ++tc) {
        int n = inf.readInt();
        cases[tc - 1].n = n;
        cases[tc - 1].stack.resize(n);

        for (int i = 0; i < n; ++i) {
            cases[tc - 1].stack[i] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);
    (void)jury;

    quitf(_ok,
          "%d case%s sorted with valid flip certificates",
          int(participant.flips.size()),
          participant.flips.size() == 1 ? "" : "s");
}
