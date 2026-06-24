#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

int n;
vector<int> targetHeights;
vector<int> boughtHeights;

struct Answer {
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0LL, 300000000000000LL, "niceness");

    vector<int> fence(n);
    for (int i = 0; i < n; ++i) {
        fence[i] = stream.readInt(1, 999999999,
                                  format("fence[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after fence heights");
    }

    vector<int> sortedFence = fence;
    sort(sortedFence.begin(), sortedFence.end());
    if (sortedFence != boughtHeights) {
        stream.quitf(_wa, "fence heights are not exactly the purchased boards");
    }

    long long actual = 0;
    for (int i = 0; i + 1 < n; ++i) {
        bool targetIncreasing = targetHeights[i] < targetHeights[i + 1];
        bool fenceIncreasing = fence[i] < fence[i + 1];
        if (targetIncreasing != fenceIncreasing) {
            stream.quitf(_wa,
                         "adjacent relation differs at position %d: target %d %s %d, fence %d %s %d",
                         i + 1, targetHeights[i],
                         targetIncreasing ? "<" : ">", targetHeights[i + 1],
                         fence[i], fenceIncreasing ? "<" : ">", fence[i + 1]);
        }
        actual += abs(static_cast<long long>(fence[i]) - fence[i + 1]);
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed niceness %lld does not match fence niceness %lld",
                     claimed, actual);
    }

    return {actual};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    targetHeights.resize(n);
    boughtHeights.resize(n);
    for (int i = 0; i < n; ++i) {
        targetHeights[i] = inf.readInt();
    }
    for (int i = 0; i < n; ++i) {
        boughtHeights[i] = inf.readInt();
    }
    sort(boughtHeights.begin(), boughtHeights.end());

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa, "jury has better niceness: jury=%lld participant=%lld",
              jury.value, participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant found better niceness: jury=%lld participant=%lld",
              jury.value, participant.value);
    }
    quitf(_ok, "niceness=%lld", participant.value);
}
