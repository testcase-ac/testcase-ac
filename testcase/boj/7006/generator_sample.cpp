#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

string randomJump(int pos, int m) {
    vector<int> targets;
    for (int target = 0; target <= m + 1; ++target) {
        if (target != pos) {
            targets.push_back(target);
        }
    }

    int target = rnd.any(targets);
    int amount = abs(target - pos);
    return string(target > pos ? "+" : "-") + to_string(amount);
}

string instructionFor(int pos, int m, int mode) {
    if (mode == 0) {
        return rnd.next(4) == 0 ? randomJump(pos, m) : "0";
    }

    if (mode == 1) {
        return rnd.next(3) == 0 ? "L" : "0";
    }

    if (mode == 2) {
        if (pos > 0 && rnd.next(100) < 65) {
            int target = rnd.next(0, pos - 1);
            return "-" + to_string(pos - target);
        }
        return rnd.next(2) == 0 ? "L" : "0";
    }

    if (mode == 3) {
        if (pos < m + 1 && rnd.next(100) < 65) {
            int target = rnd.next(pos + 1, m + 1);
            return "+" + to_string(target - pos);
        }
        return rnd.next(3) == 0 ? "L" : "0";
    }

    int choice = rnd.next(100);
    if (choice < 35) {
        return "0";
    }
    if (choice < 55) {
        return "L";
    }
    return randomJump(pos, m);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(4, 10);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = tc % 5;
        if (tc >= 5) {
            mode = rnd.next(0, 4);
        }

        int m;
        if (tc == 0) {
            m = rnd.next(1, 3);
        } else if (mode == 4) {
            m = rnd.next(8, 16);
        } else {
            m = rnd.next(3, 12);
        }

        int T;
        if (mode == 2) {
            T = rnd.next(1, 12);
        } else if (mode == 3) {
            T = rnd.next(2, 20);
        } else {
            T = rnd.next(1, 40);
        }

        println(m, T);

        vector<string> instructions;
        for (int pos = 1; pos <= m; ++pos) {
            instructions.push_back(instructionFor(pos, m, mode));
        }
        println(instructions);
    }

    return 0;
}
