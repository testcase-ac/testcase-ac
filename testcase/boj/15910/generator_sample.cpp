#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string similarBanana() {
    int extraB = rnd.next(0, 5);
    int extraNA = rnd.next(0, 6);
    string s(extraB + 1, 'B');
    s += "ANANA";
    for (int i = 0; i < extraNA; ++i) s += "NA";
    return s;
}

void mutate(string& s, int changes) {
    const string alphabet = "BAN";
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next((int)s.size());
        char c = rnd.any(alphabet);
        if (c == s[pos]) c = alphabet[(alphabet.find(c) + 1) % alphabet.size()];
        s[pos] = c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "BAN";
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int parts = rnd.next(1, 5);
        for (int i = 0; i < parts; ++i) s += similarBanana();
    } else if (mode == 1) {
        int parts = rnd.next(1, 4);
        for (int i = 0; i < parts; ++i) s += similarBanana();
        mutate(s, rnd.next(1, max(1, min(8, (int)s.size() / 2))));
    } else if (mode == 2) {
        int n = rnd.next(6, 80);
        int maxChar = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) s += alphabet[rnd.next(maxChar)];
    } else if (mode == 3) {
        vector<string> blocks = {"BANANA", "BBANANA", "BANANANA", "NA", "BA", "AN"};
        int n = rnd.next(6, 90);
        while ((int)s.size() < n) s += rnd.any(blocks);
        s.resize(n);
    } else if (mode == 4) {
        int n = rnd.next(6, 100);
        char c = rnd.any(alphabet);
        s.assign(n, c);
        mutate(s, rnd.next(0, min(6, n)));
    } else {
        int n = rnd.next(6, 120);
        string pattern = rnd.any(vector<string>{"BANANA", "BANANANA", "BBANANA", "BNANAA"});
        while ((int)s.size() < n) s += pattern;
        s.resize(n);
        mutate(s, rnd.next(0, min(10, n / 3)));
    }

    println(s);
    return 0;
}
