#include "testlib.h"

#include <deque>
#include <vector>

using namespace std;

int n;

struct Answer {
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0, (long long)4e18, "minimum decay");

    vector<int> used(2 * n + 1, 0);
    vector<deque<int>> tubes(2);
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < n; ++col) {
            int apple = stream.readInt(1, 2 * n, format("tube[%d][%d]", row + 1, col + 1).c_str());
            if (used[apple]) {
                stream.quitf(_wa, "apple %d appears more than once", apple);
            }
            used[apple] = 1;
            tubes[row].push_back(apple);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after arrangement");
    }

    long long elapsed = 0;
    long long nextDelta = 1;
    long long actual = 0;
    for (int removed = 0; removed < 2 * n; ++removed) {
        int bestTube = -1;
        bool bestFront = true;
        int bestApple = 2 * n + 1;

        for (int tube = 0; tube < 2; ++tube) {
            if (tubes[tube].empty()) {
                continue;
            }
            if (tubes[tube].front() < bestApple) {
                bestApple = tubes[tube].front();
                bestTube = tube;
                bestFront = true;
            }
            if (tubes[tube].back() < bestApple) {
                bestApple = tubes[tube].back();
                bestTube = tube;
                bestFront = false;
            }
        }

        if (bestTube == -1) {
            stream.quitf(_fail, "internal error: no apple available at removal %d", removed + 1);
        }
        actual += (long long)bestApple * elapsed;
        if (bestFront) {
            tubes[bestTube].pop_front();
        } else {
            tubes[bestTube].pop_back();
        }
        elapsed += nextDelta;
        ++nextDelta;
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed decay is %lld, but arrangement has decay %lld", claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 10000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value > jury.value) {
        quitf(_wa, "jury has better decay: jury=%lld participant=%lld", jury.value, participant.value);
    }
    if (participant.value < jury.value) {
        quitf(_fail, "participant found better decay: jury=%lld participant=%lld", jury.value, participant.value);
    }
    quitf(_ok, "decay=%lld", participant.value);
}
