#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

string alternatingString(int n) {
    string s;
    s.reserve(n);
    char first = rnd.next(2) == 0 ? 'C' : 'J';
    for (int i = 0; i < n; ++i) {
        char ch = (i % 2 == 0) ? first : (first == 'C' ? 'J' : 'C');
        if (rnd.next(5) == 0) ch = '?';
        s += ch;
    }
    return s;
}

string runString(int n) {
    string s;
    while ((int)s.size() < n) {
        char ch = rnd.any(string("CJ?"));
        int len = rnd.next(1, min(8, n - (int)s.size()));
        s.append(len, ch);
    }
    return s;
}

pair<int, int> chooseCosts() {
    int mode = rnd.next(6);
    if (mode == 0) return {rnd.any(vector<int>{-100, -1, 0, 1, 100}), rnd.next(-100, 100)};
    if (mode == 1) return {rnd.next(-100, 100), rnd.any(vector<int>{-100, -1, 0, 1, 100})};
    if (mode == 2) return {rnd.next(1, 100), rnd.next(1, 100)};
    if (mode == 3) return {rnd.next(-100, -1), rnd.next(-100, -1)};
    if (mode == 4) return {rnd.next(-100, -1), rnd.next(1, 100)};
    return {rnd.next(1, 100), rnd.next(-100, -1)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        auto [x, y] = chooseCosts();

        int lengthMode = rnd.next(5);
        int n;
        if (lengthMode == 0) n = 1;
        else if (lengthMode == 1) n = rnd.next(2, 5);
        else if (lengthMode == 2) n = rnd.next(6, 15);
        else if (lengthMode == 3) n = rnd.next(16, 40);
        else n = rnd.next(80, 160);

        string s;
        int pattern = rnd.next(6);
        if (pattern == 0) s = string(n, '?');
        else if (pattern == 1) s = randomString(n, "CJ");
        else if (pattern == 2) s = randomString(n, "CJ?");
        else if (pattern == 3) s = alternatingString(n);
        else if (pattern == 4) s = runString(n);
        else {
            s = randomString(n, "???CJ");
            s[0] = rnd.any(string("CJ"));
            s[n - 1] = rnd.any(string("CJ"));
        }

        println(x, y, s);
    }

    return 0;
}
