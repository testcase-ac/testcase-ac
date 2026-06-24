#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    vector<int> answers;
    int updates;
};

int n, m;
vector<int> requiredAnswers;

int currentAnswer(const vector<int>& height) {
    int mn = *min_element(height.begin() + 1, height.end());
    int mx = *max_element(height.begin() + 1, height.end());

    int firstMin = n + 1, lastMin = 0;
    int firstMax = n + 1, lastMax = 0;
    for (int i = 1; i <= n; ++i) {
        if (height[i] == mn) {
            firstMin = min(firstMin, i);
            lastMin = max(lastMin, i);
        }
        if (height[i] == mx) {
            firstMax = min(firstMax, i);
            lastMax = max(lastMax, i);
        }
    }

    return max(abs(lastMax - firstMin), abs(lastMin - firstMax));
}

Claim readClaim(InStream& stream, TResult verdict, const char* who) {
    int q = stream.readInt(1, 8200 + m, format("%s Q", who).c_str());
    vector<int> height(n + 1, 0);
    vector<int> answers;
    int updates = 0;

    for (int i = 1; i <= q; ++i) {
        string op = stream.readToken();
        if (op == "U") {
            int x = stream.readInt(1, n, format("%s x[%d]", who, i).c_str());
            int h = stream.readInt(-10000, 10000, format("%s h[%d]", who, i).c_str());
            ++updates;
            if (updates > 8200) {
                stream.quitf(verdict, "%s uses more than 8200 updates", who);
            }
            height[x] = h;
        } else if (op == "P") {
            if ((int)answers.size() >= m) {
                stream.quitf(verdict, "%s asks more than %d questions", who, m);
            }
            answers.push_back(currentAnswer(height));
        } else {
            stream.quitf(verdict, "%s op[%d] is '%s', expected U or P", who, i, op.c_str());
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "%s has extra output", who);
    }

    if ((int)answers.size() != m) {
        stream.quitf(verdict, "%s asks %d questions, expected %d", who, (int)answers.size(), m);
    }
    for (int i = 0; i < m; ++i) {
        if (answers[i] != requiredAnswers[i]) {
            stream.quitf(verdict,
                         "%s answer[%d] is %d, expected %d",
                         who,
                         i + 1,
                         answers[i],
                         requiredAnswers[i]);
        }
    }

    return {answers, updates};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    requiredAnswers.resize(m);
    for (int i = 0; i < m; ++i) {
        requiredAnswers[i] = inf.readInt();
    }

    Claim jury = readClaim(ans, _fail, "jury");
    Claim participant = readClaim(ouf, _wa, "participant");

    if (participant.answers != jury.answers) {
        quitf(_wa, "participant transcript does not match jury transcript");
    }

    quitf(_ok, "%d questions matched using %d updates", m, participant.updates);
}
