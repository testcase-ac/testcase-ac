#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomTitle(int maxLen, const vector<string>& pool) {
    if (!pool.empty() && rnd.next(100) < 45) {
        return rnd.any(pool);
    }

    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('a' + rnd.next(26)));
    }
    return s;
}

void pushBook(vector<string>& actions, vector<string>& stack, const string& title) {
    actions.push_back(title);
    stack.push_back(title);
}

void readBook(vector<string>& actions, vector<string>& stack) {
    actions.push_back("READ");
    stack.pop_back();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int q = 0;
    vector<string> pool = {"a", "b", "aa", "zz", "alpha", "omega", "abcdefghij"};
    vector<string> actions;
    vector<string> stack;

    if (mode == 0) {
        q = rnd.next(2, 20);
        if (q % 2 == 1) --q;
        for (int i = 0; i < q / 2; ++i) {
            pushBook(actions, stack, randomTitle(10, pool));
            readBook(actions, stack);
        }
    } else if (mode == 1) {
        int depth = rnd.next(1, 60);
        q = depth * 2;
        for (int i = 0; i < depth; ++i) {
            pushBook(actions, stack, randomTitle(10, pool));
        }
        while (!stack.empty()) {
            readBook(actions, stack);
        }
    } else if (mode == 2) {
        q = rnd.next(10, 120);
        for (int i = 0; i < q; ++i) {
            bool mustPush = stack.empty();
            bool leaveRoomForRead = static_cast<int>(actions.size()) + static_cast<int>(stack.size()) >= q;
            if (mustPush || (!leaveRoomForRead && rnd.next(100) < 62)) {
                pushBook(actions, stack, randomTitle(8, pool));
            } else {
                readBook(actions, stack);
            }
        }
    } else if (mode == 3) {
        q = rnd.next(15, 90);
        vector<string> duplicates = {"same", "same", "readable", "book", "book"};
        for (int i = 0; i < q; ++i) {
            if (stack.empty() || rnd.next(100) < 70) {
                pushBook(actions, stack, randomTitle(10, duplicates));
            } else {
                readBook(actions, stack);
            }
        }
    } else {
        int prefix = rnd.next(1, 25);
        int middle = rnd.next(0, 35);
        q = prefix + middle + prefix;
        for (int i = 0; i < prefix; ++i) {
            pushBook(actions, stack, randomTitle(10, pool));
        }
        for (int i = 0; i < middle; ++i) {
            if (stack.empty() || rnd.next(2) == 0) {
                pushBook(actions, stack, randomTitle(10, pool));
            } else {
                readBook(actions, stack);
            }
        }
        while (static_cast<int>(actions.size()) < q) {
            if (stack.empty()) {
                pushBook(actions, stack, randomTitle(10, pool));
            } else {
                readBook(actions, stack);
            }
        }
    }

    bool hasRead = false;
    for (const string& action : actions) {
        if (action == "READ") hasRead = true;
    }
    if (!hasRead) {
        actions.back() = "READ";
    }

    println(static_cast<int>(actions.size()));
    for (const string& action : actions) {
        println(action);
    }

    return 0;
}
