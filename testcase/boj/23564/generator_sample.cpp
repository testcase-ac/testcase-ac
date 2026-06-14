#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string buildRecursiveString(const vector<char>& s, const vector<int>& a) {
    string current;
    for (int i = 0; i < int(s.size()); ++i) {
        string unit = current + s[i];
        string next;
        next.reserve(a[i] * unit.size() + current.size());
        for (int j = 0; j < a[i]; ++j) {
            next += unit;
        }
        next += current;
        current = next;
    }
    return current;
}

char randomLowercase() {
    return char('a' + rnd.next(26));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<char> s;
    vector<int> a;

    if (mode == 0) {
        s.push_back(randomLowercase());
        a.push_back(rnd.next(1, 80));
    } else if (mode == 1) {
        int n = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            s.push_back(char('a' + i));
            a.push_back(rnd.next(1, 3));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            s.push_back(randomLowercase());
            a.push_back(1);
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 6);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.any(string("abc")));
            a.push_back(i % 2 == 0 ? rnd.next(1, 2) : rnd.next(2, 4));
        }
    } else {
        while (true) {
            vector<char> candidateS;
            vector<int> candidateA;
            int n = rnd.next(4, 10);
            for (int i = 0; i < n; ++i) {
                candidateS.push_back(randomLowercase());
                candidateA.push_back(rnd.next(1, 4));
            }

            string candidate = buildRecursiveString(candidateS, candidateA);
            if (candidate.size() <= 500) {
                s = candidateS;
                a = candidateA;
                break;
            }
        }
    }

    println(buildRecursiveString(s, a));
    return 0;
}
