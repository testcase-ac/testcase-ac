#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string word;
    word.reserve(len);
    for (int i = 0; i < len; ++i) {
        word += rnd.any(alphabet);
    }
    return word;
}

string shuffledCopy(string word) {
    shuffle(word.begin(), word.end());
    return word;
}

pair<string, string> makeCase() {
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        string a = randomWord(rnd.next(0, 8), "abcdefghijklmnopqrstuvwxyz");
        string b = randomWord(rnd.next(0, 8), "abcdefghijklmnopqrstuvwxyz");
        return {a, b};
    }

    if (mode == 1) {
        string a = randomWord(rnd.next(0, 18), "abcde");
        return {a, shuffledCopy(a)};
    }

    if (mode == 2) {
        string base = randomWord(rnd.next(1, 20), "abcdef");
        string a = base + randomWord(rnd.next(0, 5), "abc");
        string b = shuffledCopy(base) + randomWord(rnd.next(0, 5), "def");
        return {shuffledCopy(a), shuffledCopy(b)};
    }

    if (mode == 3) {
        int lenA = rnd.next(0, 15);
        int lenB = rnd.next(0, 15);
        return {randomWord(lenA, "abc"), randomWord(lenB, "xyz")};
    }

    if (mode == 4) {
        char ca = static_cast<char>('a' + rnd.next(0, 25));
        char cb = static_cast<char>('a' + rnd.next(0, 25));
        int lenA = rnd.next(0, 45);
        int lenB = rnd.next(0, 45);
        return {string(lenA, ca), string(lenB, cb)};
    }

    if (mode == 5) {
        string a = randomWord(rnd.next(30, 45), "pneumoltracisfv");
        string b = randomWord(rnd.next(30, 45), "pneumoltracisfv");
        return {a, b};
    }

    if (mode == 6) {
        string a = randomWord(rnd.next(1, 12), "abcdefghijklmnop");
        string b = a;
        int edits = rnd.next(1, 4);
        for (int i = 0; i < edits; ++i) {
            if (!b.empty() && rnd.next(0, 1) == 0) {
                b.erase(b.begin() + rnd.next(static_cast<int>(b.size())));
            } else if (static_cast<int>(b.size()) < 45) {
                b += rnd.any(string("qrstuvwxyz"));
            }
        }
        return {a, shuffledCopy(b)};
    }

    vector<string> words = {
        "",
        "a",
        "dog",
        "god",
        "sleep",
        "leap",
        "pneumonoultramicroscopicsilicovolcanoconiosis",
    };
    string a = rnd.any(words);
    string b = rnd.any(words);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 24);
    println(n);
    for (int i = 0; i < n; ++i) {
        auto [a, b] = makeCase();
        println(a);
        println(b);
    }

    return 0;
}
