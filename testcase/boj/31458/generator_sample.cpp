#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string expression(int prefix, int value, int suffix) {
    return string(prefix, '!') + char('0' + value) + string(suffix, '!');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> cases;

    for (int value = 0; value <= 1; ++value) {
        cases.push_back(expression(0, value, 0));
        cases.push_back(expression(1, value, 0));
        cases.push_back(expression(0, value, 1));
        cases.push_back(expression(1, value, 1));
        cases.push_back(expression(2, value, 2));
        cases.push_back(expression(30, value, 0));
        cases.push_back(expression(0, value, 30));
        cases.push_back(expression(30, value, 30));
    }

    int extra = rnd.next(8, 24);
    for (int i = 0; i < extra; ++i) {
        int prefix;
        int suffix;

        int mode = rnd.next(4);
        if (mode == 0) {
            prefix = rnd.next(0, 3);
            suffix = rnd.next(0, 3);
        } else if (mode == 1) {
            prefix = rnd.next(27, 30);
            suffix = rnd.next(0, 3);
        } else if (mode == 2) {
            prefix = rnd.next(0, 3);
            suffix = rnd.next(27, 30);
        } else {
            prefix = rnd.next(0, 30);
            suffix = rnd.next(0, 30);
        }

        cases.push_back(expression(prefix, rnd.next(0, 1), suffix));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
