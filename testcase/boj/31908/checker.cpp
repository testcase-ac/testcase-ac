#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<string, string> ringByName;
map<string, int> ringCount;

using Pair = pair<string, string>;

Pair normalizedPair(string a, string b) {
    if (b < a) {
        swap(a, b);
    }
    return {a, b};
}

set<Pair> readAnswer(InStream& stream) {
    int pairCount = stream.readInt(0, 500, "pair count");
    stream.readEoln();

    set<Pair> pairs;
    for (int i = 0; i < pairCount; ++i) {
        string first = stream.readToken("[A-Za-z0-9_]{1,50}", format("pair[%d].first", i + 1).c_str());
        stream.readSpace();
        string second = stream.readToken("[A-Za-z0-9_]{1,50}", format("pair[%d].second", i + 1).c_str());
        stream.readEoln();

        if (first == second) {
            stream.quitf(_wa, "pair %d uses the same name twice: %s", i + 1, first.c_str());
        }

        auto firstIt = ringByName.find(first);
        if (firstIt == ringByName.end()) {
            stream.quitf(_wa, "pair %d contains unknown name: %s", i + 1, first.c_str());
        }
        auto secondIt = ringByName.find(second);
        if (secondIt == ringByName.end()) {
            stream.quitf(_wa, "pair %d contains unknown name: %s", i + 1, second.c_str());
        }

        const string& ring = firstIt->second;
        if (ring == "-") {
            stream.quitf(_wa, "pair %d includes a person without a ring: %s", i + 1, first.c_str());
        }
        if (ring != secondIt->second) {
            stream.quitf(_wa,
                         "pair %d uses different ring features: %s has %s, %s has %s",
                         i + 1,
                         first.c_str(),
                         ring.c_str(),
                         second.c_str(),
                         secondIt->second.c_str());
        }
        if (ringCount[ring] != 2) {
            stream.quitf(_wa,
                         "pair %d uses ring feature %s, which appears %d times",
                         i + 1,
                         ring.c_str(),
                         ringCount[ring]);
        }

        Pair current = normalizedPair(first, second);
        if (!pairs.insert(current).second) {
            stream.quitf(_wa, "duplicate pair: %s %s", current.first.c_str(), current.second.c_str());
        }
    }

    stream.readEof();
    return pairs;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken();
        string ring = inf.readToken();
        ringByName[name] = ring;
        if (ring != "-") {
            ++ringCount[ring];
        }
    }

    set<Pair> jury = readAnswer(ans);
    set<Pair> participant = readAnswer(ouf);

    for (const Pair& current : participant) {
        if (!jury.count(current)) {
            quitf(_fail,
                  "participant reported valid pair missing from jury answer: %s %s",
                  current.first.c_str(),
                  current.second.c_str());
        }
    }

    for (const Pair& current : jury) {
        if (!participant.count(current)) {
            quitf(_wa,
                  "missing pair from jury answer: %s %s",
                  current.first.c_str(),
                  current.second.c_str());
        }
    }

    quitf(_ok, "reported %d pair(s)", int(participant.size()));
}
