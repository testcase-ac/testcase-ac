#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) result.push_back(rnd.any(alphabet));
    return result;
}

string randomSubsequence(const string& s, int length) {
    vector<int> positions(s.size());
    for (int i = 0; i < int(s.size()); ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    positions.resize(length);
    sort(positions.begin(), positions.end());

    string t;
    t.reserve(length);
    for (int pos : positions) t.push_back(s[pos]);
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string s;
    string t;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        s = randomString(n, "abc");
        t = randomSubsequence(s, rnd.next(1, min(n, 5)));
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        char c = char('a' + rnd.next(0, 2));
        s.assign(n, c);
        t.assign(rnd.next(1, min(n, 20)), c);
    } else if (mode == 2) {
        int n = rnd.next(5, 40);
        int m = rnd.next(1, min(n, 10));
        s = randomString(n, "abc");
        t = randomString(m, "xyz");
    } else if (mode == 3) {
        int repeats = rnd.next(2, 25);
        string block = rnd.any(vector<string>{"ab", "abc", "aab", "bca"});
        for (int i = 0; i < repeats; ++i) s += block;
        t = randomSubsequence(s, rnd.next(2, min(30, int(s.size()))));
    } else if (mode == 4) {
        int n = rnd.next(20, 120);
        string alphabet = rnd.any(vector<string>{"ab", "abcd", "abcdef"});
        s = randomString(n, alphabet);
        t = randomSubsequence(s, rnd.next(1, min(100, n)));
    } else if (mode == 5) {
        int m = rnd.next(1, 100);
        t = randomString(m, "abcde");
        s = randomString(rnd.next(0, 20), "abcde") + t + randomString(rnd.next(0, 20), "abcde");
    } else {
        int n = rnd.next(150, 450);
        s = randomString(n, "abcdefghijklmnopqrstuvwxyz");
        t = randomSubsequence(s, rnd.next(50, 100));
    }

    println(s);
    println(t);
    return 0;
}
