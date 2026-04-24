#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int N, W;
vector<pair<int,int>> events;

// Reads an answer from stream (ouf or ans), validates it, computes the total
// distance, and returns it. Quits with _wa if participant is wrong or with
// _fail if jury's provided answer is wrong.
int readAns(InStream &stream) {
    // Read reported total distance
    int reported = stream.readInt(0, 2000000000, "total distance");
    // Read assignments for each of the W events
    vector<int> who(W);
    for (int i = 0; i < W; i++) {
        who[i] = stream.readInt(1, 2, format("assignment[%d]", i+1).c_str());
    }
    // Simulate the cars
    int x1 = 1, y1 = 1;
    int x2 = N, y2 = N;
    long long sum = 0;
    for (int i = 0; i < W; i++) {
        int ex = events[i].first;
        int ey = events[i].second;
        if (who[i] == 1) {
            sum += abs(x1 - ex) + abs(y1 - ey);
            x1 = ex; y1 = ey;
        } else {
            sum += abs(x2 - ex) + abs(y2 - ey);
            x2 = ex; y2 = ey;
        }
    }
    if (sum != reported) {
        stream.quitf(_wa,
            "expected total distance = %lld, but found = %d",
            sum, reported);
    }
    return reported;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    N = inf.readInt(5, 1000);
    W = inf.readInt(1, 1000);
    events.resize(W);
    for (int i = 0; i < W; i++) {
        events[i].first  = inf.readInt(1, N);
        events[i].second = inf.readInt(1, N);
    }

    // Read jury and participant answers
    int juryDist = readAns(ans);
    int partDist = readAns(ouf);

    // Compare
    if (partDist > juryDist) {
        quitf(_wa,
            "participant total = %d, jury minimum = %d",
            partDist, juryDist);
    } else if (partDist == juryDist) {
        quitf(_ok, "total distance = %d", partDist);
    } else {
        // Participant found a better distance than jury: jury is wrong
        quitf(_fail,
            "participant total = %d is less than jury = %d",
            partDist, juryDist);
    }
}
