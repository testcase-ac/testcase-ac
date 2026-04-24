#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of distinct sock types
    int T = rnd.next(1, 5);
    set<string> used;
    vector<string> names;
    // Generate unique lowercase names of length 1..6
    for (int i = 0; i < T; i++) {
        int len = rnd.next(1, 6);
        string s;
        do {
            s.clear();
            for (int j = 0; j < len; j++)
                s.push_back(char('a' + rnd.next(0, 25)));
        } while (used.count(s));
        used.insert(s);
        names.push_back(s);
    }
    // Hyper-parameter: maximum socks in a group
    int maxK = rnd.next(1, 10);

    vector<tuple<string,string,int>> groups;
    vector<string> fits = {"any", "left", "right"};
    // For each type, pick 1..3 fits and assign random counts
    for (auto &nm : names) {
        shuffle(fits.begin(), fits.end());
        int fi = rnd.next(1, 3);
        for (int j = 0; j < fi; j++) {
            string f = fits[j];
            int k = rnd.next(1, maxK);
            groups.emplace_back(nm, f, k);
        }
    }
    // Shuffle output order
    shuffle(groups.begin(), groups.end());
    // Print result
    println((int)groups.size());
    for (auto &g : groups) {
        string nm, f; int k;
        tie(nm, f, k) = g;
        println(nm, f, k);
    }
    return 0;
}
