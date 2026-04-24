#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool isAnagram(const string &a, const string &b) {
    if (a.size() != b.size()) return false;
    int cnt[26] = {0};
    for (char c : a) cnt[c - 'a']++;
    for (char c : b) cnt[c - 'a']--;
    for (int i = 0; i < 26; i++) if (cnt[i] != 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        bool ana = rnd.next(0, 1) == 1;
        if (ana) {
            int len = rnd.next(1, 10);
            string s, t;
            for (int j = 0; j < len; j++)
                s += char('a' + rnd.next(0, 25));
            t = s;
            shuffle(t.begin(), t.end());
            println(s, t);
        } else {
            // generate a non-anagram pair
            int l1 = rnd.next(1, 10), l2 = rnd.next(1, 10);
            string s, t;
            for (int j = 0; j < l1; j++)
                s += char('a' + rnd.next(0, 25));
            do {
                t.clear();
                for (int j = 0; j < l2; j++)
                    t += char('a' + rnd.next(0, 25));
            } while (isAnagram(s, t));
            println(s, t);
        }
    }

    return 0;
}
