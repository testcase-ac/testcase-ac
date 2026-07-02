#include "testlib.h"

#include <array>
#include <set>
#include <string>
#include <vector>

using namespace std;

int n, c;
vector<int> mustBeOn;
vector<int> mustBeOff;
set<string> reachable;

array<int, 101> applyButtons(int mask) {
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

void readLampList(vector<int>& lamps) {
    while (true) {
        int lamp = inf.readInt();
        if (lamp == -1) break;
        lamps.push_back(lamp);
    }
}

string stateToString(const array<int, 101>& state) {
    string result;
    result.reserve(n);
    for (int i = 1; i <= n; ++i) {
        result.push_back(char('0' + state[i]));
    }
    return result;
}

void buildReachableSet() {
    for (int mask = 0; mask < 16; ++mask) {
        int presses = __builtin_popcount(static_cast<unsigned>(mask));
        if (presses > c || presses % 2 != c % 2) continue;

        auto state = applyButtons(mask);
        bool matches = true;
        for (int lamp : mustBeOn) matches = matches && state[lamp] == 1;
        for (int lamp : mustBeOff) matches = matches && state[lamp] == 0;
        if (matches) reachable.insert(stateToString(state));
    }
}

set<string> readAnswer(InStream& stream) {
    set<string> configs;
    int index = 0;

    while (!stream.seekEof()) {
        string config = stream.readToken(format("[01]{%d}", n), format("configuration[%d]", index + 1).c_str());
        ++index;

        if (!reachable.count(config)) {
            stream.quitf(_wa, "configuration[%d] is not reachable or violates the required lamp states", index);
        }
        if (!configs.insert(config).second) {
            stream.quitf(_wa, "configuration[%d] is duplicated", index);
        }
    }

    if (configs.empty()) {
        stream.quitf(_wa, "no configurations printed");
    }
    return configs;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    c = inf.readInt();
    readLampList(mustBeOn);
    readLampList(mustBeOff);
    buildReachableSet();

    set<string> jury = readAnswer(ans);
    set<string> participant = readAnswer(ouf);

    vector<string> extra;
    for (const string& config : participant) {
        if (!jury.count(config)) extra.push_back(config);
    }
    if (!extra.empty()) {
        quitf(_fail, "participant found a valid configuration missing from jury output: %s", extra.front().c_str());
    }

    vector<string> missing;
    for (const string& config : jury) {
        if (!participant.count(config)) missing.push_back(config);
    }
    if (!missing.empty()) {
        quitf(_wa, "missing jury configuration: %s", missing.front().c_str());
    }

    quitf(_ok, "%d configurations", static_cast<int>(participant.size()));
}
