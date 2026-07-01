#include "testlib.h"

#include <array>
#include <set>
#include <vector>

using namespace std;

vector<int> readLampList(const char* name, int n) {
    vector<int> lamps;
    while (true) {
        int lamp = inf.readInt(-1, n, name);
        ensuref(lamp == -1 || lamp >= 1, "%s contains invalid lamp number %d", name, lamp);
        if (lamp == -1) {
            inf.readEoln();
            break;
        }

        ensuref(lamps.size() < 2, "%s contains more than 2 lamp numbers", name);
        lamps.push_back(lamp);
        inf.readSpace();
    }

    set<int> uniqueLamps(lamps.begin(), lamps.end());
    ensuref(uniqueLamps.size() == lamps.size(), "%s contains a duplicate lamp number", name);
    return lamps;
}

array<int, 101> applyButtons(int n, int mask) {
    array<int, 101> state{};
    state.fill(1);

    if (mask & 1) {
        for (int i = 1; i <= n; ++i) state[i] ^= 1;
    }
    if (mask & 2) {
        for (int i = 1; i <= n; i += 2) state[i] ^= 1;
    }
    if (mask & 4) {
        for (int i = 2; i <= n; i += 2) state[i] ^= 1;
    }
    if (mask & 8) {
        for (int i = 1; i <= n; i += 3) state[i] ^= 1;
    }

    return state;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(10, 100, "N");
    inf.readEoln();
    int c = inf.readInt(1, 10000, "C");
    inf.readEoln();

    vector<int> on = readLampList("on_lamps", n);
    vector<int> off = readLampList("off_lamps", n);
    inf.readEof();

    set<int> onSet(on.begin(), on.end());
    for (int lamp : off) {
        ensuref(!onSet.count(lamp), "lamp %d is listed as both ON and OFF", lamp);
    }

    bool hasPossibleConfiguration = false;
    for (int mask = 0; mask < 16; ++mask) {
        int presses = __builtin_popcount(static_cast<unsigned>(mask));
        if (presses > c || presses % 2 != c % 2) continue;

        array<int, 101> state = applyButtons(n, mask);
        bool matches = true;
        for (int lamp : on) matches = matches && state[lamp] == 1;
        for (int lamp : off) matches = matches && state[lamp] == 0;
        hasPossibleConfiguration = hasPossibleConfiguration || matches;
    }

    ensuref(hasPossibleConfiguration, "no possible final configuration satisfies the informed lamp states");
}
