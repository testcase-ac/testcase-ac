#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Lecture {
    long long start;
    long long end;
};

struct Answer {
    int rooms;
};

int n;
vector<Lecture> lectures;

Answer readAnswer(InStream& stream) {
    int rooms = stream.readInt(1, n, "room_count");
    stream.readEoln();

    vector<vector<pair<long long, long long>>> byRoom(rooms + 1);
    for (int id = 1; id <= n; ++id) {
        int room = stream.readInt(1, rooms, format("room[%d]", id).c_str());
        stream.readEoln();
        byRoom[room].push_back({lectures[id].start, lectures[id].end});
    }
    stream.readEof();

    for (int room = 1; room <= rooms; ++room) {
        auto& intervals = byRoom[room];
        sort(intervals.begin(), intervals.end());
        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (intervals[i - 1].second > intervals[i].first) {
                stream.quitf(_wa,
                             "room %d has overlapping lectures: [%lld, %lld) and [%lld, %lld)",
                             room,
                             intervals[i - 1].first,
                             intervals[i - 1].second,
                             intervals[i].first,
                             intervals[i].second);
            }
        }
    }

    return {rooms};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "n");
    lectures.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        int id = inf.readInt(1, n, "lecture_number");
        long long start = inf.readLong(0LL, 1000000000LL, "start_time");
        long long end = inf.readLong(0LL, 1000000000LL, "end_time");
        lectures[id] = {start, end};
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.rooms > jury.rooms) {
        quitf(_wa,
              "participant uses too many rooms: jury=%d participant=%d",
              jury.rooms,
              participant.rooms);
    }
    if (participant.rooms < jury.rooms) {
        quitf(_fail,
              "participant found a better valid assignment: jury=%d participant=%d",
              jury.rooms,
              participant.rooms);
    }

    quitf(_ok, "valid assignment using %d rooms", participant.rooms);
}
