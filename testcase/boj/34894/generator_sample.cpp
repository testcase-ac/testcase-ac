#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long randomCost(int profile) {
    if (profile == 0) return rnd.next(1, 20);
    if (profile == 1) return rnd.next(1, 1000000);
    if (rnd.next(0, 4) == 0) return 1000000000LL;
    return rnd.next(900000000, 1000000000);
}

void printCase(const string& s, const vector<long long>& costs) {
    println((int)s.size());
    println(s);
    println(costs);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "UOSPC";
    const string target = "UOSPC";
    int mode = rnd.next(0, 5);
    int costProfile = rnd.next(0, 2);
    string s;

    if (mode == 0) {
        s = target;
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) {
            int pos = rnd.next(0, (int)s.size());
            s.insert(s.begin() + pos, rnd.any(alphabet));
        }
    } else if (mode == 1) {
        s = target;
        for (char c : alphabet) {
            int repeats = rnd.next(0, 5);
            for (int i = 0; i < repeats; ++i) {
                int pos = rnd.next(0, (int)s.size());
                s.insert(s.begin() + pos, c);
            }
        }
    } else if (mode == 2) {
        vector<char> chars(target.begin(), target.end());
        shuffle(chars.begin(), chars.end());
        s.assign(chars.begin(), chars.end());
        int extra = rnd.next(0, 15);
        for (int i = 0; i < extra; ++i) s += rnd.any(alphabet);
    } else if (mode == 3) {
        string reduced = alphabet;
        reduced.erase(reduced.begin() + rnd.next(0, (int)reduced.size() - 1));
        int n = rnd.next(5, 30);
        for (int i = 0; i < n; ++i) s += rnd.any(reduced);
    } else if (mode == 4) {
        int n = rnd.next(5, 40);
        for (int i = 0; i < n; ++i) {
            int block = i * 5 / n;
            s += target[block];
        }
        for (int i = 0; i < n / 4; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(s[x], s[y]);
        }
    } else {
        int n = rnd.next(5, 50);
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    }

    while ((int)s.size() < 5) s += rnd.any(alphabet);
    vector<long long> costs(s.size());
    for (long long& cost : costs) cost = randomCost(costProfile);

    if (rnd.next(0, 3) == 0) {
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == target[i % (int)target.size()]) costs[i] = 1000000000LL;
        }
    }

    printCase(s, costs);
    return 0;
}
