#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int n;
long long m;
vector<long long> power;

struct Claim {
    bool possible;
};

bool peaceful(const set<pair<long long, int>>& dragons) {
    if (dragons.size() <= 1) {
        return true;
    }

    auto strongest = dragons.rbegin();
    auto second = next(strongest);
    return strongest->first - second->first <= m;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<int> used(n + 1, 0);
    set<pair<long long, int>> canyon;
    set<pair<long long, int>> abyss;
    for (int i = 1; i <= n; ++i) {
        canyon.insert({power[i], i});
    }

    for (int step = 1; step <= n; ++step) {
        int id = stream.readInt(1, n, format("order[%d]", step).c_str());
        if (used[id]) {
            stream.quitf(_wa, "dragon %d appears more than once", id);
        }
        used[id] = 1;

        auto dragon = make_pair(power[id], id);
        auto erased = canyon.erase(dragon);
        if (erased != 1) {
            stream.quitf(_wa, "dragon %d was not in Summoner's Rift at step %d", id, step);
        }
        abyss.insert(dragon);

        if (!peaceful(canyon)) {
            stream.quitf(_wa, "Summoner's Rift is not peaceful after moving order[%d]=%d", step, id);
        }
        if (!peaceful(abyss)) {
            stream.quitf(_wa, "Howling Abyss is not peaceful after moving order[%d]=%d", step, id);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after ordering");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readLong();
    power.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        power[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury found a valid ordering but participant answered NO");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid ordering but jury answered NO");
    }

    quitf(_ok, "%s", participant.possible ? "valid ordering" : "both answered NO");
}
