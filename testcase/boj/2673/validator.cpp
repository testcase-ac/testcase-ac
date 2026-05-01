#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Each point 1..100 can be used at most once as an endpoint
    // So, we track used points
    vector<bool> used(101, false); // 1-based, 1..100

    // Store all chords for possible further checks
    vector<pair<int, int>> chords;

    for (int i = 0; i < N; ++i) {
        int a = inf.readInt(1, 100, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 100, "b_i");
        inf.readEoln();

        ensuref(a != b, "Chord %d: endpoints must be different, got (%d, %d)", i+1, a, b);

        ensuref(!used[a], "Point %d is used as endpoint of more than one chord (at chord %d)", a, i+1);
        ensuref(!used[b], "Point %d is used as endpoint of more than one chord (at chord %d)", b, i+1);

        used[a] = true;
        used[b] = true;

        chords.emplace_back(a, b);
    }

    inf.readEof();
}
