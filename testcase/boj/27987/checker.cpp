#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
int total;
vector<int> requiredCount;

struct Answer {
    int minDistance;
};

Answer readAnswer(InStream& stream) {
    vector<int> seen(n + 1, 0);
    vector<int> lastPosition(n + 1, -1);
    int minDistance = total + 1;

    for (int i = 0; i < total; ++i) {
        int value = stream.readInt(1, n, format("X[%d]", i + 1).c_str());
        ++seen[value];
        if (lastPosition[value] != -1) {
            minDistance = min(minDistance, i - lastPosition[value]);
        }
        lastPosition[value] = i;
    }

    for (int value = 1; value <= n; ++value) {
        if (seen[value] != requiredCount[value]) {
            stream.quitf(_wa,
                         "class %d appears %d times, expected %d",
                         value,
                         seen[value],
                         requiredCount[value]);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after arrangement");
    }
    return {minDistance};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    requiredCount.assign(n + 1, 0);
    total = 0;
    for (int i = 1; i <= n; ++i) {
        requiredCount[i] = inf.readInt();
        total += requiredCount[i];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.minDistance < jury.minDistance) {
        quitf(_wa,
              "jury has better minimum distance: jury=%d participant=%d",
              jury.minDistance,
              participant.minDistance);
    }
    if (participant.minDistance > jury.minDistance) {
        quitf(_fail,
              "participant found better minimum distance: jury=%d participant=%d",
              jury.minDistance,
              participant.minDistance);
    }

    quitf(_ok, "minimum distance is %d", participant.minDistance);
}
