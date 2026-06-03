#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string repeatChar(char c, int count) {
    return string(count, c);
}

string goodName() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return repeatChar('a', rnd.next(1, 10));
    if (mode == 1) return repeatChar('-', rnd.next(1, 10));
    if (mode == 2) return "a" + repeatChar('1', rnd.next(0, 8)) + "A";
    if (mode == 3) return "ab-" + repeatChar('2', rnd.next(0, 7));
    if (mode == 4) return "a-A-" + repeatChar('b', rnd.next(0, 6));
    return "z9-" + repeatChar('z', rnd.next(0, 7));
}

string badName() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return repeatChar('A', rnd.next(1, 10));
    if (mode == 1) return repeatChar('1', rnd.next(1, 10));
    if (mode == 2) return repeatChar('a', rnd.next(11, 20));
    if (mode == 3) {
        int lower = rnd.next(0, 6);
        return repeatChar('A', lower + 1) + repeatChar('a', lower);
    }
    if (mode == 4) return repeatChar('-', 11 + rnd.next(0, 9));
    return repeatChar('9', rnd.next(11, 20));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    int answerIndex = rnd.next(0, n - 1);

    vector<string> names;
    names.reserve(n);
    for (int i = 0; i < n; ++i) {
        names.push_back(i == answerIndex ? goodName() : badName());
    }

    println(n);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
