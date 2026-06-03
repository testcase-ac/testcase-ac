#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomUpper() {
    return char('A' + rnd.next(26));
}

char randomConsonant() {
    static const string consonants = "BCDFGHJKLMNPQRSTVWXYZ";
    return consonants[rnd.next((int)consonants.size())];
}

char randomNonA() {
    char c = randomUpper();
    while (c == 'A') c = randomUpper();
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(4, 40);
    int m = rnd.next(4, n);
    string s(n, 'A');

    if (mode == 0) {
        m = rnd.next(4, n);
        for (char& c : s) c = randomNonA();
    } else if (mode == 1) {
        m = n;
        for (char& c : s) c = randomUpper();
        s[n - 3] = 'A';
        s[n - 2] = 'A';
        s[n - 1] = randomConsonant();
    } else if (mode == 2) {
        for (char& c : s) c = randomUpper();

        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        pos.resize(m);
        sort(pos.begin(), pos.end());

        s[pos[m - 3]] = 'A';
        s[pos[m - 2]] = 'A';
        s[pos[m - 1]] = randomConsonant();
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        m = rnd.next(4, n);
        s.assign(n, randomConsonant());
        int aCount = rnd.next(0, min(1, n));
        for (int i = 0; i < aCount; ++i) s[rnd.next(n)] = 'A';
    } else {
        for (char& c : s) {
            int bucket = rnd.next(100);
            if (bucket < 35) c = 'A';
            else if (bucket < 55) c = randomConsonant();
            else c = randomUpper();
        }
    }

    println(n, m);
    println(s);

    return 0;
}
