#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

struct Query {
    char type;
    int value;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(10, 25);
    } else if (mode == 2) {
        n = rnd.next(25, 60);
    } else {
        n = rnd.next(40, 120);
    }

    vector<Query> queries(n + 1);
    vector<int> previous(n + 1, -1);
    vector<int> last(n + 1, -1);
    vector<int> size(n + 1, 0);

    auto cowId = [&]() {
        int style = rnd.next(0, 5);
        if (style == 0) return 1;
        if (style == 1) return 1000000;
        if (style == 2) return rnd.next(1, 10);
        if (style == 3) return rnd.next(999990, 1000000);
        return rnd.next(1, 1000000);
    };

    for (int i = 1; i <= n; ++i) {
        vector<char> choices;
        choices.push_back('a');

        if (size[i - 1] > 0) {
            int sellWeight = (mode == 1 ? 5 : 2);
            for (int j = 0; j < sellWeight; ++j) choices.push_back('s');
        }

        if (i > 1) {
            int travelWeight = (mode == 2 ? 7 : 3);
            for (int j = 0; j < travelWeight; ++j) choices.push_back('t');
        }

        char type = rnd.any(choices);

        if (mode == 0 && i <= 3) {
            type = 'a';
        } else if (mode == 3 && i % 5 == 0) {
            type = 't';
        } else if (mode == 1 && size[i - 1] > 0 && rnd.next(0, 3) == 0) {
            type = 's';
        }

        if (type == 's' && size[i - 1] == 0) {
            type = 'a';
        }
        if (type == 't' && i == 1) {
            type = 'a';
        }

        if (type == 'a') {
            int value = cowId();
            queries[i] = {type, value};
            previous[i] = i - 1;
            last[i] = value;
            size[i] = size[i - 1] + 1;
        } else if (type == 's') {
            queries[i] = {type, 0};
            int restored = previous[i - 1];
            previous[i] = previous[restored];
            last[i] = last[restored];
            size[i] = size[restored];
        } else {
            int value;
            if (mode == 2 && rnd.next(0, 1) == 0) {
                value = rnd.next(1, max(1, i / 3));
            } else if (mode == 3 && rnd.next(0, 2) == 0) {
                value = i;
            } else {
                value = rnd.next(1, i);
            }

            queries[i] = {type, value};
            int restored = value - 1;
            previous[i] = previous[restored];
            last[i] = last[restored];
            size[i] = size[restored];
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (queries[i].type == 's') {
            println("s");
        } else {
            println(string(1, queries[i].type), queries[i].value);
        }
    }

    return 0;
}
