#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeHandle(char initial, int id) {
    string body;
    do {
        body.push_back(char('A' + id % 26));
        id /= 26;
    } while (id > 0);
    reverse(body.begin(), body.end());
    string handle(1, initial);
    handle += body;
    return handle.substr(0, 10);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;
    if (mode == 0) {
        s = string(3, char('A' + rnd.next(26)));
    } else if (mode == 1) {
        char a = char('A' + rnd.next(26));
        char b = char('A' + rnd.next(25));
        if (b >= a) ++b;
        s = string() + a + a + b;
        shuffle(s.begin(), s.end());
    } else {
        vector<char> letters;
        for (char c = 'A'; c <= 'Z'; ++c) letters.push_back(c);
        shuffle(letters.begin(), letters.end());
        s = string() + letters[0] + letters[1] + letters[2];
        shuffle(s.begin(), s.end());
    }

    int required[26] = {};
    for (char c : s) ++required[c - 'A'];

    int target[26] = {};
    int profile = rnd.next(0, 4);
    for (int i = 0; i < 26; ++i) {
        if (required[i] == 0) continue;
        if (profile == 0) {
            target[i] = max(0, required[i] - 1);
        } else if (profile == 1) {
            target[i] = required[i];
        } else {
            target[i] = required[i] + rnd.next(1, 8);
        }
    }

    int n = 0;
    for (int x : target) n += x;
    n += rnd.next(0, 18);
    n = max(n, 3);

    vector<int> initials;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < target[i]; ++j) initials.push_back(i);
    }
    while ((int)initials.size() < n) {
        initials.push_back(rnd.next(26));
    }
    shuffle(initials.begin(), initials.end());

    set<string> used;
    vector<string> handles;
    int serial[26] = {};
    for (int x : initials) {
        char initial = char('A' + x);
        string handle;
        do {
            handle = makeHandle(initial, serial[x]++);
        } while (!used.insert(handle).second);
        handles.push_back(handle);
    }

    println(s);
    println((int)handles.size());
    for (const string& handle : handles) {
        println(handle);
    }

    return 0;
}
