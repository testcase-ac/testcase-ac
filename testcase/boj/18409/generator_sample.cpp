#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string vowels = "aiueo";
    const string consonants = "bcdfghjklmnpqrstvwxyz";
    const string lowercase = "abcdefghijklmnopqrstuvwxyz";

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 50;
    } else {
        n = rnd.next(2, 30);
    }

    string s;
    s.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            s += rnd.any(vowels);
        } else if (mode == 3) {
            s += rnd.any(consonants);
        } else if (mode == 4) {
            s += (i % 2 == 0 ? rnd.any(vowels) : rnd.any(consonants));
        } else if (mode == 5) {
            s += (rnd.next(0, 99) < 70 ? rnd.any(vowels) : rnd.any(consonants));
        } else {
            s += rnd.any(lowercase);
        }
    }

    println(n);
    println(s);

    return 0;
}
