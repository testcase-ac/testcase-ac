#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
string mode;
vector<bool> composite;

struct Answer {
    int score;
};

Answer readAnswer(InStream& stream) {
    vector<int> path(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        path[i] = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
        if (seen[path[i]]) {
            stream.quitf(_wa, "path[%d]=%d is repeated", i + 1, path[i]);
        }
        seen[path[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    int score = 0;
    for (int i = 0; i < n; ++i) {
        int sum = path[i] + path[(i + 1) % n];
        bool isOrder = composite[sum];
        if ((mode == "order" && isOrder) || (mode == "chaos" && !isOrder)) {
            ++score;
        }
    }

    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    mode = inf.readToken("order|chaos", "S");
    n = inf.readInt(2, 888888, "N");

    int maxSum = 2 * n;
    composite.assign(maxSum + 1, false);
    for (int p = 2; p <= maxSum / p; ++p) {
        if (!composite[p]) {
            for (int q = p * p; q <= maxSum; q += p) {
                composite[q] = true;
            }
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.score < jury.score) {
        quitf(_wa, "jury has better score: jury=%d participant=%d", jury.score, participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant found better score: jury=%d participant=%d", jury.score, participant.score);
    }
    quitf(_ok, "score=%d", participant.score);
}
