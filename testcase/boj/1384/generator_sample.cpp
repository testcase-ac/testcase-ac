#include "testlib.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

string makeName(int groupIndex, int personIndex, int style) {
    if (style == 0) {
        return string(1, char('A' + personIndex));
    }
    if (style == 1) {
        return "Person" + string(1, char('A' + groupIndex)) +
               string(1, char('A' + personIndex));
    }

    int len = rnd.next(1, 60);
    string name;
    name.reserve(len);
    for (int i = 0; i < len; ++i) {
        char base = rnd.next(0, 1) == 0 ? 'a' : 'A';
        name.push_back(char(base + rnd.next(0, 25)));
    }
    return name;
}

vector<string> makeNames(int n, int groupIndex, int style) {
    vector<string> names;
    set<string> used;
    for (int i = 0; i < n; ++i) {
        string name;
        do {
            name = makeName(groupIndex, i, style);
        } while (!used.insert(name).second);
        names.push_back(name);
    }
    return names;
}

vector<vector<char>> makeMessages(int n, int mode) {
    vector<vector<char>> messages(n, vector<char>(n - 1, 'P'));

    if (mode == 0) {
        return messages;
    }

    if (mode == 1) {
        messages[rnd.next(0, n - 1)][rnd.next(0, n - 2)] = 'N';
        return messages;
    }

    if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            messages[i][i % (n - 1)] = 'N';
        }
        return messages;
    }

    if (mode == 3) {
        for (int j = 0; j < n - 1; ++j) {
            messages[0][j] = 'N';
        }
        return messages;
    }

    int threshold = rnd.next(15, 55);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (rnd.next(0, 99) < threshold) {
                messages[i][j] = 'N';
            }
        }
    }
    return messages;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int groupCount = rnd.next(1, 4);
    for (int g = 0; g < groupCount; ++g) {
        int n;
        if (g == 0 && rnd.next(0, 3) == 0) {
            n = rnd.any(vector<int>{5, 20});
        } else {
            n = rnd.next(5, 12);
        }

        int nameStyle = rnd.next(0, 2);
        vector<string> names = makeNames(n, g, nameStyle);
        vector<vector<char>> messages = makeMessages(n, rnd.next(0, 4));

        println(n);
        for (int i = 0; i < n; ++i) {
            cout << names[i];
            for (int j = 0; j < n - 1; ++j) {
                cout << ' ' << messages[i][j];
            }
            cout << '\n';
        }
    }
    println(0);

    return 0;
}
