#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

static const int MAX_VALUE = (1 << 25) - 1;

static int randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(0, 31);
    }
    if (mode == 1) {
        return MAX_VALUE - rnd.next(0, 31);
    }
    if (mode == 2) {
        int bit = rnd.next(0, 24);
        int delta = rnd.next(-3, 3);
        return max(0, min(MAX_VALUE, (1 << bit) + delta));
    }
    return rnd.next(0, MAX_VALUE);
}

static int pickExisting(const map<int, int>& count) {
    int target = rnd.next(0, (int)count.size() - 1);
    auto it = count.begin();
    advance(it, target);
    return it->first;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 10);
        int q = rnd.next(8, 24);
        int valueMode = rnd.next(0, 3);

        vector<int> initial;
        map<int, int> count;
        int total = 0;

        for (int i = 0; i < n; ++i) {
            int value;
            if (!initial.empty() && rnd.next(0, 99) < 35) {
                value = rnd.any(initial);
            } else {
                value = randomValue(valueMode);
            }
            initial.push_back(value);
            ++count[value];
            ++total;
        }

        vector<vector<int>> ops;
        for (int i = 0; i < q; ++i) {
            vector<int> choices = {1, 2, 3};
            if (count.size() > 1 || total - count.begin()->second > 0) {
                choices.push_back(4);
            }
            if (count.size() > 1 || total - count.rbegin()->second > 0) {
                choices.push_back(5);
            }

            int op = rnd.any(choices);
            if (i + 2 >= q) {
                op = rnd.next(1, 3);
            }

            if (op <= 3) {
                int value;
                if (rnd.next(0, 99) < 45) {
                    value = pickExisting(count);
                } else if (rnd.next(0, 99) < 30) {
                    value = rnd.any(vector<int>{0, 1, MAX_VALUE, MAX_VALUE - 1});
                } else {
                    value = randomValue(valueMode);
                }
                ops.push_back({op, value});
                if (op == 3) {
                    ++count[value];
                    ++total;
                }
            } else {
                ops.push_back({op});
                if (op == 4) {
                    total -= count.begin()->second;
                    count.erase(count.begin());
                } else {
                    auto it = prev(count.end());
                    total -= it->second;
                    count.erase(it);
                }
            }
        }

        println(n, q);
        println(initial);
        for (const vector<int>& op : ops) {
            println(op);
        }
    }

    return 0;
}
