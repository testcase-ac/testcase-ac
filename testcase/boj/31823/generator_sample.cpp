#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeName(int index) {
    string name;
    do {
        name.push_back(char('a' + index % 26));
        index /= 26;
    } while (index > 0);
    return name;
}

vector<char> makeActivity(int m, int mode) {
    vector<char> activity(m, '*');

    if (mode == 0) {
        return activity;
    }

    if (mode == 1) {
        for (int i = 0; i < m; ++i) activity[i] = '.';
        return activity;
    }

    if (mode == 2) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < m; ++i) activity[i] = ((i + start) % 2 == 0 ? '*' : '.');
        return activity;
    }

    if (mode == 3) {
        int pos = 0;
        while (pos < m) {
            char value = rnd.next(0, 1) == 0 ? '*' : '.';
            int length = rnd.next(1, 5);
            for (int i = 0; i < length && pos < m; ++i, ++pos) activity[pos] = value;
        }
        return activity;
    }

    int missPercent = rnd.next(15, 85);
    for (int i = 0; i < m; ++i) activity[i] = (rnd.next(1, 100) <= missPercent ? '.' : '*');
    return activity;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 24);

    println(n, m);
    for (int i = 0; i < n; ++i) {
        vector<char> activity = makeActivity(m, rnd.next(0, 4));
        for (int j = 0; j < m; ++j) {
            if (j > 0) cout << ' ';
            cout << activity[j];
        }
        cout << ' ' << makeName(i) << '\n';
    }

    return 0;
}
