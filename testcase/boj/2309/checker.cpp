#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

vector<int> heights;
set<int> heightSet;

vector<int> readAnswer(InStream& stream) {
    vector<int> answer(7);
    int sum = 0;

    for (int i = 0; i < 7; ++i) {
        answer[i] = stream.readInt(1, 100, format("height[%d]", i + 1).c_str());
        stream.readEoln();

        if (!heightSet.count(answer[i])) {
            stream.quitf(_wa, "height[%d]=%d is not present in the input", i + 1, answer[i]);
        }
        if (i > 0 && answer[i - 1] >= answer[i]) {
            stream.quitf(_wa,
                         "heights are not strictly increasing at positions %d and %d: %d, %d",
                         i,
                         i + 1,
                         answer[i - 1],
                         answer[i]);
        }
        sum += answer[i];
    }

    stream.readEof();

    if (sum != 100) {
        stream.quitf(_wa, "selected heights sum to %d instead of 100", sum);
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    heights.resize(9);
    for (int i = 0; i < 9; ++i) {
        heights[i] = inf.readInt();
        heightSet.insert(heights[i]);
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid seven-dwarf selection");
}
