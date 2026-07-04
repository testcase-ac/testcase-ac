#include "testlib.h"

#include <array>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxTotalMoves = 200000;
    long long totalMoves = 0;
    int cases = 0;

    while (true) {
        string line = inf.readLine("[UDLRQ]{1,200001}", "line");
        if (line == "Q") {
            break;
        }

        ++cases;
        setTestCase(cases);

        ensuref(line.back() == 'Q', "testcase %d is not terminated by Q", cases);
        ensuref(line.size() >= 2, "testcase %d has an empty move sequence", cases);
        for (int i = 0; i + 1 < static_cast<int>(line.size()); ++i) {
            ensuref(line[i] != 'Q', "testcase %d has Q before the line terminator", cases);
        }

        int moves = static_cast<int>(line.size()) - 1;
        totalMoves += moves;
        // CHECK: The statement gives no sequence length bound; cap total moves to keep validation finite.
        ensuref(totalMoves <= maxTotalMoves, "total move count exceeds %lld", maxTotalMoves);

        int x = 0;
        int y = 0;
        set<array<int, 4>> edges;

        for (int i = 0; i < moves; ++i) {
            int nx = x;
            int ny = y;
            if (line[i] == 'U') {
                ++ny;
            } else if (line[i] == 'D') {
                --ny;
            } else if (line[i] == 'L') {
                --nx;
            } else {
                ++nx;
            }

            array<int, 4> edge = {x, y, nx, ny};
            if (edge[2] < edge[0] || (edge[2] == edge[0] && edge[3] < edge[1])) {
                swap(edge[0], edge[2]);
                swap(edge[1], edge[3]);
            }
            ensuref(edges.insert(edge).second,
                    "testcase %d reuses segment %d: (%d,%d)-(%d,%d)",
                    cases, i + 1, x, y, nx, ny);

            x = nx;
            y = ny;
        }
    }

    ensuref(cases >= 1, "input must contain at least one testcase before the final Q");
    inf.readEof();
}
