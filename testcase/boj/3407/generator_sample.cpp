#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const vector<string> oneLetter = {"h", "b", "c", "n", "o", "f", "p", "s", "k", "v", "y", "i", "w", "u"};

const vector<string> twoLetter = {
    "ba", "ca", "ga", "la", "na", "pa", "ra", "ta", "db", "nb", "pb", "rb", "sb", "tb", "yb", "ac",
    "sc", "tc", "cd", "gd", "md", "nd", "pd", "be", "ce", "fe", "ge", "he", "ne", "re", "se", "te",
    "xe", "cf", "hf", "rf", "ag", "hg", "mg", "rg", "sg", "bh", "rh", "th", "bi", "li", "ni", "si",
    "ti", "bk", "al", "cl", "fl", "tl", "am", "cm", "fm", "pm", "sm", "tm", "cn", "in", "mn", "rn",
    "sn", "zn", "co", "ho", "mo", "no", "po", "np", "ar", "br", "cr", "er", "fr", "ir", "kr", "lr",
    "pr", "sr", "zr", "as", "cs", "ds", "es", "hs", "os", "at", "mt", "pt", "au", "cu", "eu", "lu",
    "pu", "ru", "lv", "dy"};

string elementWord(int parts) {
    string word;
    for (int i = 0; i < parts; ++i) {
        if (rnd.next(100) < 35) {
            word += rnd.any(oneLetter);
        } else {
            word += rnd.any(twoLetter);
        }
    }
    return word;
}

string randomWord(int length) {
    string word;
    for (int i = 0; i < length; ++i) {
        if (rnd.next(100) < 30) {
            word += rnd.any(string("aeiou"));
        } else {
            word += static_cast<char>('a' + rnd.next(26));
        }
    }
    return word;
}

string biasedNoWord() {
    vector<string> fragments = {"zz", "jq", "qx", "xj", "jj", "vv", "xx", "zq"};
    string word = randomWord(rnd.next(1, 10));
    int insertAt = rnd.next(static_cast<int>(word.size()) + 1);
    word.insert(insertAt, rnd.any(fragments));
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 30);
    vector<string> words;
    words.reserve(t);

    vector<string> anchors = {"international", "collegiate", "programming", "contest", "h", "z", "ra"};
    shuffle(anchors.begin(), anchors.end());
    for (string word : anchors) {
        if (static_cast<int>(words.size()) < t && rnd.next(100) < 70) {
            words.push_back(word);
        }
    }

    while (static_cast<int>(words.size()) < t) {
        int mode = rnd.next(100);
        if (mode < 45) {
            words.push_back(elementWord(rnd.next(1, 12)));
        } else if (mode < 75) {
            string word = elementWord(rnd.next(1, 8));
            if (!word.empty()) {
                word[rnd.next(static_cast<int>(word.size()))] = rnd.any(string("jqxz"));
            }
            words.push_back(word);
        } else {
            words.push_back(biasedNoWord());
        }
    }

    shuffle(words.begin(), words.end());

    println(t);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
