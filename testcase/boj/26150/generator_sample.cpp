#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

char randomChar(const string& pool) {
    return pool[rnd.next((int)pool.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const string digits = "0123456789";
    const string alnum = uppercase + lowercase + digits;

    int mode = rnd.next(5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 15);
    } else if (mode == 3) {
        n = rnd.next(16, 35);
    } else {
        n = rnd.next(40, 100);
    }

    vector<int> ids;
    set<int> usedIds;
    int idStyle = rnd.next(4);
    while ((int)ids.size() < n) {
        int id;
        if (idStyle == 0) {
            id = (int)ids.size() + 1;
        } else if (idStyle == 1) {
            id = 100000 - (int)ids.size();
        } else if (idStyle == 2) {
            id = ((int)ids.size() + 1) * rnd.next(2, 17);
            id = min(id, 100000);
        } else {
            id = rnd.next(1, 100000);
        }
        if (usedIds.insert(id).second) ids.push_back(id);
    }

    vector<tuple<string, int, int>> rows;
    int forcedKind = rnd.next(3);
    for (int i = 0; i < n; ++i) {
        int len;
        if (mode == 0) {
            len = rnd.next(1, 4);
        } else if (mode == 4 && rnd.next(4) == 0) {
            len = rnd.next(40, 100);
        } else {
            len = rnd.next(1, 25);
        }

        string s(len, 'A');
        for (int j = 0; j < len; ++j) {
            if (forcedKind == 0) {
                s[j] = randomChar(alnum);
            } else if (forcedKind == 1) {
                s[j] = randomChar(uppercase + lowercase);
            } else {
                s[j] = randomChar(digits + lowercase);
            }
        }

        int d = rnd.next(1, len);
        int selectedKind = rnd.next(4);
        if (selectedKind == 0) {
            s[d - 1] = randomChar(lowercase);
        } else if (selectedKind == 1) {
            s[d - 1] = randomChar(uppercase);
        } else if (selectedKind == 2) {
            s[d - 1] = randomChar(digits);
        }

        rows.emplace_back(s, ids[i], d);
    }

    if (rnd.next(2) == 0) shuffle(rows.begin(), rows.end());

    println(n);
    for (const auto& [s, id, d] : rows) {
        println(s, id, d);
    }

    return 0;
}
