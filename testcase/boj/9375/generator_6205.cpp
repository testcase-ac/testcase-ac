#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

string randStr(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += char('a' + rnd.next(0, 25));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Number of clothes
        int n = rnd.next(0, 20);
        println(n);
        if (n == 0) continue;

        // Decide number of types (at least 1, up to min(n,10)), biased with wnext
        int hiTypes = min(n, 10);
        int w = rnd.next(-1, 1);
        int t = rnd.wnext(hiTypes, w) + 1;  // in [1..hiTypes]

        // Distribute n items into t types (each gets at least 1)
        vector<int> cnt(t, 1);
        int rem = n - t;
        for (int i = 0; i < rem; i++) {
            int idx = rnd.next(0, t - 1);
            cnt[idx]++;
        }

        // Generate unique type names
        vector<string> types;
        set<string> usedTypes;
        for (int i = 0; i < t; i++) {
            string s;
            do {
                s = randStr(rnd.next(3, 8));
            } while (usedTypes.count(s));
            usedTypes.insert(s);
            types.push_back(s);
        }

        // Generate items
        vector<pair<string,string>> items;
        set<string> usedItems;
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                string it;
                do {
                    it = randStr(rnd.next(3, 10));
                } while (usedItems.count(it));
                usedItems.insert(it);
                items.emplace_back(it, types[i]);
            }
        }

        // Shuffle to vary order
        shuffle(items.begin(), items.end());

        // Output item lines
        for (auto &pr : items) {
            println(pr.first, pr.second);
        }
    }
    return 0;
}
