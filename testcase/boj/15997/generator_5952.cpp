#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate 4 distinct team names (1 to 10 uppercase letters)
    set<string> used;
    vector<string> teams;
    while ((int)teams.size() < 4) {
        int len = rnd.next(1, 10);
        string s;
        for (int i = 0; i < len; i++)
            s.push_back(char('A' + rnd.next(0, 25)));
        if (!used.count(s)) {
            used.insert(s);
            teams.push_back(s);
        }
    }

    // Print team names in order
    println(teams);

    // Build all 6 matches
    vector<pair<int,int>> matches;
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            matches.emplace_back(i, j);
    shuffle(matches.begin(), matches.end());

    // For each match, generate probabilities W, D, L summing to 1.000 with up to 3 decimals
    const int TOT = 1000;
    for (auto &p : matches) {
        int w, d, l;
        // 1/5 chance to make an extreme case: one outcome certain
        if (rnd.next(0, 4) == 0) {
            int pick = rnd.next(0, 2);
            w = (pick == 0 ? TOT : 0);
            d = (pick == 1 ? TOT : 0);
            l = (pick == 2 ? TOT : 0);
        } else {
            w = rnd.next(0, TOT);
            d = rnd.next(0, TOT - w);
            l = TOT - w - d;
        }
        // print: TeamA TeamB W D L
        printf("%s %s %.3f %.3f %.3f\n",
               teams[p.first].c_str(),
               teams[p.second].c_str(),
               w / 1000.0, d / 1000.0, l / 1000.0);
    }

    return 0;
}
