#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int INF_SCORE = 1000000000;

int n;
vector<int> limitScore;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    string first = stream.readToken();

    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> height(n);
    vector<int> seen(n + 1, 0);

    long long parsed = stringToLongLong(stream, first);
    if (parsed < 1 || parsed > n) {
        stream.quitf(_wa, "height[1] is %lld, outside [1, %d]", parsed, n);
    }
    height[0] = parsed;
    seen[height[0]] = 1;

    for (int i = 1; i < n; ++i) {
        height[i] = stream.readInt(1, n, format("height[%d]", i + 1).c_str());
        if (seen[height[i]]) {
            stream.quitf(_wa, "height %d appears more than once", height[i]);
        }
        seen[height[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after height array");
    }

    vector<int> stack;
    vector<int> score(n, INF_SCORE);
    stack.reserve(n);
    for (int i = n - 1; i >= 0; --i) {
        while (!stack.empty() && height[stack.back()] < height[i]) {
            stack.pop_back();
        }
        if (!stack.empty()) {
            score[i] = stack.back() - i;
        }
        stack.push_back(i);
    }

    for (int i = 0; i < n; ++i) {
        if (limitScore[i] < 0) {
            int upper = -limitScore[i];
            if (score[i] > upper) {
                stream.quitf(_wa,
                             "position %d has visibility score %d, expected at most %d",
                             i + 1,
                             score[i],
                             upper);
            }
        } else {
            int lower = limitScore[i];
            if (score[i] < lower) {
                stream.quitf(_wa,
                             "position %d has visibility score %d, expected at least %d",
                             i + 1,
                             score[i],
                             lower);
            }
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    limitScore.resize(n);
    for (int i = 0; i < n; ++i) {
        limitScore[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid arrangement while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury has a valid arrangement");
    }

    quitf(_ok, "valid arrangement");
}
