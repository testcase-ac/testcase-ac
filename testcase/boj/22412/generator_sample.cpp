#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string expandOnce(const string& s, char target) {
    string result;
    for (char c : s) {
        if (c == target) {
            result += "ABC";
        } else {
            result += c;
        }
    }
    return result;
}

string randomString(int length, const vector<int>& weights) {
    const string alphabet = "ABC";
    int total = weights[0] + weights[1] + weights[2];
    string result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        int pick = rnd.next(1, total);
        int prefix = 0;
        for (int j = 0; j < 3; ++j) {
            prefix += weights[j];
            if (pick <= prefix) {
                result += alphabet[j];
                break;
            }
        }
    }

    return result;
}

string reachableString() {
    string s = "ABC";
    int steps = rnd.next(0, 6);

    for (int step = 0; step < steps; ++step) {
        vector<char> present;
        for (char c : string("ABC")) {
            if (s.find(c) != string::npos) {
                present.push_back(c);
            }
        }

        string next = expandOnce(s, rnd.any(present));
        if (static_cast<int>(next.size()) > 5000) {
            break;
        }
        s = next;
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int length = rnd.next(1, 30);
        s = randomString(length, {1, 1, 1});
    } else if (mode == 1) {
        vector<int> weights = {rnd.next(1, 8), rnd.next(1, 8), rnd.next(1, 8)};
        int length = rnd.next(1, 80);
        s = randomString(length, weights);
    } else if (mode == 2) {
        s = reachableString();
    } else if (mode == 3) {
        s = reachableString();
        int edits = rnd.next(1, 3);
        for (int i = 0; i < edits; ++i) {
            int action = rnd.next(0, 2);
            if (action == 0 && !s.empty()) {
                int pos = rnd.next(0, static_cast<int>(s.size()) - 1);
                s[pos] = rnd.any(string("ABC"));
            } else if (action == 1 && static_cast<int>(s.size()) < 5000) {
                int pos = rnd.next(0, static_cast<int>(s.size()));
                s.insert(s.begin() + pos, rnd.any(string("ABC")));
            } else if (s.size() > 1) {
                int pos = rnd.next(0, static_cast<int>(s.size()) - 1);
                s.erase(s.begin() + pos);
            }
        }
    } else if (mode == 4) {
        int a = rnd.next(0, 20);
        int b = rnd.next(0, 20);
        int c = rnd.next(0, 20);
        if (a + b + c == 0) {
            a = 1;
        }
        s = string(a, 'A') + string(b, 'B') + string(c, 'C');
    } else {
        int blocks = rnd.next(1, 18);
        for (int i = 0; i < blocks; ++i) {
            char c = rnd.any(string("ABC"));
            int count = rnd.next(1, 8);
            s += string(count, c);
        }
    }

    println(s);
    return 0;
}
