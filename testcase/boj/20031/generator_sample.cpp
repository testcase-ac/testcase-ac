#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

string repeatedCommand(int n, char c) {
    return string(n, c);
}

string randomCommand(int n, const string& alphabet) {
    string command;
    command.reserve(n);
    for (int i = 0; i < n; ++i) {
        command.push_back(rnd.any(alphabet));
    }
    return command;
}

string wallBounceCommand(int n) {
    const vector<string> patterns = {"LR", "RL", "UD", "DU", "LURD", "RDLU"};
    string pattern = rnd.any(patterns);
    string command;
    command.reserve(n);
    while (static_cast<int>(command.size()) < n) {
        command += pattern;
    }
    command.resize(n);
    return command;
}

pair<int, int> randomQuery(int mode) {
    if (mode == 0) {
        const vector<pair<int, int>> nearWall = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1},
            {-2, 0}, {2, 0}, {0, -2}, {0, 2},
        };
        return rnd.any(nearWall);
    }

    if (mode == 1) {
        vector<int> edges = {-300000, -299999, 299999, 300000};
        return {rnd.any(edges), rnd.any(edges)};
    }

    int bound = rnd.next(2, 20);
    int x = rnd.next(-bound, bound);
    int y = rnd.next(-bound, bound);
    if (x == 0 && y == 0) {
        if (rnd.next(2) == 0) {
            x = rnd.next(2) == 0 ? -1 : 1;
        } else {
            y = rnd.next(2) == 0 ? -1 : 1;
        }
    }
    return {x, y};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 40);
    int q = rnd.next(1, 30);

    string command;
    if (mode == 0) {
        command = wallBounceCommand(n);
    } else if (mode == 1) {
        command = repeatedCommand(n, rnd.any(string("LRUD")));
    } else if (mode == 2) {
        command = randomCommand(n, rnd.any(vector<string>{"LR", "UD", "LU", "RD"}));
    } else {
        command = randomCommand(n, "LRUD");
    }

    println(n);
    println(command);
    println(q);

    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(0, 2);
        if (mode == 1 && rnd.next(3) == 0) {
            queryMode = 1;
        }
        auto [x, y] = randomQuery(queryMode);
        println(x, y);
    }

    return 0;
}
