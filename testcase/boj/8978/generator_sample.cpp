#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeName(char first, int index, int targetLen) {
    string name(1, first);
    int value = index + 1;
    while (value > 0 && (int)name.size() < 10) {
        name.push_back(char('a' + value % 26));
        value /= 26;
    }
    while ((int)name.size() < targetLen) {
        name.push_back('a');
    }
    return name;
}

void addUniqueName(vector<string>& names, set<string>& used, char first,
                   int index, int targetLen) {
    string name = makeName(first, index, targetLen);
    int suffix = 0;
    while (!used.insert(name).second) {
        ++suffix;
        name = makeName(first, index + suffix * 101, targetLen);
    }
    names.push_back(name);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    int p;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 3);
        p = rnd.next(1, n * k);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        k = rnd.next(1, 4);
        p = n * k;
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        k = rnd.next(2, 10);
        p = rnd.next(max(1, n * k - n), n * k);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        k = rnd.next(2, 6);
        p = rnd.next(n, n * k);
    } else if (mode == 4) {
        n = rnd.next(4, 10);
        k = rnd.next(1, 10);
        p = rnd.next(1, n * k);
    } else {
        n = rnd.next(1, 10);
        k = rnd.next(1, 10);
        p = rnd.next(1, n * k);
    }

    vector<string> names;
    set<string> used;
    names.reserve(p);

    int letters;
    if (mode == 1) {
        letters = 1;
    } else if (mode == 2) {
        letters = rnd.next(2, min(5, p));
    } else if (mode == 3) {
        letters = min(26, max(1, n));
    } else {
        letters = rnd.next(1, min(26, max(1, p)));
    }

    int targetLen = rnd.next(2, 10);
    vector<char> alphabet;
    for (int i = 0; i < letters; ++i) {
        alphabet.push_back(char('a' + i));
    }
    shuffle(alphabet.begin(), alphabet.end());

    for (int i = 0; i < p; ++i) {
        char first;
        if (mode == 1) {
            first = alphabet[0];
        } else if (mode == 2) {
            first = alphabet[rnd.wnext(letters, -2)];
        } else if (mode == 3) {
            first = alphabet[i % letters];
        } else if (mode == 4) {
            first = alphabet[(i * 3 + rnd.next(0, letters - 1)) % letters];
        } else {
            first = rnd.any(alphabet);
        }
        addUniqueName(names, used, first, i + 1, targetLen);
    }

    if (mode == 3 || mode == 4) {
        int block = rnd.next(1, max(1, min(4, p)));
        for (int i = 0; i + block <= p; i += block) {
            if (rnd.next(0, 1) == 0) {
                reverse(names.begin() + i, names.begin() + i + block);
            }
        }
    } else if (mode == 5) {
        shuffle(names.begin(), names.end());
    }

    println(n, k);
    println(p);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
