#include "testlib.h"
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static string makeName(int index, int style) {
    static const vector<string> shortNames = {
        "A", "B", "C", "D", "E", "a", "b", "c", "Aa", "aA", "Z", "z"
    };
    if (style == 0 && index < (int)shortNames.size()) return shortNames[index];

    string name;
    int x = index;
    do {
        int letter = x % 52;
        name.push_back(letter < 26 ? char('A' + letter) : char('a' + letter - 26));
        x /= 52;
    } while (x > 0 && (int)name.size() < 5);

    while ((int)name.size() < rnd.next(1, 5)) {
        name.push_back(rnd.next(2) ? char('A' + rnd.next(26)) : char('a' + rnd.next(26)));
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 30);
    int peopleCount = rnd.next(2, 12);
    int nameStyle = rnd.next(3) == 0 ? 1 : 0;

    vector<string> people;
    set<string> used;
    for (int i = 0; (int)people.size() < peopleCount; i++) {
        string name = makeName(i + rnd.next(10), nameStyle);
        if (used.insert(name).second) people.push_back(name);
    }

    vector<pair<string, string>> logs;
    vector<string> inside, outside = people;

    auto enter = [&](int outsideIndex) {
        string name = outside[outsideIndex];
        outside.erase(outside.begin() + outsideIndex);
        inside.push_back(name);
        logs.push_back({name, "enter"});
    };

    auto leave = [&](int insideIndex) {
        string name = inside[insideIndex];
        inside.erase(inside.begin() + insideIndex);
        outside.push_back(name);
        logs.push_back({name, "leave"});
    };

    while ((int)logs.size() < n) {
        bool canEnter = !outside.empty();
        bool canLeave = !inside.empty();

        if (mode == 0 && canEnter) {
            enter(rnd.next((int)outside.size()));
        } else if (mode == 1 && canLeave && (logs.size() + outside.empty() >= 2 || rnd.next(2))) {
            leave(rnd.next((int)inside.size()));
        } else if (mode == 2 && canEnter && (inside.empty() || rnd.next(3))) {
            enter(rnd.next((int)outside.size()));
        } else if (mode == 3 && canLeave && rnd.next(3) == 0) {
            leave(rnd.next((int)inside.size()));
        } else if (canEnter) {
            enter(rnd.next((int)outside.size()));
        } else {
            leave(rnd.next((int)inside.size()));
        }
    }

    println((int)logs.size());
    for (const auto& log : logs) println(log.first, log.second);

    return 0;
}
