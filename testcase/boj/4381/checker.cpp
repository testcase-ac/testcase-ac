#include "testlib.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    long long total;
    int moves;
};

vector<int> initialLeft;

vector<int> parseMoveLine(InStream& stream, const string& line, int moveIndex) {
    if (line.empty()) {
        stream.quitf(_wa, "move %d is empty", moveIndex);
    }

    istringstream iss(line);
    vector<int> group;
    int value;
    while (iss >> value) {
        group.push_back(value);
    }

    if (!iss.eof()) {
        stream.quitf(_wa, "move %d contains a non-integer token", moveIndex);
    }
    if (group.empty() || group.size() > 2) {
        stream.quitf(_wa, "move %d has %d people instead of one or two",
                     moveIndex, int(group.size()));
    }
    for (int time : group) {
        if (time < 1 || time > 100) {
            stream.quitf(_wa, "move %d uses crossing time %d outside [1, 100]",
                         moveIndex, time);
        }
    }
    return group;
}

void moveGroup(InStream& stream, vector<int>& from, vector<int>& to,
               const vector<int>& group, int moveIndex) {
    vector<int> need(101, 0);
    for (int time : group) {
        ++need[time];
    }

    for (int time = 1; time <= 100; ++time) {
        if (need[time] > from[time]) {
            stream.quitf(_wa,
                         "move %d uses crossing time %d %d time(s), but only %d available",
                         moveIndex, time, need[time], from[time]);
        }
    }

    for (int time = 1; time <= 100; ++time) {
        from[time] -= need[time];
        to[time] += need[time];
    }
}

Claim readClaim(InStream& stream) {
    long long declaredTotal = stream.readLong(0, 1000000000LL, "total seconds");
    stream.readEoln();

    vector<int> left = initialLeft;
    vector<int> right(101, 0);
    long long computedTotal = 0;
    int moves = 0;
    bool forward = true;

    while (!stream.seekEof()) {
        string line = stream.readLine();
        ++moves;
        vector<int> group = parseMoveLine(stream, line, moves);

        int moveTime = *max_element(group.begin(), group.end());
        computedTotal += moveTime;

        if (forward) {
            moveGroup(stream, left, right, group, moves);
        } else {
            moveGroup(stream, right, left, group, moves);
        }
        forward = !forward;
    }

    if (moves == 0) {
        stream.quitf(_wa, "strategy is empty");
    }

    int remainingLeft = 0;
    for (int time = 1; time <= 100; ++time) {
        remainingLeft += left[time];
    }
    if (remainingLeft != 0) {
        stream.quitf(_wa, "strategy leaves %d people on the starting side", remainingLeft);
    }
    if (computedTotal != declaredTotal) {
        stream.quitf(_wa, "declared total %lld does not match strategy time %lld",
                     declaredTotal, computedTotal);
    }

    return {declaredTotal, moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    initialLeft.assign(101, 0);
    for (int i = 0; i < n; ++i) {
        int time = inf.readInt();
        ++initialLeft[time];
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.total > jury.total) {
        quitf(_wa, "participant total %lld is worse than jury total %lld",
              participant.total, jury.total);
    }
    if (participant.total < jury.total) {
        quitf(_fail, "participant total %lld is better than jury total %lld",
              participant.total, jury.total);
    }

    quitf(_ok, "total=%lld moves=%d", participant.total, participant.moves);
}
