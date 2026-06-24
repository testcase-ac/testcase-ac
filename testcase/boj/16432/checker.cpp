#include "testlib.h"

#include <vector>

using namespace std;

struct Output {
    bool impossible;
    vector<int> cakes;
};

int n;
vector<vector<bool>> available;

Output readOutput(InStream& stream) {
    int first = stream.readInt(-1, 9, "answer[1]");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, {}};
    }

    if (first < 1) {
        stream.quitf(_wa, "answer[1] must be between 1 and 9, or -1");
    }

    vector<int> cakes(n);
    cakes[0] = first;
    stream.readEoln();

    for (int day = 2; day <= n; ++day) {
        cakes[day - 1] = stream.readInt(1, 9, format("answer[%d]", day).c_str());
        stream.readEoln();
    }
    stream.readEof();

    for (int day = 1; day <= n; ++day) {
        int cake = cakes[day - 1];
        if (!available[day][cake]) {
            stream.quitf(_wa, "answer[%d]=%d is not available on day %d", day, cake, day);
        }
        if (day > 1 && cakes[day - 2] == cake) {
            stream.quitf(_wa,
                         "answer[%d]=%d equals the previous day's cake",
                         day,
                         cake);
        }
    }

    return {false, cakes};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    available.assign(n + 1, vector<bool>(10, false));

    for (int day = 1; day <= n; ++day) {
        int m = inf.readInt();
        for (int i = 0; i < m; ++i) {
            int cake = inf.readInt();
            available[day][cake] = true;
        }
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report no valid sequence");
        }
        quitf(_fail, "participant found a valid sequence while jury reports -1");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid sequence but participant reports -1");
    }

    quitf(_ok, "valid sequence");
}
