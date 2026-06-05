#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string randomFromAlphabet(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 50);
    string s;

    if (mode == 0) {
        s.assign(n, char('a' + rnd.next(0, 25)));
    } else if (mode == 1) {
        int kinds = rnd.next(1, 8);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        alphabet.resize(kinds);
        s = randomFromAlphabet(n, alphabet);
        if (rnd.next(0, 1)) sort(s.begin(), s.end());
    } else if (mode == 2) {
        int kinds = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, kinds - 1);
            s += char('a' + x);
        }
        sort(s.begin(), s.end(), greater<char>());
    } else if (mode == 3) {
        int kinds = rnd.next(2, 6);
        vector<char> letters;
        for (int i = 0; i < kinds; ++i) letters.push_back(char('a' + rnd.next(0, 25)));
        while ((int)s.size() < n) {
            char c = rnd.any(letters);
            int run = rnd.next(1, min(8, n - (int)s.size()));
            s.append(run, c);
        }
    } else if (mode == 4) {
        char a = char('a' + rnd.next(0, 25));
        char b = char('a' + rnd.next(0, 25));
        while (b == a) b = char('a' + rnd.next(0, 25));
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 5) {
        int kinds = rnd.next(2, 26);
        vector<char> letters;
        for (int i = 0; i < kinds; ++i) letters.push_back(char('a' + i));
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < n; ++i) s += letters[i % kinds];
        shuffle(s.begin(), s.end());
    } else if (mode == 6) {
        n = rnd.next(35, 50);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        s = randomFromAlphabet(n, alphabet);
    } else {
        n = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) s += char('a' + rnd.next(0, 3));
            if (bucket == 1) s += char('m' + rnd.next(0, 2));
            if (bucket == 2) s += char('x' + rnd.next(0, 2));
        }
    }

    println(s);
    return 0;
}
