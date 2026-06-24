#include "testlib.h"

#include <vector>

using namespace std;

struct Brick {
    int area;
    int height;
    int weight;
};

int n;
vector<Brick> bricks;

struct Answer {
    long long height;
};

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(1, n, "brick count");
    stream.readEoln();

    vector<int> tower(count);
    vector<int> used(n + 1, 0);
    long long totalHeight = 0;

    for (int i = 0; i < count; ++i) {
        tower[i] = stream.readInt(1, n, format("brick[%d]", i + 1).c_str());
        stream.readEoln();

        if (used[tower[i]]) {
            stream.quitf(_wa, "brick %d is used more than once", tower[i]);
        }
        used[tower[i]] = 1;
        totalHeight += bricks[tower[i]].height;
    }

    stream.readEof();

    for (int i = 0; i + 1 < count; ++i) {
        int upper = tower[i];
        int lower = tower[i + 1];
        if (bricks[upper].area >= bricks[lower].area) {
            stream.quitf(_wa,
                         "brick %d above brick %d has invalid areas: %d >= %d",
                         upper,
                         lower,
                         bricks[upper].area,
                         bricks[lower].area);
        }
        if (bricks[upper].weight >= bricks[lower].weight) {
            stream.quitf(_wa,
                         "brick %d above brick %d has invalid weights: %d >= %d",
                         upper,
                         lower,
                         bricks[upper].weight,
                         bricks[lower].weight);
        }
    }

    return {totalHeight};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    bricks.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        bricks[i].area = inf.readInt();
        bricks[i].height = inf.readInt();
        bricks[i].weight = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.height < jury.height) {
        quitf(_wa,
              "jury has a taller tower: jury=%lld participant=%lld",
              jury.height,
              participant.height);
    }
    if (participant.height > jury.height) {
        quitf(_fail,
              "participant found a taller tower: jury=%lld participant=%lld",
              jury.height,
              participant.height);
    }

    quitf(_ok, "tower height=%lld", participant.height);
}
