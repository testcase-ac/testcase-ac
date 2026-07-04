#include "testlib.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

string makeName(int index, int minLen, int maxLen, bool preferLastUpper) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.push_back(char('A' + (index % 26)));

    for (int i = 1; i <= len - 2; ++i) {
        int value = index;
        for (int step = 0; step < i; ++step) value /= 26;
        s.push_back(char('a' + ((value + rnd.next(0, 25)) % 26)));
    }

    if (preferLastUpper || rnd.next(0, 4) == 0) {
        s.push_back(char('A' + rnd.next(0, 25)));
    } else {
        s.push_back(char('a' + rnd.next(0, 25)));
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int N;
    int M;
    int minLen = 2;
    int maxLen = 12;
    bool preferLastUpper = false;

    if (mode == 0) {
        N = rnd.next(2, 8);
        M = rnd.next(2, 16);
    } else if (mode == 1) {
        N = rnd.next(9, 30);
        M = rnd.next(20, 70);
    } else if (mode == 2) {
        N = rnd.next(5, 18);
        M = rnd.next(15, 50);
        minLen = 15;
        maxLen = 20;
    } else {
        N = rnd.next(10, 40);
        M = rnd.next(20, 80);
        minLen = 2;
        maxLen = 20;
        preferLastUpper = true;
    }

    vector<string> names;
    set<string> seen;
    for (int i = 0; i < N; ++i) {
        string name;
        do {
            name = makeName(i + seen.size() * 17 + rnd.next(0, 1000), minLen, maxLen, preferLastUpper);
        } while (!seen.insert(name).second);
        names.push_back(name);
    }

    println(N, M);
    for (const string& name : names) {
        println(name);
    }

    for (int i = 0; i < M; ++i) {
        if (rnd.next(0, 99) < 45) {
            println(rnd.next(1, N));
        } else {
            println(names[rnd.next(0, N - 1)]);
        }
    }

    return 0;
}
