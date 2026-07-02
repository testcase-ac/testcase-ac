#include "testlib.h"
#include <vector>
using namespace std;

struct Ranking {
    vector<int> order;
    long long cost;
};

int n, k;
vector<vector<int>> inputPosition;

Ranking readRanking(InStream& stream) {
    Ranking result;
    result.order.resize(n + 1);
    vector<int> outputPosition(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int value = stream.readInt(1, n, format("ranking[%d]", i).c_str());
        if (outputPosition[value] != 0) {
            stream.quitf(_wa,
                         "result %d appears more than once at positions %d and %d",
                         value,
                         outputPosition[value],
                         i);
        }
        outputPosition[value] = i;
        result.order[i] = value;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after ranking");
    }

    result.cost = 0;
    for (int value = 1; value <= n; ++value) {
        for (int engine = 0; engine < k; ++engine) {
            long long diff = outputPosition[value] - inputPosition[engine][value];
            result.cost += diff * diff;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    inputPosition.assign(k, vector<int>(n + 1));

    for (int engine = 0; engine < k; ++engine) {
        for (int position = 1; position <= n; ++position) {
            int value = inf.readInt();
            inputPosition[engine][value] = position;
        }
    }

    Ranking jury = readRanking(ans);
    Ranking participant = readRanking(ouf);

    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found a better ranking: jury cost is %lld, participant cost is %lld",
              jury.cost,
              participant.cost);
    }
    if (participant.cost > jury.cost) {
        quitf(_wa,
              "ranking cost is %lld, but jury cost is %lld",
              participant.cost,
              jury.cost);
    }

    quitf(_ok, "ranking cost is %lld", participant.cost);
}
