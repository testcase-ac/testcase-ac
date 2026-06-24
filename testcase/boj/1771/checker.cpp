#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Bundle {
    int l;
    int r;
    int mn;
    int mx;
};

int n;
vector<int> cards;

void readAndValidateCertificate(InStream& stream) {
    map<int, Bundle> byLeft;
    vector<int> startAt(n + 2);

    for (int i = 1; i <= n; ++i) {
        byLeft[i] = Bundle{i, i, cards[i], cards[i]};
        startAt[i] = i;
    }

    for (int step = 1; step < n; ++step) {
        int p = stream.readInt(1, n, format("merge_position[%d]", step).c_str());
        stream.readEoln();

        int leftStart = startAt[p];
        if (leftStart == 0) {
            stream.quitf(_wa, "step %d: position %d is not in an active bundle", step, p);
        }

        auto leftIt = byLeft.find(leftStart);
        if (leftIt == byLeft.end() || leftIt->second.r != p) {
            stream.quitf(_wa,
                         "step %d: position %d is not the last card of an active left bundle",
                         step,
                         p);
        }

        auto rightIt = next(leftIt);
        if (rightIt == byLeft.end()) {
            stream.quitf(_wa, "step %d: no right bundle after position %d", step, p);
        }

        Bundle left = leftIt->second;
        Bundle right = rightIt->second;
        int mergedMin = min(left.mn, right.mn);
        int mergedMax = max(left.mx, right.mx);
        int mergedLen = right.r - left.l + 1;
        if (mergedMax - mergedMin + 1 != mergedLen) {
            stream.quitf(_wa,
                         "step %d: merging [%d,%d] and [%d,%d] does not form consecutive values",
                         step,
                         left.l,
                         left.r,
                         right.l,
                         right.r);
        }

        Bundle merged{left.l, right.r, mergedMin, mergedMax};
        byLeft.erase(rightIt);
        leftIt->second = merged;

        startAt[merged.l] = merged.l;
        startAt[merged.r] = merged.l;
    }

    if ((int)byLeft.size() != 1) {
        stream.quitf(_wa, "certificate leaves %d bundles", (int)byLeft.size());
    }
    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    cards.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cards[i] = inf.readInt();
    }

    readAndValidateCertificate(ans);
    readAndValidateCertificate(ouf);

    quitf(_ok, "valid merge certificate");
}
