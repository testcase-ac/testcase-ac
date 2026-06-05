#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static void addUnique(vector<int>& stations, int position) {
    if (find(stations.begin(), stations.end(), position) == stations.end()) {
        stations.push_back(position);
    }
}

static vector<int> makePossible() {
    vector<int> stations;
    addUnique(stations, 0);

    int position = 0;
    while (position < 1322) {
        int step = rnd.next(120, 200);
        position = min(1322, position + step);
        addUnique(stations, position);
    }

    int extraCount = rnd.next(0, 5);
    for (int i = 0; i < extraCount; ++i) {
        addUnique(stations, rnd.next(1, 1422));
    }

    return stations;
}

static vector<int> makeGapImpossible() {
    vector<int> stations;
    addUnique(stations, 0);

    int beforeGap = rnd.next(0, 900);
    if (beforeGap != 0) {
        addUnique(stations, beforeGap);
    }

    int afterGap = rnd.next(beforeGap + 201, min(1422, beforeGap + 420));
    addUnique(stations, afterGap);

    int extraCount = rnd.next(0, 4);
    for (int i = 0; i < extraCount; ++i) {
        int position = rnd.next(1, 1422);
        if (position <= beforeGap || position >= afterGap) {
            addUnique(stations, position);
        }
    }

    return stations;
}

static vector<int> makeTurnaroundImpossible() {
    vector<int> stations;
    addUnique(stations, 0);

    int position = 0;
    while (position < 1200) {
        position = min(1200, position + rnd.next(120, 200));
        addUnique(stations, position);
    }

    int farthest = rnd.next(1200, 1321);
    addUnique(stations, farthest);

    return stations;
}

static vector<int> makeRandomScenario() {
    int n = rnd.next(1, 18);
    set<int> used;
    used.insert(0);
    while ((int)used.size() < n) {
        used.insert(rnd.next(1, 1422));
    }

    return vector<int>(used.begin(), used.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenarioCount = rnd.next(3, 10);
    for (int tc = 0; tc < scenarioCount; ++tc) {
        int mode = rnd.next(0, 3);
        vector<int> stations;
        if (mode == 0) {
            stations = makePossible();
        } else if (mode == 1) {
            stations = makeGapImpossible();
        } else if (mode == 2) {
            stations = makeTurnaroundImpossible();
        } else {
            stations = makeRandomScenario();
        }

        shuffle(stations.begin(), stations.end());
        println((int)stations.size());
        for (int position : stations) {
            println(position);
        }
    }

    println(0);
    return 0;
}
