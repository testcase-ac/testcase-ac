#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Answer {
    vector<int> h;
    long long score;
};

long long bounceSum(const vector<int>& h) {
    long long total = 0;

    for (int i = 0; i < n; ++i) {
        long long left = 0;
        long long right = 0;

        for (int j = 0; j < i; ++j) {
            if (h[j] > h[i]) {
                left += h[j] - h[i];
            }
        }
        for (int j = i + 1; j < n; ++j) {
            if (h[j] > h[i]) {
                right += h[j] - h[i];
            }
        }

        total += 2 * min(left, right) + (right > left ? 1 : 0);
    }

    return total;
}

Answer readAnswer(InStream& stream) {
    vector<int> h(n);
    vector<bool> seen(n + 1, false);

    for (int i = 0; i < n; ++i) {
        h[i] = stream.readInt(1, n, format("H[%d]", i + 1).c_str());
        if (seen[h[i]]) {
            stream.quitf(_wa, "height %d appears more than once", h[i]);
        }
        seen[h[i]] = true;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d heights", n);
    }

    return {h, bounceSum(h)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 5000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.score < jury.score) {
        quitf(_wa, "jury has better score: jury=%lld participant=%lld",
              jury.score, participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant found better score: jury=%lld participant=%lld",
              jury.score, participant.score);
    }

    quitf(_ok, "score=%lld", participant.score);
}
