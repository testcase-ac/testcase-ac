#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

struct MonkeyState {
    bool exists = false;
    bool hasL1 = false;
    bool hasR1 = false;
};

int parseTimeMs(const string& token, const string& name) {
    size_t dot = token.find('.');
    ensuref(dot != string::npos, "%s must contain decimal point: %s", name.c_str(), token.c_str());
    ensuref(dot > 0, "%s must have integer seconds: %s", name.c_str(), token.c_str());
    ensuref(token.size() == dot + 4, "%s must have exactly three millisecond digits: %s", name.c_str(), token.c_str());
    ensuref(token[0] != '0' || dot == 1, "%s seconds have leading zeroes: %s", name.c_str(), token.c_str());

    int seconds = 0;
    for (size_t i = 0; i < dot; ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "%s seconds contain non-digit: %s", name.c_str(), token.c_str());
        seconds = seconds * 10 + (token[i] - '0');
    }

    int millis = 0;
    for (size_t i = dot + 1; i < token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "%s milliseconds contain non-digit: %s", name.c_str(), token.c_str());
        millis = millis * 10 + (token[i] - '0');
    }

    int total = seconds * 1000 + millis;
    ensuref(0 <= total && total <= 300000, "%s is outside [0.000, 300.000]: %s", name.c_str(), token.c_str());
    return total;
}

pair<int, int> readPoint(int routeId, int pointId) {
    string token = inf.readToken("[^ ]+", "point");
    ensuref(token.size() >= 5, "route %d point %d has invalid format: %s", routeId, pointId, token.c_str());
    ensuref(token.front() == '(' && token.back() == ')', "route %d point %d must be parenthesized: %s", routeId, pointId, token.c_str());
    size_t comma = token.find(',');
    ensuref(comma != string::npos, "route %d point %d has no comma: %s", routeId, pointId, token.c_str());
    ensuref(token.find(',', comma + 1) == string::npos, "route %d point %d has multiple commas: %s", routeId, pointId, token.c_str());
    ensuref(comma > 1 && comma + 1 < token.size() - 1, "route %d point %d has empty coordinate: %s", routeId, pointId, token.c_str());
    ensuref(comma == 2 || token[1] != '0', "route %d point %d x has leading zeroes: %s", routeId, pointId, token.c_str());
    ensuref(comma + 2 == token.size() - 1 || token[comma + 1] != '0', "route %d point %d y has leading zeroes: %s", routeId, pointId, token.c_str());

    int x = 0;
    for (size_t i = 1; i < comma; ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "route %d point %d x is not numeric: %s", routeId, pointId, token.c_str());
        x = x * 10 + (token[i] - '0');
    }

    int y = 0;
    for (size_t i = comma + 1; i + 1 < token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "route %d point %d y is not numeric: %s", routeId, pointId, token.c_str());
        y = y * 10 + (token[i] - '0');
    }
    ensuref(0 <= x && x <= 1000, "route %d point %d x is outside [0, 1000]: %d", routeId, pointId, x);
    ensuref(0 <= y && y <= 1000, "route %d point %d y is outside [0, 1000]: %d", routeId, pointId, y);
    return {x, y};
}

void readUpgradeStatus(MonkeyState& monkey, const string& name) {
    string status = inf.readToken("-|L1|R1|L1R1", name);
    monkey.hasL1 = status == "L1" || status == "L1R1";
    monkey.hasR1 = status == "R1" || status == "L1R1";
}

void readPriority(const string& name) {
    inf.readToken("FIRST|LAST|STRONG", name);
}

string readBalloonName() {
    string first = inf.readToken("[A-Za-z]+", "balloon_name_part");
    if (first == "Red") {
        inf.readSpace();
        string second = inf.readToken("Balloon", "balloon_name_part");
        return first + " " + second;
    }
    if (first == "Lead") {
        inf.readSpace();
        string second = inf.readToken("Balloon", "balloon_name_part");
        return first + " " + second;
    }

    ensuref(first == "Camo", "unknown balloon name prefix: %s", first.c_str());
    inf.readSpace();
    string second = inf.readToken("Red|Lead", "balloon_name_part");
    inf.readSpace();
    string third = inf.readToken("Balloon", "balloon_name_part");
    return first + " " + second + " " + third;
}

bool isAttackTimeForMonkey(int timeMs, int monkeyId) {
    return timeMs >= monkeyId && timeMs % 1000 == monkeyId % 1000;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 10, "R");
    inf.readSpace();
    int U = inf.readInt(1, 1000, "U");
    inf.readEoln();

    vector<int> routeLength(R + 1);
    for (int routeId = 1; routeId <= R; ++routeId) {
        if (routeId > 1) inf.readSpace();
        routeLength[routeId] = inf.readInt(5, 500, "r_i");
    }
    inf.readEoln();

    set<pair<int, int>> mapPoints;
    for (int routeId = 1; routeId <= R; ++routeId) {
        for (int pointId = 1; pointId <= routeLength[routeId]; ++pointId) {
            if (pointId > 1) inf.readSpace();
            mapPoints.insert(readPoint(routeId, pointId));
        }
        inf.readEoln();
    }
    ensuref((int)mapPoints.size() <= 3000, "map has too many distinct points: %d", (int)mapPoints.size());

    vector<MonkeyState> monkeys(1001);
    set<int> activeMonkeyIds;
    for (int i = 1; i <= U; ++i) {
        int monkeyId = inf.readInt(1, 1000, "monkey_id");
        ensuref(activeMonkeyIds.insert(monkeyId).second, "duplicate initial monkey id: %d", monkeyId);
        monkeys[monkeyId].exists = true;
        inf.readSpace();
        readUpgradeStatus(monkeys[monkeyId], "upgrade_status");
        inf.readSpace();
        readPriority("select_priority");
        inf.readEoln();
    }

    int E = inf.readInt(1, 500000, "E");
    inf.readEoln();

    int previousTimeMs = -1;
    set<pair<int, int>> monkeyEventAtTime;
    set<pair<int, int>> balloonTimeByRoute;
    set<int> balloonIds;

    for (int eventIndex = 1; eventIndex <= E; ++eventIndex) {
        int timeMs = parseTimeMs(inf.readToken("[0-9]{1,3}[.][0-9]{3}", "event_time"), "event_time");
        ensuref(previousTimeMs <= timeMs, "events are not in chronological order at event %d", eventIndex);
        previousTimeMs = timeMs;
        inf.readSpace();

        string command = inf.readToken("ADD|UPGRADE|REMOVE|CHANGEPRIORITY|BALLOON", "event_type");
        if (command == "ADD") {
            inf.readSpace();
            int monkeyId = inf.readInt(1, 1000, "monkey_id");
            ensuref(!monkeys[monkeyId].exists, "ADD for existing monkey id %d at event %d", monkeyId, eventIndex);
            ensuref(!isAttackTimeForMonkey(timeMs, monkeyId), "monkey event coincides with attack command for id %d", monkeyId);
            ensuref(monkeyEventAtTime.insert({timeMs, monkeyId}).second, "multiple same-time monkey events for id %d", monkeyId);
            monkeys[monkeyId] = MonkeyState{true, false, false};
            inf.readEoln();
        } else if (command == "UPGRADE") {
            inf.readSpace();
            int monkeyId = inf.readInt(1, 1000, "monkey_id");
            ensuref(monkeys[monkeyId].exists, "UPGRADE for missing monkey id %d at event %d", monkeyId, eventIndex);
            ensuref(!isAttackTimeForMonkey(timeMs, monkeyId), "monkey event coincides with attack command for id %d", monkeyId);
            ensuref(monkeyEventAtTime.insert({timeMs, monkeyId}).second, "multiple same-time monkey events for id %d", monkeyId);
            inf.readSpace();
            string skill = inf.readToken("L1|R1", "skill_name");
            if (skill == "L1") {
                ensuref(!monkeys[monkeyId].hasL1, "monkey id %d learns L1 twice", monkeyId);
                monkeys[monkeyId].hasL1 = true;
            } else {
                ensuref(!monkeys[monkeyId].hasR1, "monkey id %d learns R1 twice", monkeyId);
                monkeys[monkeyId].hasR1 = true;
            }
            inf.readEoln();
        } else if (command == "REMOVE") {
            inf.readSpace();
            int monkeyId = inf.readInt(1, 1000, "monkey_id");
            ensuref(monkeys[monkeyId].exists, "REMOVE for missing monkey id %d at event %d", monkeyId, eventIndex);
            ensuref(!isAttackTimeForMonkey(timeMs, monkeyId), "monkey event coincides with attack command for id %d", monkeyId);
            ensuref(monkeyEventAtTime.insert({timeMs, monkeyId}).second, "multiple same-time monkey events for id %d", monkeyId);
            monkeys[monkeyId] = MonkeyState{};
            inf.readEoln();
        } else if (command == "CHANGEPRIORITY") {
            inf.readSpace();
            int monkeyId = inf.readInt(1, 1000, "monkey_id");
            ensuref(monkeys[monkeyId].exists, "CHANGEPRIORITY for missing monkey id %d at event %d", monkeyId, eventIndex);
            ensuref(!isAttackTimeForMonkey(timeMs, monkeyId), "monkey event coincides with attack command for id %d", monkeyId);
            ensuref(monkeyEventAtTime.insert({timeMs, monkeyId}).second, "multiple same-time monkey events for id %d", monkeyId);
            inf.readSpace();
            readPriority("select_priority");
            inf.readEoln();
        } else {
            // CHECK: The Korean statement says balloons are not generated "after 180.000s"; this validator treats 180.000 itself as disallowed.
            ensuref(timeMs < 180000, "BALLOON event is not before 180.000s at event %d", eventIndex);
            inf.readSpace();
            readBalloonName();
            inf.readSpace();
            int balloonId = inf.readInt(1, 1000000, "balloon_id");
            ensuref(balloonIds.insert(balloonId).second, "duplicate balloon id: %d", balloonId);
            inf.readSpace();
            int routeId = inf.readInt(1, R, "route_id");
            ensuref(balloonTimeByRoute.insert({routeId, timeMs}).second, "duplicate balloon generation time on route %d", routeId);
            inf.readEoln();
        }
    }

    inf.readEof();
}
