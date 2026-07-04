#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string makeName(int id, int len) {
    string name;
    do {
        name.push_back(char('A' + (id % 26)));
        id /= 26;
    } while (id > 0);
    reverse(name.begin(), name.end());

    while ((int)name.size() < len) {
        char next = char('A' + rnd.next(26));
        name.push_back(next);
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int towns = rnd.next(1, 12);
    vector<string> names;
    names.reserve(towns);
    for (int i = 0; i < towns; ++i) {
        int len = rnd.next(1, 7);
        names.push_back(makeName(i, len));
    }

    int maxLen = 1;
    for (const string& name : names) {
        maxLen = max(maxLen, (int)name.size());
    }

    int r = towns * 3;
    int c = rnd.next(maxLen + 2, min(50, maxLen + 12));
    vector<string> grid(r, string(c, '.'));

    for (int i = 0; i < towns; ++i) {
        int bandTop = i * 3;
        bool townAbove = rnd.next(2) == 0;
        int nameRow = bandTop + (townAbove ? 1 : 0);
        int townRow = bandTop + (townAbove ? 0 : 1);
        int len = (int)names[i].size();
        int left = rnd.next(0, c - len);
        int townCol = rnd.next(left, left + len - 1);

        for (int j = 0; j < len; ++j) {
            grid[nameRow][left + j] = names[i][j];
        }
        grid[townRow][townCol] = 'x';
    }

    println(r, c);
    for (const string& row : grid) {
        println(row);
    }
    return 0;
}
