#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int n;
vector<int> requiredDepth;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "A[1] or -1");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    if (first == 0) {
        stream.quitf(_wa, "A[1] must be in [1, %d] or -1", n);
    }

    vector<int> a(n);
    vector<int> seen(n + 1, 0);
    a[0] = first;
    seen[first] = 1;

    for (int i = 1; i < n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i + 1).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        seen[a[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    vector<int> depth(n + 1, -1);
    set<int> inserted;
    inserted.insert(a[0]);
    depth[a[0]] = 0;

    for (int i = 1; i < n; ++i) {
        int x = a[i];
        auto it = inserted.lower_bound(x);
        int bestParentDepth = -1;

        if (it != inserted.end()) {
            bestParentDepth = max(bestParentDepth, depth[*it]);
        }
        if (it != inserted.begin()) {
            --it;
            bestParentDepth = max(bestParentDepth, depth[*it]);
        }

        int actualDepth = bestParentDepth + 1;
        if (actualDepth != requiredDepth[i - 1]) {
            stream.quitf(_wa,
                         "A[%d]=%d has depth %d, expected %d",
                         i + 1,
                         x,
                         actualDepth,
                         requiredDepth[i - 1]);
        }

        inserted.insert(x);
        depth[x] = actualDepth;
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    requiredDepth.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        requiredDepth[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers report impossible");
        }
        quitf(_fail, "participant found a valid sequence while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a valid sequence but participant reports impossible");
    }

    quitf(_ok, "valid sequence");
}
