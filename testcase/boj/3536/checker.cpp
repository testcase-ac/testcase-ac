#include "testlib.h"

#include <vector>

using namespace std;

struct Plan {
    int episodes;
};

int n;

Plan readPlan(InStream& stream) {
    int k = stream.readInt(0, 20000, "k");

    vector<int> knowsTruth(n + 1, 0);
    vector<vector<int>> seen(n + 1, vector<int>(2 * n + 1, 0));
    int lastType = -1;

    for (int i = 0; i < k; ++i) {
        int a = stream.readInt(1, n, format("episode[%d].A", i + 1).c_str());
        int b = stream.readInt(-n, n, format("episode[%d].B", i + 1).c_str());

        int type = 0;
        if (b > 0) {
            type = 1;
        } else if (b < 0) {
            type = 2;
        }

        if (type == lastType) {
            stream.quitf(_wa, "episodes %d and %d have the same type %d", i, i + 1, type + 1);
        }
        lastType = type;

        int factIndex = b + n;
        if (seen[a][factIndex]) {
            stream.quitf(_wa, "character %d finds out fact %d more than once", a, b);
        }
        seen[a][factIndex] = 1;

        if (b == 0) {
            if (knowsTruth[a]) {
                stream.quitf(_wa, "character %d already knows the truth before episode %d", a, i + 1);
            }
            knowsTruth[a] = 1;
        } else if (b > 0) {
            if (!knowsTruth[b]) {
                stream.quitf(_wa, "episode %d claims character %d knows the truth", i + 1, b);
            }
        } else {
            int target = -b;
            if (knowsTruth[target]) {
                stream.quitf(_wa, "episode %d claims character %d does not know the truth", i + 1, target);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d episodes", k);
    }
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");

    Plan jury = readPlan(ans);
    Plan participant = readPlan(ouf);

    if (participant.episodes < jury.episodes) {
        quitf(_wa, "participant has fewer episodes: expected %d, found %d", jury.episodes, participant.episodes);
    }
    if (participant.episodes > jury.episodes) {
        quitf(_fail, "participant found a longer valid plan: jury=%d participant=%d", jury.episodes, participant.episodes);
    }

    quitf(_ok, "valid plan with %d episodes", participant.episodes);
}
