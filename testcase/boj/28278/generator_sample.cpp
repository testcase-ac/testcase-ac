#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 40);
    int mode = rnd.next(0, 4);
    vector<string> commands;
    commands.reserve(n);

    int depth = 0;
    bool hasOutputCommand = false;
    vector<int> boundaryValues = {1, 2, 99999, 100000};

    auto addOutputCommand = [&](int command) {
        commands.push_back(to_string(command));
        hasOutputCommand = true;
    };

    auto addPushCommand = [&]() {
        int x;
        if (rnd.next(100) < 30) {
            x = rnd.any(boundaryValues);
        } else if (mode == 3) {
            x = rnd.next(99990, 100000);
        } else {
            x = rnd.next(1, 100000);
        }
        commands.push_back("1 " + to_string(x));
        ++depth;
    };

    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(100);
        if (mode == 0) {
            if (choice < 45) addPushCommand();
            else if (choice < 65) {
                addOutputCommand(2);
                if (depth > 0) --depth;
            } else if (choice < 80) {
                addOutputCommand(3);
            } else if (choice < 90) {
                addOutputCommand(4);
            } else {
                addOutputCommand(5);
            }
        } else if (mode == 1) {
            if (choice < 35) {
                addOutputCommand(rnd.any(vector<int>{2, 4, 5}));
                if (commands.back() == "2" && depth > 0) --depth;
            } else if (choice < 70) {
                addPushCommand();
            } else {
                addOutputCommand(3);
            }
        } else if (mode == 2) {
            if (i < n / 2 || (depth == 0 && choice < 70)) {
                addPushCommand();
            } else if (choice < 65) {
                addOutputCommand(2);
                --depth;
            } else {
                addOutputCommand(rnd.any(vector<int>{3, 5}));
            }
        } else {
            if (choice < 50) addPushCommand();
            else addOutputCommand(rnd.next(2, 5));
            if (!commands.empty() && commands.back() == "2" && depth > 0) --depth;
        }
    }

    if (!hasOutputCommand) {
        commands[rnd.next((int)commands.size())] = to_string(rnd.next(3, 5));
    }

    println((int)commands.size());
    for (const string& command : commands) {
        println(command);
    }

    return 0;
}
