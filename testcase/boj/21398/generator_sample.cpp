#include "testlib.h"

#include <string>

using namespace std;

char pick(const string& chars) {
    return chars[rnd.next((int)chars.size())];
}

string randomString(int n, const string& chars) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += pick(chars);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string albert = "ALBERT";
    const string alice = "ALICE";
    const string shared = "ALE";
    const string aliceOnly = "IC";
    const string albertOnly = "BRT";
    const string neutral = "DFGHJKMNOPQSUVWXYZ";
    const string all = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int t = rnd.next(8, 30);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(8);
        int n = rnd.next(1, 24);
        string s;

        if (mode == 0) {
            s = randomString(n, all);
        } else if (mode == 1) {
            s = randomString(n, albert);
        } else if (mode == 2) {
            s = randomString(n, alice);
        } else if (mode == 3) {
            s = randomString(n, neutral);
        } else if (mode == 4) {
            s = randomString(n, shared + aliceOnly + albertOnly);
        } else if (mode == 5) {
            int inner = rnd.next(0, 20);
            s += pick(albertOnly + shared);
            s += randomString(inner, neutral + aliceOnly);
            s += pick(neutral);
        } else if (mode == 6) {
            int inner = rnd.next(0, 20);
            s += pick(neutral);
            s += randomString(inner, neutral + shared);
            s += pick(albertOnly + shared);
        } else {
            n = rnd.next(25, 60);
            s = randomString(n, all);
            if (rnd.next(2) == 0) {
                for (int i = 0; i < n / 2; ++i) {
                    s[n - 1 - i] = s[i];
                }
            }
        }

        println(s);
    }

    return 0;
}
