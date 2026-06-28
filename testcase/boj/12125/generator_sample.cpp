#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomSpell(int m, int mode) {
    vector<int> spell(m, 0);

    if (m == 1) {
        if (mode == 0) {
            spell[0] = 0;
        } else if (mode == 1) {
            spell[0] = rnd.next(1, 100);
        } else if (mode == 2) {
            spell[0] = -rnd.next(1, 100);
        } else {
            spell[0] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
        }
        return spell;
    }

    if (mode == 0) {
        spell[0] = rnd.next(1, 100);
        spell[1] = rnd.next(1, 100);
    } else if (mode == 1) {
        spell[0] = -rnd.next(1, 100);
        spell[1] = -rnd.next(1, 100);
    } else if (mode == 2) {
        spell[0] = rnd.next(1, 100);
        spell[1] = -rnd.next(1, 100);
    } else if (mode == 3) {
        spell[0] = -rnd.next(1, 100);
        spell[1] = rnd.next(1, 100);
    } else if (mode == 4) {
        spell[0] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
        spell[1] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
    } else {
        spell[0] = 0;
        spell[1] = rnd.next(-100, 100);
        if (rnd.next(2) == 0) {
            swap(spell[0], spell[1]);
        }
    }

    return spell;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int m = (tc == 0 ? 1 : tc == 1 ? 2 : rnd.next(1, 2));
        int n;
        if (tc < 2) {
            n = rnd.next(1, 5);
        } else if (rnd.next(5) == 0) {
            n = rnd.next(20, 40);
        } else {
            n = rnd.next(1, 12);
        }

        println(n, m);

        vector<vector<int>> spells;
        for (int i = 0; i < n; ++i) {
            int modes = (m == 1 ? 4 : 6);
            spells.push_back(randomSpell(m, (i < modes ? i : rnd.next(modes))));
        }
        shuffle(spells.begin(), spells.end());

        for (const vector<int>& spell : spells) {
            println(spell);
        }
    }

    return 0;
}
