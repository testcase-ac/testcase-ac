#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string W, S;
    int type = rnd.next(0, 6);

    if (type == 0) {
        // Very small W and S
        int lenW = rnd.next(1, 3);
        int lenS = rnd.next(1, 3);
        W.clear();
        S.clear();
        for (int i = 0; i < lenW; i++) W.push_back(char('A' + rnd.next(0, 25)));
        for (int i = 0; i < lenS; i++) S.push_back(char('A' + rnd.next(0, 25)));
    } else if (type == 1) {
        // Medium random
        int lenW = rnd.next(5, 20);
        int lenS = rnd.next(10, 40);
        W.clear();
        S.clear();
        for (int i = 0; i < lenW; i++) W.push_back(char('A' + rnd.next(0, 25)));
        for (int i = 0; i < lenS; i++) S.push_back(char('A' + rnd.next(0, 25)));
    } else if (type == 2) {
        // W with all same letter
        char c = char('A' + rnd.next(0, 25));
        int lenW = rnd.next(5, 20);
        W.assign(lenW, c);

        int lenS = rnd.next(10, 25);
        S.clear();
        for (int i = 0; i < lenS; i++) S.push_back(char('A' + rnd.next(0, 25)));
    } else if (type == 3) {
        // W with many distinct letters (max coverage)
        vector<char> letters(26);
        for (int i = 0; i < 26; i++) letters[i] = char('A' + i);
        shuffle(letters.begin(), letters.end());
        int lenW = rnd.next(10, 20);
        W.clear();
        for (int i = 0; i < lenW; i++) W.push_back(letters[i]);

        int lenS = rnd.next(30, 80);
        S.clear();
        for (int i = 0; i < lenS; i++) S.push_back(char('A' + rnd.next(0, 25)));
    } else if (type == 4) {
        // Include the sample keyword, maybe with sample sentence
        W = "THEFIFTHSMUPC";
        if (rnd.next(0, 1) == 0) {
            S = "GOODLUCK";
        } else {
            int lenS = rnd.next(8, 25);
            S.clear();
            for (int i = 0; i < lenS; i++) S.push_back(char('A' + rnd.next(0, 25)));
        }
    } else if (type == 5) {
        // Alphabet or reversed alphabet slice for W, and patterned S
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string ralpha = alpha;
        reverse(ralpha.begin(), ralpha.end());

        int lenW = rnd.next(5, 20);
        if (rnd.next(0, 1) == 0) {
            int pos = rnd.next(0, 26 - lenW);
            W = alpha.substr(pos, lenW);
        } else {
            int pos = rnd.next(0, 26 - lenW);
            W = ralpha.substr(pos, lenW);
        }

        // S as ascending or descending alphabet, maybe truncated
        int maxLen = rnd.next(5, 26);
        if (rnd.next(0, 1) == 0) {
            S = alpha.substr(0, maxLen);
        } else {
            S = ralpha.substr(0, maxLen);
        }
    } else {
        // type == 6: S with strong patterns and repetitions
        int lenW = rnd.next(5, 10);
        W.clear();
        for (int i = 0; i < lenW; i++) W.push_back(char('A' + rnd.next(0, 25)));

        vector<string> segments = {
            "A",
            "Z",
            "AAAAAAAAAA",
            "ZZZZZZZZZZ",
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            "ZYXWVUTSRQPONMLKJIHGFEDCBA"
        };

        int targetLen = rnd.next(20, 80);
        S.clear();
        while ((int)S.size() < targetLen) {
            string seg = rnd.any(segments);
            if ((int)S.size() + (int)seg.size() > targetLen) {
                seg = seg.substr(0, targetLen - S.size());
            }
            S += seg;
        }
    }

    println(W);
    println(S);

    return 0;
}
