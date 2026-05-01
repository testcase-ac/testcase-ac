#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 20);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // total length including spaces
        int L = rnd.next(1, 30);
        // decide number of spaces (but keep at least 1 letter)
        int maxSpaces = min(L - 1, 3);
        int spaceCount = maxSpaces > 0 ? rnd.next(0, maxSpaces) : 0;
        int letterTotal = L - spaceCount;
        if (letterTotal < 1) {
            spaceCount = 0;
            letterTotal = L;
        }
        // choose scenario types
        vector<int> types;
        if (L <= 26) types.push_back(0); // all distinct letters
        types.push_back(1); // one clear max
        types.push_back(3); // all same
        if (letterTotal >= 2 && letterTotal % 2 == 0) types.push_back(2); // tie of 2
        types.push_back(4); // random
        int tp = rnd.any(types);

        vector<char> v;
        // add spaces
        for (int i = 0; i < spaceCount; i++) v.push_back(' ');

        if (tp == 0) {
            // distinct letters
            string alpha = "abcdefghijklmnopqrstuvwxyz";
            shuffle(alpha.begin(), alpha.end());
            for (int i = 0; i < letterTotal; i++)
                v.push_back(alpha[i]);
        }
        else if (tp == 1) {
            // one clear max
            char X = char('a' + rnd.next(0, 25));
            int mainCnt = rnd.next(letterTotal / 2 + 1, letterTotal);
            int rest = letterTotal - mainCnt;
            for (int i = 0; i < mainCnt; i++) v.push_back(X);
            if (rest > 0) {
                // one other letter
                char Y;
                do { Y = char('a' + rnd.next(0, 25)); } while (Y == X);
                for (int i = 0; i < rest; i++) v.push_back(Y);
            }
        }
        else if (tp == 2) {
            // tie between two letters, exactly equal and top
            char X = char('a' + rnd.next(0, 25));
            char Y;
            do { Y = char('a' + rnd.next(0, 25)); } while (Y == X);
            int cnt = rnd.next(1, letterTotal / 2);
            for (int i = 0; i < cnt; i++) v.push_back(X);
            for (int i = 0; i < cnt; i++) v.push_back(Y);
            // no other letters so rest = 0
        }
        else if (tp == 3) {
            // all same letter
            char X = char('a' + rnd.next(0, 25));
            for (int i = 0; i < letterTotal; i++) v.push_back(X);
        }
        else {
            // random distribution
            for (int i = 0; i < letterTotal; i++)
                v.push_back(char('a' + rnd.next(0, 25)));
        }

        // shuffle the positions
        shuffle(v.begin(), v.end());
        // build string
        string s;
        s.reserve(L);
        for (char c : v) s.push_back(c);
        println(s);
    }
    return 0;
}
