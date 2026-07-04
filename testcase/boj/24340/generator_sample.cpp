#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Monkey {
    int id;
    bool exists;
    bool hasL1;
    bool hasR1;
};

string upgradeStatus(bool hasL1, bool hasR1) {
    if (hasL1 && hasR1) return "L1R1";
    if (hasL1) return "L1";
    if (hasR1) return "R1";
    return "-";
}

string timeToken(int timeMs) {
    return vtos(timeMs / 1000) + "." + format("%03d", timeMs % 1000);
}

bool isAttackTimeForMonkey(int timeMs, int monkeyId) {
    return timeMs >= monkeyId && timeMs % 1000 == monkeyId % 1000;
}

int pickSafeMonkeyEventTime(int low, int high, int monkeyId, set<pair<int, int>>& usedMonkeyEvents) {
    vector<int> candidates;
    for (int t = low; t <= high; ++t) {
        if (!isAttackTimeForMonkey(t, monkeyId) && !usedMonkeyEvents.count({t, monkeyId})) {
            candidates.push_back(t);
        }
    }
    ensuref(!candidates.empty(), "no safe monkey event time for monkey %d", monkeyId);
    int t = rnd.any(candidates);
    usedMonkeyEvents.insert({t, monkeyId});
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> priorities = {"FIRST", "LAST", "STRONG"};
    const vector<string> balloonNames = {
        "Red Balloon",
        "Camo Red Balloon",
        "Lead Balloon",
        "Camo Lead Balloon",
    };

    int R = rnd.next(1, 3);
    int U = rnd.next(2, 5);

    vector<int> routeLength(R + 1);
    for (int routeId = 1; routeId <= R; ++routeId) {
        routeLength[routeId] = rnd.next(5, 12);
    }

    vector<vector<pair<int, int>>> routes(R + 1);
    set<pair<int, int>> usedPoints;
    for (int routeId = 1; routeId <= R; ++routeId) {
        int baseX = routeId * 20 + rnd.next(0, 4);
        int baseY = rnd.next(0, 4);
        for (int pointId = 0; pointId < routeLength[routeId]; ++pointId) {
            pair<int, int> point;
            int pattern = rnd.next(0, 2);
            if (pattern == 0) {
                point = {baseX + pointId, baseY + rnd.next(0, 2)};
            } else if (pattern == 1) {
                point = {baseX + (pointId % 4), baseY + pointId};
            } else {
                point = {baseX + abs(3 - (pointId % 7)), baseY + pointId / 2};
            }

            point.first = min(point.first, 1000);
            point.second = min(point.second, 1000);
            routes[routeId].push_back(point);
            usedPoints.insert(point);
        }
    }

    vector<int> candidateIds;
    for (int id = 1; id <= 1000; ++id) {
        candidateIds.push_back(id);
    }
    shuffle(candidateIds.begin() + 1, candidateIds.end());

    vector<Monkey> monkeys;
    monkeys.push_back({1, true, true, true});
    for (int i = 1; (int)monkeys.size() < U; ++i) {
        int id = candidateIds[i];
        bool hasL1 = rnd.next(0, 1);
        bool hasR1 = rnd.next(0, 1);
        monkeys.push_back({id, true, hasL1, hasR1});
    }
    shuffle(monkeys.begin() + 1, monkeys.end());

    struct Event {
        int timeMs;
        string text;
    };

    vector<Event> events;
    set<pair<int, int>> usedMonkeyEvents;
    set<pair<int, int>> balloonTimeByRoute;
    set<int> usedBalloonIds;
    vector<bool> active(1001, false);
    vector<bool> hasL1(1001, false), hasR1(1001, false);
    for (const Monkey& monkey : monkeys) {
        active[monkey.id] = true;
        hasL1[monkey.id] = monkey.hasL1;
        hasR1[monkey.id] = monkey.hasR1;
    }

    int firstRoute = rnd.next(1, R);
    int firstBalloonId = rnd.next(1, 1000000);
    usedBalloonIds.insert(firstBalloonId);
    balloonTimeByRoute.insert({firstRoute, 1});
    events.push_back({1, "BALLOON " + rnd.any(balloonNames) + " " + vtos(firstBalloonId) + " " + vtos(firstRoute)});

    int nextExtraMonkey = 1000;
    if (U < 5 && rnd.next(0, 1)) {
        while (active[nextExtraMonkey]) --nextExtraMonkey;
        int t = pickSafeMonkeyEventTime(2, 40, nextExtraMonkey, usedMonkeyEvents);
        active[nextExtraMonkey] = true;
        hasL1[nextExtraMonkey] = false;
        hasR1[nextExtraMonkey] = false;
        events.push_back({t, "ADD " + vtos(nextExtraMonkey)});
    }

    for (const Monkey& monkey : monkeys) {
        int actionCount = rnd.next(0, 2);
        for (int k = 0; k < actionCount; ++k) {
            int t = pickSafeMonkeyEventTime(10 + k * 50, 90 + k * 70, monkey.id, usedMonkeyEvents);
            int choice = rnd.next(0, 2);
            if (choice == 0 && !hasL1[monkey.id]) {
                hasL1[monkey.id] = true;
                events.push_back({t, "UPGRADE " + vtos(monkey.id) + " L1"});
            } else if (choice == 1 && !hasR1[monkey.id]) {
                hasR1[monkey.id] = true;
                events.push_back({t, "UPGRADE " + vtos(monkey.id) + " R1"});
            } else {
                events.push_back({t, "CHANGEPRIORITY " + vtos(monkey.id) + " " + rnd.any(priorities)});
            }
        }
    }

    int balloonCount = rnd.next(6, 16);
    int currentTime = rnd.next(2, 20);
    for (int i = 0; i < balloonCount; ++i) {
        int routeId = rnd.next(1, R);
        currentTime += rnd.next(1, 35);
        while (balloonTimeByRoute.count({routeId, currentTime})) {
            ++currentTime;
        }
        balloonTimeByRoute.insert({routeId, currentTime});

        int balloonId = rnd.next(1, 1000000);
        while (usedBalloonIds.count(balloonId)) {
            balloonId = rnd.next(1, 1000000);
        }
        usedBalloonIds.insert(balloonId);
        events.push_back({currentTime, "BALLOON " + rnd.any(balloonNames) + " " + vtos(balloonId) + " " + vtos(routeId)});
    }

    if (rnd.next(0, 1)) {
        vector<int> removable;
        for (const Monkey& monkey : monkeys) {
            if (monkey.id != 1) removable.push_back(monkey.id);
        }
        if (!removable.empty()) {
            int id = rnd.any(removable);
            int t = pickSafeMonkeyEventTime(220, 320, id, usedMonkeyEvents);
            events.push_back({t, "REMOVE " + vtos(id)});
        }
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.timeMs != b.timeMs) return a.timeMs < b.timeMs;
        return a.text < b.text;
    });

    println(R, U);
    for (int routeId = 1; routeId <= R; ++routeId) {
        if (routeId > 1) cout << ' ';
        cout << routeLength[routeId];
    }
    cout << '\n';

    for (int routeId = 1; routeId <= R; ++routeId) {
        for (int pointId = 0; pointId < routeLength[routeId]; ++pointId) {
            if (pointId > 0) cout << ' ';
            cout << '(' << routes[routeId][pointId].first << ',' << routes[routeId][pointId].second << ')';
        }
        cout << '\n';
    }

    for (const Monkey& monkey : monkeys) {
        println(monkey.id, upgradeStatus(monkey.hasL1, monkey.hasR1), rnd.any(priorities));
    }

    println((int)events.size());
    for (const Event& event : events) {
        cout << timeToken(event.timeMs) << ' ' << event.text << '\n';
    }

    return 0;
}
