#include "testlib.h"

#include <vector>

using namespace std;

const long long INITIAL_MAX = 1234567890123LL;
const long long REMOVE_SUM_LIMIT = 1234567890120LL;
const long long VALUE_LIMIT = 1000000000000000000LL;

struct Command {
    int op;
    long long x;
};

bool inBounds(__int128 first, __int128 mul, __int128 add) {
    __int128 minValue = first * mul + add;
    __int128 maxValue = (__int128)INITIAL_MAX * mul + add;
    return -(__int128)VALUE_LIMIT <= minValue && minValue <= (__int128)VALUE_LIMIT &&
           -(__int128)VALUE_LIMIT <= maxValue && maxValue <= (__int128)VALUE_LIMIT;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = rnd.next(1, mode == 4 ? 80 : 35);
    vector<Command> commands;

    __int128 first = 1;
    __int128 mul = 1;
    __int128 add = 0;
    __int128 removed = 0;

    for (int i = 0; i + 1 < q; ++i) {
        vector<Command> candidates;

        if (mode == 0 || rnd.next(100) < 65) {
            int span = rnd.any(vector<int>{5, 100, 1000, 100000});
            candidates.push_back({0, rnd.next(-span, span)});
        }

        if (mode != 1 || rnd.next(100) < 35) {
            int hi = rnd.any(vector<int>{2, 3, 10, 100});
            candidates.push_back({1, rnd.next(1, hi)});
        }

        if (removed < (__int128)REMOVE_SUM_LIMIT && (mode != 2 || rnd.next(100) < 80)) {
            int removeHi = rnd.any(vector<int>{1, 3, 20, 1000, 100000000});
            long long remaining = (long long)min((__int128)removeHi, (__int128)REMOVE_SUM_LIMIT - removed);
            candidates.push_back({2, rnd.next(1LL, remaining)});
        }

        if (rnd.next(100) < 25 + mode * 10) {
            candidates.push_back({3, 0});
        }

        shuffle(candidates.begin(), candidates.end());
        bool accepted = false;
        for (Command command : candidates) {
            __int128 nextFirst = first;
            __int128 nextMul = mul;
            __int128 nextAdd = add;
            __int128 nextRemoved = removed;

            if (command.op == 0) {
                nextAdd += command.x;
            } else if (command.op == 1) {
                nextMul *= command.x;
                nextAdd *= command.x;
            } else if (command.op == 2) {
                nextRemoved += command.x;
                nextFirst += command.x;
            }

            if (nextRemoved <= (__int128)REMOVE_SUM_LIMIT && inBounds(nextFirst, nextMul, nextAdd)) {
                commands.push_back(command);
                first = nextFirst;
                mul = nextMul;
                add = nextAdd;
                removed = nextRemoved;
                accepted = true;
                break;
            }
        }

        if (!accepted) {
            commands.push_back({3, 0});
        }
    }

    commands.push_back({3, 0});

    println((int)commands.size());
    for (Command command : commands) {
        if (command.op == 3) {
            println(3);
        } else {
            println(command.op, command.x);
        }
    }

    return 0;
}
