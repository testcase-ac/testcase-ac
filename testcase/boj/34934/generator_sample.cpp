#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string makeName(int index, int style) {
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string code;
    int x = index;
    do {
        code += char('a' + x % 26);
        x /= 26;
    } while (x > 0);

    if (style == 0) {
        return code;
    }
    if (style == 1) {
        string name = string(1, char('a' + (index * 7) % 26));
        name += code;
        return name;
    }
    if (style == 2) {
        string name = code;
        int len = rnd.next((int)name.size(), 15);
        while ((int)name.size() < len) {
            int i = (int)name.size();
            name += alphabet[(index + i * 7 + rnd.next(26)) % 26];
        }
        return name;
    }

    string name = "dept";
    name += code;
    while ((int)name.size() < rnd.next(5, 15)) {
        name += rnd.any(alphabet);
    }
    return name.substr(0, 15);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(13, 30);
    } else {
        n = rnd.next(31, 54);
    }

    int style = rnd.next(4);
    set<string> used;
    vector<pair<string, int>> departments;
    departments.reserve(n);

    int newestIndex = rnd.next(n);
    for (int i = 0; i < n; ++i) {
        string name;
        do {
            name = makeName(i, style);
        } while (!used.insert(name).second);

        int year;
        if (i == newestIndex) {
            year = 2026;
        } else if (mode == 1) {
            year = rnd.any(vector<int>{2001, 2025});
        } else if (mode == 2) {
            year = rnd.next(2001, 2006);
        } else if (mode == 3) {
            year = rnd.next(2020, 2025);
        } else {
            year = rnd.next(2001, 2025);
        }
        departments.emplace_back(name, year);
    }

    shuffle(departments.begin(), departments.end());

    println(n);
    for (const auto& department : departments) {
        println(department.first, department.second);
    }

    return 0;
}
