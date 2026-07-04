#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Event {
    char type;
    int id;
};

int randomKnownId(const vector<int>& ids) {
    return ids[rnd.next(static_cast<int>(ids.size()))];
}

Event randomEvent(const vector<int>& ids, int zeroChance) {
    char type = rnd.next(2) == 0 ? 'E' : 'L';
    int id = rnd.next(100) < zeroChance ? 0 : randomKnownId(ids);
    return {type, id};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 15);

        vector<int> ids = {1, 2, 3, 4, 5, 1999, 2000};
        shuffle(ids.begin(), ids.end());
        ids.resize(rnd.next(1, static_cast<int>(ids.size())));

        vector<Event> events;

        if (mode == 0) {
            int zeroChance = rnd.next(65, 100);
            for (int i = 0; i < n; ++i) events.push_back(randomEvent(ids, zeroChance));
        } else if (mode == 1) {
            int id = randomKnownId(ids);
            for (int i = 0; i < n; ++i) {
                char type = i % 2 == 0 ? 'E' : 'L';
                if (rnd.next(100) < 35) type = type == 'E' ? 'L' : 'E';
                int printedId = rnd.next(100) < 25 ? 0 : id;
                events.push_back({type, printedId});
            }
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                int id = i % 3 == 0 ? 2000 : randomKnownId(ids);
                char type = rnd.next(100) < 55 ? 'E' : 'L';
                if (rnd.next(100) < 20) id = 0;
                events.push_back({type, id});
            }
        } else if (mode == 3) {
            while (static_cast<int>(events.size()) + 1 < n) {
                int id = randomKnownId(ids);
                if (rnd.next(2) == 0) {
                    events.push_back({'E', id});
                    events.push_back({'L', rnd.next(100) < 30 ? 0 : id});
                } else {
                    events.push_back({'L', id});
                    events.push_back({'E', rnd.next(100) < 30 ? 0 : id});
                }
            }
            if (static_cast<int>(events.size()) < n) events.push_back(randomEvent(ids, 40));
            shuffle(events.begin(), events.end());
        } else {
            for (int i = 0; i < n; ++i) {
                int id = rnd.any(vector<int>{0, 1, 2, 5, 2000});
                char type = rnd.next(2) == 0 ? 'E' : 'L';
                events.push_back({type, id});
            }
        }

        println(n);
        for (const Event& event : events) {
            println(string(1, event.type), event.id);
        }
    }

    return 0;
}
