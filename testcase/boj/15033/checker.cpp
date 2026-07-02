#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const long long COORD_LIMIT = 1000000;
const int MAX_STATES = 7000;

struct Point {
    long long x;
    long long y;
    long long z;
};

struct State {
    Point a;
    Point b;
};

bool samePoint(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

long long dist(const Point& lhs, const Point& rhs) {
    return llabs(lhs.x - rhs.x) + llabs(lhs.y - rhs.y) + llabs(lhs.z - rhs.z);
}

TResult invalidVerdict(bool isJury) {
    return isJury ? _fail : _wa;
}

vector<State> readSchedule(InStream& stream, bool isJury, const State& start, const State& finish) {
    vector<State> schedule;
    while (!stream.seekEof()) {
        State cur;
        int line = int(schedule.size()) + 1;
        cur.a.x = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot1.x[%d]", line).c_str());
        cur.a.y = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot1.y[%d]", line).c_str());
        cur.a.z = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot1.z[%d]", line).c_str());
        cur.b.x = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot2.x[%d]", line).c_str());
        cur.b.y = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot2.y[%d]", line).c_str());
        cur.b.z = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("robot2.z[%d]", line).c_str());

        if (samePoint(cur.a, cur.b)) {
            stream.quitf(invalidVerdict(isJury), "robots share position on line %d", line);
        }
        schedule.push_back(cur);
        if (int(schedule.size()) > MAX_STATES) {
            stream.quitf(invalidVerdict(isJury), "schedule has more than %d states", MAX_STATES);
        }
    }

    if (schedule.empty()) {
        stream.quitf(invalidVerdict(isJury), "schedule is empty");
    }

    if (!samePoint(schedule.front().a, start.a) || !samePoint(schedule.front().b, start.b)) {
        stream.quitf(invalidVerdict(isJury), "first state does not match the start positions");
    }
    if (!samePoint(schedule.back().a, finish.a) || !samePoint(schedule.back().b, finish.b)) {
        stream.quitf(invalidVerdict(isJury), "last state does not match the finish positions");
    }

    for (int i = 1; i < int(schedule.size()); ++i) {
        long long moveA = dist(schedule[i - 1].a, schedule[i].a);
        long long moveB = dist(schedule[i - 1].b, schedule[i].b);
        if (moveA > 1) {
            stream.quitf(invalidVerdict(isJury), "robot 1 moves %lld metres from line %d to line %d", moveA, i, i + 1);
        }
        if (moveB > 1) {
            stream.quitf(invalidVerdict(isJury), "robot 2 moves %lld metres from line %d to line %d", moveB, i, i + 1);
        }
        if (samePoint(schedule[i - 1].a, schedule[i].b) && samePoint(schedule[i - 1].b, schedule[i].a)) {
            stream.quitf(invalidVerdict(isJury), "robots swap positions from line %d to line %d", i, i + 1);
        }
    }

    return schedule;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    State start, finish;
    start.a.x = inf.readLong();
    start.a.y = inf.readLong();
    start.a.z = inf.readLong();
    finish.a.x = inf.readLong();
    finish.a.y = inf.readLong();
    finish.a.z = inf.readLong();
    start.b.x = inf.readLong();
    start.b.y = inf.readLong();
    start.b.z = inf.readLong();
    finish.b.x = inf.readLong();
    finish.b.y = inf.readLong();
    finish.b.z = inf.readLong();

    readSchedule(ans, true, start, finish);
    vector<State> participant = readSchedule(ouf, false, start, finish);

    quitf(_ok, "valid schedule with %d states", int(participant.size()));
}
