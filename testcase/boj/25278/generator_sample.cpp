#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Change {
    string parameter;
    int delta;
};

void addSplit(vector<Change>& changes, const string& parameter, int total, int maxParts) {
    while (total > 0 && maxParts > 0) {
        int delta = rnd.next(1, min(5, total));
        changes.push_back({parameter, delta});
        total -= delta;
        --maxParts;
    }
}

void addRandomChange(vector<Change>& changes) {
    static const vector<string> parameters = {"oxygen", "ocean", "temperature"};
    changes.push_back({rnd.any(parameters), rnd.next(1, 5)});
}

int sumFor(const vector<Change>& changes, const string& parameter) {
    int sum = 0;
    for (const Change& change : changes) {
        if (change.parameter == parameter) sum += change.delta;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<Change> changes;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) addRandomChange(changes);
    } else if (mode == 1) {
        addSplit(changes, "oxygen", rnd.next(14, 18), 6);
        addSplit(changes, "ocean", rnd.next(9, 13), 5);
        addSplit(changes, "temperature", rnd.next(38, 42), 10);
    } else if (mode == 2) {
        addSplit(changes, "oxygen", rnd.next(0, 13), 5);
        addSplit(changes, "ocean", rnd.next(9, 15), 5);
        addSplit(changes, "temperature", rnd.next(38, 45), 10);
    } else if (mode == 3) {
        addSplit(changes, "oxygen", rnd.next(14, 20), 6);
        addSplit(changes, "ocean", rnd.next(0, 8), 4);
        addSplit(changes, "temperature", rnd.next(38, 45), 10);
    } else if (mode == 4) {
        addSplit(changes, "oxygen", rnd.next(14, 20), 6);
        addSplit(changes, "ocean", rnd.next(9, 15), 5);
        addSplit(changes, "temperature", rnd.next(0, 37), 10);
    } else if (mode == 5) {
        addSplit(changes, "oxygen", 14, 6);
        addSplit(changes, "ocean", 9, 5);
        addSplit(changes, "temperature", 38, 10);
    } else {
        int n = rnd.next(120, 315);
        for (int i = 0; i < n; ++i) addRandomChange(changes);
    }

    while (changes.empty()) addRandomChange(changes);

    if (mode != 6) {
        int filler = rnd.next(0, min(12, 315 - int(changes.size())));
        for (int i = 0; i < filler; ++i) addRandomChange(changes);
    }

    shuffle(changes.begin(), changes.end());

    println(int(changes.size()));
    for (const Change& change : changes) {
        println(change.parameter, "+" + to_string(change.delta));
    }

    return 0;
}
