#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomLowercase(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

void insertAtRandomPositions(string& s, const vector<string>& parts) {
    for (const string& part : parts) {
        int pos = rnd.next(0, static_cast<int>(s.size()));
        s.insert(pos, part);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 80);
        string alphabet = rnd.next(0, 3) == 0 ? "skep" : "abcdefghijklmnopqrstuvwxyz";
        s = randomLowercase(n, alphabet);
    } else if (mode == 1) {
        int blocks = rnd.next(1, 18);
        string gapAlphabet = rnd.next(0, 1) ? "fanclub" : "abcxyz";
        for (int i = 0; i < blocks; ++i) {
            if (rnd.next(0, 2) == 0) {
                s += randomLowercase(rnd.next(0, 4), gapAlphabet);
            }
            s += "skeep";
        }
        s += randomLowercase(rnd.next(0, 8), gapAlphabet);
    } else if (mode == 2) {
        int blocks = rnd.next(1, 15);
        string prefix = rnd.any(vector<string>{"", "s", "sk", "ske", "skee", "ss"});
        s = prefix;
        for (int i = 0; i < blocks; ++i) {
            s += "skeep";
            if (rnd.next(0, 3) == 0) {
                s += rnd.any(string("kep"));
            }
        }
    } else if (mode == 3) {
        int depth = rnd.next(1, 20);
        string prefix = rnd.any(vector<string>{"a", "k", "e", "ss", "abc", "xyz"});
        s = prefix;
        for (int i = 0; i < depth; ++i) {
            s += "skeep";
            if (rnd.next(0, 4) == 0) {
                s += randomLowercase(rnd.next(1, 3), "kep");
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 120);
        s = randomLowercase(n, "abcdefghijklmnopqrstuvwxyz");
        int occurrences = rnd.next(1, 10);
        vector<string> parts;
        for (int i = 0; i < occurrences; ++i) {
            parts.push_back(rnd.any(vector<string>{"skeep", "sskeep", "skee", "keep", "skeepp"}));
        }
        insertAtRandomPositions(s, parts);
    } else {
        int groups = rnd.next(1, 10);
        for (int i = 0; i < groups; ++i) {
            s += rnd.any(vector<string>{"skeep", "sskeep", "sskeepee", "abcxyzskeepp", "skeepfanclub"});
            if (rnd.next(0, 2) == 0) {
                s += randomLowercase(rnd.next(0, 5), "skepabc");
            }
        }
    }

    println(static_cast<int>(s.size()));
    println(s);
    return 0;
}
