#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string start = "고무오리 디버깅 시작";
    const string end = "고무오리 디버깅 끝";
    const string duck = "고무오리";
    const string problem = "문제";

    int mode = rnd.next(0, 5);
    int commandCount;
    vector<string> commands;
    int remaining = 0;

    auto addProblem = [&]() {
        commands.push_back(problem);
        ++remaining;
    };

    auto addDuck = [&]() {
        commands.push_back(duck);
        if (remaining > 0) {
            --remaining;
        } else {
            remaining = 2;
        }
    };

    if (mode == 0) {
        commandCount = rnd.next(0, 12);
        for (int i = 0; i < commandCount; ++i) {
            if (rnd.next(0, 1) == 0) {
                addProblem();
            } else {
                addDuck();
            }
        }
    } else if (mode == 1) {
        commandCount = rnd.next(70, 100);
        for (int i = 0; i < commandCount; ++i) {
            if (rnd.next(0, 99) < 55) {
                addProblem();
            } else {
                addDuck();
            }
        }
    } else if (mode == 2) {
        commandCount = rnd.next(1, 35);
        for (int i = 0; i < commandCount; ++i) {
            if (rnd.next(0, 99) < 80) {
                addDuck();
            } else {
                addProblem();
            }
        }
    } else if (mode == 3) {
        commandCount = rnd.next(1, 35);
        for (int i = 0; i < commandCount; ++i) {
            if (rnd.next(0, 99) < 75) {
                addProblem();
            } else {
                addDuck();
            }
        }
    } else if (mode == 4) {
        commandCount = rnd.next(0, 45);
        for (int i = 0; i < commandCount; ++i) {
            if (remaining == 0 || rnd.next(0, 99) < 60) {
                addProblem();
            } else {
                addDuck();
            }
        }
        while (remaining > 0 && (int)commands.size() < 100) {
            addDuck();
        }
    } else {
        commandCount = rnd.next(1, 45);
        for (int i = 0; i < commandCount; ++i) {
            if (rnd.next(0, 99) < 45) {
                addProblem();
            } else {
                addDuck();
            }
        }
        if (remaining == 0 && (int)commands.size() < 100) {
            addProblem();
        }
    }

    println(start);
    for (const string& command : commands) {
        println(command);
    }
    println(end);

    return 0;
}
