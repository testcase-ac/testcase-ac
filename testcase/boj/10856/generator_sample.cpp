#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Method {
    string id;
    vector<int> callers;
};

string methodId(int index, bool isProgram) {
    string packageName = "P" + to_string(index);
    string methodName = isProgram ? "PROGRAM" : "M" + to_string(index);
    return packageName + "::" + methodName;
}

void addCall(vector<Method>& methods, int caller, int callee) {
    if (caller == callee && rnd.next(0, 3) == 0) {
        return;
    }
    vector<int>& callers = methods[callee].callers;
    if (find(callers.begin(), callers.end(), caller) == callers.end()) {
        callers.push_back(caller);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int mode = rnd.next(0, 5);
    int programCount = rnd.next(0, min(n, 3));
    if (mode == 1 || mode == 2 || mode == 4) {
        programCount = max(1, programCount);
    }

    set<int> programIndices;
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i < programCount; ++i) {
        programIndices.insert(order[i]);
    }

    vector<string> ids(n);
    vector<Method> methods(n);
    for (int i = 0; i < n; ++i) {
        ids[i] = methodId(i, programIndices.count(i));
        methods[i].id = ids[i];
    }

    if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addCall(methods, i - 1, i);
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            int caller = rnd.next(0, i - 1);
            addCall(methods, caller, i);
        }
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                addCall(methods, rnd.next(0, i - 1), i);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            addCall(methods, i, (i + 1) % n);
        }
        if (n >= 4) {
            addCall(methods, 0, 2);
            addCall(methods, 2, 0);
        }
    } else if (mode == 4) {
        vector<int> programs(programIndices.begin(), programIndices.end());
        for (int i = 0; i < n; ++i) {
            if (!programIndices.count(i) && rnd.next(0, 1) == 0) {
                addCall(methods, rnd.any(programs), i);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!programIndices.count(i) && rnd.next(0, 2) == 0) {
                addCall(methods, i, rnd.next(0, n - 1));
            }
        }
    } else {
        double density = rnd.next(0.0, 0.35);
        for (int caller = 0; caller < n; ++caller) {
            for (int callee = 0; callee < n; ++callee) {
                if (rnd.next() < density) {
                    addCall(methods, caller, callee);
                }
            }
        }
    }

    shuffle(methods.begin(), methods.end());
    println(n);
    for (Method& method : methods) {
        shuffle(method.callers.begin(), method.callers.end());
        println(method.id, (int)method.callers.size());
        for (int j = 0; j < (int)method.callers.size(); ++j) {
            if (j > 0) {
                printf(" ");
            }
            printf("%s", ids[method.callers[j]].c_str());
        }
        printf("\n");
    }

    return 0;
}
