#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomName(int minLen, int maxLen, const string& alphabet) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string withSuffix(const string& prefix, int index) {
    string s = prefix;
    do {
        s.push_back(char('A' + index % 26));
        index /= 26;
    } while (index > 0 && (int)s.size() < 30);
    return s;
}

void addUnique(set<string>& used, vector<string>& names, string candidate) {
    if ((int)candidate.size() > 30) {
        candidate.resize(30);
    }
    while (!used.insert(candidate).second) {
        if ((int)candidate.size() < 30) {
            candidate.push_back('A');
        } else {
            for (int i = 29; i >= 0; --i) {
                if (candidate[i] != 'Z') {
                    ++candidate[i];
                    break;
                }
                candidate[i] = 'A';
            }
        }
    }
    names.push_back(candidate);
}

vector<string> makeCase(int n, int mode) {
    set<string> used;
    vector<string> names;

    if (mode == 0) {
        string alphabet = rnd.next(0, 1) ? "ABCDEF" : "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        while ((int)names.size() < n) {
            addUnique(used, names, randomName(1, rnd.next(1, 8), alphabet));
        }
    } else if (mode == 1) {
        string prefix = randomName(1, 5, "ABCDEFGHIJKLMNOPQRSTUVW");
        for (int i = 0; i < n; ++i) {
            addUnique(used, names, withSuffix(prefix, i));
        }
    } else if (mode == 2) {
        string left = randomName(1, 6, "ABCDEFGHIJKLM");
        string right = left;
        int shifted = min<int>('Z', right.back() + rnd.next(1, 3));
        right.back() = char(shifted);
        addUnique(used, names, left);
        addUnique(used, names, right);
        while ((int)names.size() < n) {
            string base = rnd.next(0, 1) ? left : right;
            addUnique(used, names, base + randomName(1, 5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        }
    } else {
        int len = rnd.next(20, 30);
        for (int i = 0; i < n; ++i) {
            string s(len, char('A' + (i % 26)));
            int pos = rnd.next(0, len - 1);
            s[pos] = char('A' + rnd.next(0, 25));
            addUnique(used, names, s);
        }
    }

    shuffle(names.begin(), names.end());
    return names;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 6);
    for (int tc = 0; tc < cases; ++tc) {
        int n = 2 * rnd.next(1, 10);
        if (tc == cases - 1 && rnd.next(0, 2) == 0) {
            n = 2 * rnd.next(12, 25);
        }

        vector<string> names = makeCase(n, tc % 4);
        println(n);
        for (const string& name : names) {
            println(name);
        }
    }
    println(0);
}
