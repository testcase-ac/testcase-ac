#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    int M = inf.readInt(0, 270, "M");
    inf.readSpace();
    int H = inf.readInt(1, 30, "H");
    inf.readEoln();

    ensuref(M <= (N - 1) * H,
            "M is too large: M=%d but (N-1)*H=%d", M, (N - 1) * H);

    vector<pair<int, int>> lines;
    lines.reserve(M);
    set<pair<int, int>> used;

    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, H, "a");
        inf.readSpace();
        int b = inf.readInt(1, N - 1, "b");
        inf.readEoln();

        ensuref(used.insert({a, b}).second,
                "duplicate horizontal line at row %d, column %d", a, b);
        lines.emplace_back(a, b);
    }

    for (auto& line : lines) {
        int a = line.first;
        int b = line.second;
        if (b > 1) {
            ensuref(!used.count({a, b - 1}),
                    "touching horizontal lines at (%d,%d) and (%d,%d)",
                    a, b - 1, a, b);
        }
        if (b < N - 1) {
            ensuref(!used.count({a, b + 1}),
                    "touching horizontal lines at (%d,%d) and (%d,%d)",
                    a, b, a, b + 1);
        }
    }

    inf.readEof();
    return 0;
}
