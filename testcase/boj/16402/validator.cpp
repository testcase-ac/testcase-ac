#include "testlib.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> leader;

    explicit DSU(int n) : parent(n), leader(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            leader[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int currentLeader(int x) {
        return leader[find(x)];
    }

    void absorb(int winnerSide, int loserSide) {
        int wr = find(winnerSide);
        int lr = find(loserSide);
        if (wr == lr) {
            return;
        }
        parent[lr] = wr;
    }

    void replaceLeader(int x) {
        leader[find(x)] = x;
    }
};

bool isKingdomName(const string& s) {
    const string prefix = "Kingdom of ";
    if (s.size() <= prefix.size() || s.size() > 20) {
        return false;
    }
    if (s.compare(0, prefix.size(), prefix) != 0) {
        return false;
    }
    for (int i = (int)prefix.size(); i < (int)s.size(); ++i) {
        char c = s[i];
        if (!(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

vector<string> splitCommas(const string& line) {
    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = line.find(',', start);
        if (pos == string::npos) {
            parts.push_back(line.substr(start));
            break;
        }
        parts.push_back(line.substr(start, pos - start));
        start = pos + 1;
    }
    return parts;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readEoln();

    map<string, int> id;
    for (int i = 0; i < n; ++i) {
        string name = inf.readLine("[A-Za-z\\ ]{12,20}", "kingdom_name");
        ensuref(isKingdomName(name), "invalid kingdom name at line %d: %s", i + 2, name.c_str());
        ensuref(id.emplace(name, i).second, "duplicate kingdom name: %s", name.c_str());
    }

    DSU dsu(n);
    for (int i = 1; i <= m; ++i) {
        string line = inf.readLine("[A-Za-z\\ ,12]{25,43}", "war_result");
        vector<string> parts = splitCommas(line);
        ensuref(parts.size() == 3, "war result %d must have exactly three comma-separated fields", i);
        ensuref(isKingdomName(parts[0]), "invalid first kingdom in war result %d: %s", i, parts[0].c_str());
        ensuref(isKingdomName(parts[1]), "invalid second kingdom in war result %d: %s", i, parts[1].c_str());
        ensuref(parts[2] == "1" || parts[2] == "2", "invalid winner field in war result %d: %s", i, parts[2].c_str());

        auto it1 = id.find(parts[0]);
        auto it2 = id.find(parts[1]);
        ensuref(it1 != id.end(), "unknown first kingdom in war result %d: %s", i, parts[0].c_str());
        ensuref(it2 != id.end(), "unknown second kingdom in war result %d: %s", i, parts[1].c_str());

        int a = it1->second;
        int b = it2->second;
        ensuref(a != b, "war result %d names the same kingdom twice: %s", i, parts[0].c_str());

        int ra = dsu.find(a);
        int rb = dsu.find(b);
        int leaderA = dsu.currentLeader(a);
        int leaderB = dsu.currentLeader(b);
        int winner = (parts[2] == "1" ? a : b);
        int loser = (parts[2] == "1" ? b : a);

        if (ra == rb) {
            ensuref((a == leaderA && b != leaderA) || (b == leaderA && a != leaderA),
                    "war result %d is not a possible vassal-sovereign war", i);
            if (winner != leaderA) {
                dsu.replaceLeader(winner);
            }
        } else {
            ensuref(a == leaderA || b == leaderB,
                    "war result %d is not possible because neither named kingdom can attack", i);
            dsu.absorb(winner, loser);
        }
    }

    inf.readEof();
    return 0;
}
