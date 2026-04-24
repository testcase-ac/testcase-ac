#include "testlib.h"
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
map<tuple<int,int,int>, int> orig_cnt;

// readAns reads one answer (jury or contestant), verifies it, and returns
// the saturation computed on the selection.
int readAns(InStream& stream) {
    // Read reported saturation
    int s_report = stream.readInt(0, 255, "saturation");
    // Make a local copy of counts
    map<tuple<int,int,int>, int> cnt = orig_cnt;
    // Track min/max of each color
    int minR = 256, maxR = -1;
    int minG = 256, maxG = -1;
    int minB = 256, maxB = -1;
    // Read K crayons
    for (int i = 0; i < K; i++) {
        int r = stream.readInt(0, 255, format("R[%d]", i+1).c_str());
        int g = stream.readInt(0, 255, format("G[%d]", i+1).c_str());
        int b = stream.readInt(0, 255, format("B[%d]", i+1).c_str());
        tuple<int,int,int> t = make_tuple(r, g, b);
        auto it = cnt.find(t);
        if (it == cnt.end() || it->second == 0) {
            stream.quitf(_wa, "crayon (%d,%d,%d) is not available or used too many times", r, g, b);
        }
        it->second--;
        minR = min(minR, r); maxR = max(maxR, r);
        minG = min(minG, g); maxG = max(maxG, g);
        minB = min(minB, b); maxB = max(maxB, b);
    }
    // Compute actual saturation = max range over R,G,B
    int s_val = max({ maxR - minR, maxG - minG, maxB - minB });
    // Check reported matches actual
    if (s_report != s_val) {
        stream.quitf(_wa, "reported saturation = %d, but actual = %d", s_report, s_val);
    }
    return s_val;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt(2, 100000, "N");
    K = inf.readInt(2, N, "K");
    for (int i = 0; i < N; i++) {
        int r = inf.readInt(0, 255);
        int g = inf.readInt(0, 255);
        int b = inf.readInt(0, 255);
        orig_cnt[make_tuple(r,g,b)]++;
    }
    // Read jury and participant answers
    int jans = readAns(ans);
    int pans = readAns(ouf);
    // Compare
    if (pans > jans) {
        quitf(_wa, "jury has a better answer: jury = %d, participant = %d", jans, pans);
    } else if (pans < jans) {
        quitf(_fail, "participant has a better answer than jury: jury = %d, participant = %d", jans, pans);
    } else {
        quitf(_ok, "saturation = %d", pans);
    }
    return 0;
}
