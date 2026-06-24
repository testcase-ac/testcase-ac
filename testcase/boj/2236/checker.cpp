#include "testlib.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;

int n, k;
vector<long long> importance;

struct Claim {
    long long score;
};

static pair<int, int> normalizedGroup(int a, int b) {
    if (a > b) swap(a, b);
    return {a, b};
}

Claim readClaim(InStream& stream) {
    vector<int> powered(k);
    map<pair<int, int>, int> powerForGroup;

    for (int i = 0; i < k; ++i) {
        powered[i] = stream.readInt(0, n, format("power[%d]", i + 1).c_str());
        stream.readEoln();
    }

    vector<int> share(n + 1);
    for (int i = 1; i <= n; ++i) {
        share[i] = stream.readInt(0, n, format("share[%d]", i).c_str());
        if (i < n) {
            stream.readEoln();
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after component sharing list");
    }

    for (int i = 1; i <= n; ++i) {
        int j = share[i];
        if (j == 0) continue;
        if (share[j] != i) {
            stream.quitf(_wa,
                         "component %d shares with %d, but component %d shares with %d",
                         i,
                         j,
                         j,
                         share[j]);
        }
    }

    for (int i = 0; i < k; ++i) {
        int x = powered[i];
        if (x == 0) continue;
        if (share[x] == 0) {
            stream.quitf(_wa, "power %d is connected to unused component %d", i + 1, x);
        }

        auto group = normalizedGroup(x, share[x]);
        auto [it, inserted] = powerForGroup.emplace(group, i + 1);
        if (!inserted) {
            stream.quitf(_wa,
                         "group (%d, %d) is connected to both power %d and power %d",
                         group.first,
                         group.second,
                         it->second,
                         i + 1);
        }
    }

    set<pair<int, int>> groups;
    for (int i = 1; i <= n; ++i) {
        if (share[i] == 0) continue;
        auto group = normalizedGroup(i, share[i]);
        groups.insert(group);
    }

    for (auto [a, b] : groups) {
        if (!powerForGroup.count({a, b})) {
            stream.quitf(_wa, "group (%d, %d) is not connected to any power", a, b);
        }
    }

    vector<pair<int, int>> pairs;
    long long score = 0;
    for (auto [a, b] : groups) {
        if (a == b) {
            score += importance[a] * importance[a];
        } else {
            pairs.push_back({a, b});
            score += importance[a] * importance[b];
        }
    }

    for (int i = 0; i < (int)pairs.size(); ++i) {
        for (int j = i + 1; j < (int)pairs.size(); ++j) {
            int a = pairs[i].first;
            int b = pairs[i].second;
            int c = pairs[j].first;
            int d = pairs[j].second;
            if ((a < c && c < b && b < d) || (c < a && a < d && d < b)) {
                stream.quitf(_wa,
                             "connections (%d, %d) and (%d, %d) cross",
                             a,
                             b,
                             c,
                             d);
            }
        }
    }

    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    importance.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        importance[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.score < jury.score) {
        quitf(_wa,
              "jury has better chip importance: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail,
              "participant found better chip importance: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }
    quitf(_ok, "chip importance is %lld", participant.score);
}
