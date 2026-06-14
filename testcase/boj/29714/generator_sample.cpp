#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

const int MAX_COLOR = 1000000000;

struct Operation {
    vector<int> take;
    vector<int> add;
};

void printList(const vector<int>& values) {
    cout << values.size();
    for (int value : values) {
        cout << ' ' << value;
    }
    cout << '\n';
}

int freshColor(const vector<int>& balls) {
    for (int attempt = 0; attempt < 100; ++attempt) {
        int color = rnd.next(1, MAX_COLOR);
        if (find(balls.begin(), balls.end(), color) == balls.end()) {
            return color;
        }
    }
    return MAX_COLOR;
}

vector<int> chooseAvailable(const vector<int>& balls, int count) {
    vector<int> order(balls.size());
    for (int i = 0; i < int(balls.size()); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    vector<int> chosen;
    for (int i = 0; i < count; ++i) {
        chosen.push_back(balls[order[i]]);
    }
    shuffle(chosen.begin(), chosen.end());
    return chosen;
}

void removeChosen(vector<int>& balls, const vector<int>& chosen) {
    map<int, int> need;
    for (int color : chosen) {
        ++need[color];
    }

    vector<int> remaining;
    for (int color : balls) {
        auto it = need.find(color);
        if (it != need.end() && it->second > 0) {
            --it->second;
        } else {
            remaining.push_back(color);
        }
    }
    balls = remaining;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 4 ? 24 : 10);
    int q = rnd.next(1, mode == 4 ? 24 : 12);

    vector<int> palette = {1, 2, 3, 5, 8, 13, MAX_COLOR};
    for (int i = 0; i < 8; ++i) {
        palette.push_back(rnd.next(1, 40));
    }

    vector<int> initial;
    for (int i = 0; i < n; ++i) {
        if (mode == 1 && i % 3 != 0) {
            initial.push_back(palette[rnd.next(0, 3)]);
        } else if (mode == 2 && i + 1 == n) {
            initial.push_back(MAX_COLOR);
        } else {
            initial.push_back(rnd.any(palette));
        }
    }

    vector<int> balls = initial;
    vector<Operation> operations;
    int totalA = 0;
    int totalB = 0;

    for (int step = 0; step < q; ++step) {
        Operation op;
        int kind = rnd.next(0, 5);
        if (mode == 0) {
            kind = step % 6;
        } else if (mode == 3 && step % 2 == 0) {
            kind = 0;
        }

        if (kind == 0) {
            op.take.clear();
        } else if (kind == 1 && !balls.empty()) {
            op.take = chooseAvailable(balls, rnd.next(1, min<int>(4, balls.size())));
        } else if (kind == 2 && !balls.empty()) {
            op.take = chooseAvailable(balls, 1);
            op.take.push_back(op.take[0]);
        } else {
            if (!balls.empty() && rnd.next(0, 1)) {
                op.take = chooseAvailable(balls, rnd.next(1, min<int>(3, balls.size())));
            }
            op.take.push_back(freshColor(balls));
        }

        bool willApply = true;
        map<int, int> have;
        for (int color : balls) {
            ++have[color];
        }
        for (int color : op.take) {
            if (--have[color] < 0) {
                willApply = false;
            }
        }

        int addCount = rnd.next(0, mode == 4 ? 8 : 4);
        if (kind == 4) {
            addCount = 0;
        }
        for (int i = 0; i < addCount; ++i) {
            if (mode == 2 && i % 2 == 0) {
                op.add.push_back(MAX_COLOR - rnd.next(0, 5));
            } else if (!op.take.empty() && rnd.next(0, 2) == 0) {
                op.add.push_back(rnd.any(op.take));
            } else {
                op.add.push_back(rnd.any(palette));
            }
        }

        if (willApply) {
            removeChosen(balls, op.take);
            balls.insert(balls.end(), op.add.begin(), op.add.end());
        }

        totalA += op.take.size();
        totalB += op.add.size();
        operations.push_back(op);
    }

    ensure(totalA <= 200000);
    ensure(totalB <= 200000);

    println(n);
    println(initial);
    println(q);
    for (const Operation& op : operations) {
        printList(op.take);
        printList(op.add);
    }

    return 0;
}
