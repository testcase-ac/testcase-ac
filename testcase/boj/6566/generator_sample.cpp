#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledWord(string letters) {
    shuffle(letters.begin(), letters.end());
    return letters;
}

string makeUniqueWord(int index, int length) {
    string word;
    for (int i = 0; i < length; ++i) {
        word += char('a' + (index + 3 * i) % 26);
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> bases = {
        "aet", "abel", "acer", "aegln", "aemnort", "aelp", "arst", "eilnst",
        "aacc", "aabb", "abcde", "aabce", "ddeor", "eerst"
    };

    shuffle(bases.begin(), bases.end());

    vector<string> words;
    int mode = rnd.next(0, 4);
    int groupCount = rnd.next(1, 8);
    if (mode == 1) {
        groupCount = rnd.next(5, 9);
    } else if (mode == 2) {
        groupCount = rnd.next(2, 5);
    }

    for (int g = 0; g < groupCount; ++g) {
        string base = bases[g % (int)bases.size()];
        int groupSize;
        if (mode == 0) {
            groupSize = rnd.next(1, 6);
        } else if (mode == 1) {
            groupSize = rnd.next(2, 5);
        } else if (mode == 2) {
            groupSize = (g % 2 == 0 ? 5 : 4);
        } else if (mode == 3) {
            groupSize = rnd.next(1, 3);
        } else {
            groupSize = rnd.next(3, 8);
        }

        for (int i = 0; i < groupSize; ++i) {
            if (rnd.next(0, 5) == 0 && !words.empty()) {
                words.push_back(words.back());
            } else {
                words.push_back(shuffledWord(base));
            }
        }
    }

    int singletonCount = rnd.next(0, mode == 3 ? 12 : 6);
    for (int i = 0; i < singletonCount; ++i) {
        words.push_back(makeUniqueWord(i + 20 * mode, rnd.next(1, 9)));
    }

    shuffle(words.begin(), words.end());
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
