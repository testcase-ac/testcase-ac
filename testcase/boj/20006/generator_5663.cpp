#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of players
    int p = rnd.next(1, 20);
    // room capacity: sometimes small, sometimes larger than p
    int m;
    if (rnd.next() < 0.2) {
        m = rnd.next(p+1, p+5);
    } else {
        m = rnd.next(1, max(1, p));
    }
    if (m > 300) m = rnd.next(1, 300);

    // cluster centers for levels
    int clusters = rnd.next(1, min(p, 3));
    vector<int> centers(clusters);
    for (int i = 0; i < clusters; i++) {
        centers[i] = rnd.next(1, 500);
    }

    // generate unique nicknames
    set<string> used;
    vector<string> names;
    for (int i = 0; i < p; i++) {
        string s;
        do {
            int len = rnd.next(1, 5);
            s.clear();
            for (int k = 0; k < len; k++) {
                char c = char('a' + rnd.next(0, 9));
                s.push_back(c);
            }
        } while (used.count(s));
        used.insert(s);
        names.push_back(s);
    }

    // generate levels around clusters
    vector<pair<int,string>> players;
    for (int i = 0; i < p; i++) {
        int cid = rnd.next(0, clusters - 1);
        int off = rnd.next(-10, 10);
        int lv = centers[cid] + off;
        if (lv < 1) lv = 1;
        if (lv > 500) lv = 500;
        players.emplace_back(lv, names[i]);
    }

    // randomize arrival order
    shuffle(players.begin(), players.end());

    // output
    println(p, m);
    for (auto &pr : players) {
        println(pr.first, pr.second);
    }
    return 0;
}
