#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int kMaxWordLength = 200;

string randomAtom() {
    const string atoms = "{},";
    return string(1, atoms[rnd.next(0, static_cast<int>(atoms.size()) - 1)]);
}

string makeSet(int depth, int budget);

string makeElement(int depth, int budget) {
    if (budget <= 1 || depth <= 0 || rnd.next(100) < 45) {
        return randomAtom();
    }
    return makeSet(depth - 1, budget);
}

string makeSet(int depth, int budget) {
    if (budget <= 2 || depth <= 0 || rnd.next(100) < 20) {
        return "{}";
    }

    string result = "{";
    int remaining = budget - 2;
    int elementCount = rnd.next(1, min(6, max(1, remaining)));
    for (int i = 0; i < elementCount && remaining > 0; ++i) {
        if (i > 0) {
            result += ",";
            --remaining;
        }
        int elementBudget = max(1, remaining / (elementCount - i));
        string element = makeElement(depth - 1, elementBudget);
        if (static_cast<int>(element.size()) > remaining) {
            element = randomAtom();
        }
        result += element;
        remaining -= static_cast<int>(element.size());
    }
    result += "}";
    return result;
}

string mutateWord(string word) {
    const string chars = "{},";
    int mode = rnd.next(0, 3);
    if (mode == 0 && word.size() > 1) {
        int pos = rnd.next(0, static_cast<int>(word.size()) - 1);
        word.erase(word.begin() + pos);
    } else if (mode == 1 && static_cast<int>(word.size()) < kMaxWordLength) {
        int pos = rnd.next(0, static_cast<int>(word.size()));
        word.insert(word.begin() + pos, chars[rnd.next(0, 2)]);
    } else if (mode == 2) {
        int pos = rnd.next(0, static_cast<int>(word.size()) - 1);
        word[pos] = chars[rnd.next(0, 2)];
    } else if (word.size() > 1) {
        int pos = rnd.next(0, static_cast<int>(word.size()) - 2);
        swap(word[pos], word[pos + 1]);
    }
    return word.empty() ? randomAtom() : word;
}

string randomWord() {
    int length = rnd.next(1, 80);
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) {
        word += randomAtom();
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> words = {
        "{}",
        "{{}}",
        "{{}},{,}}",
        "{,,}",
        "{",
        "}",
        ",",
    };

    int extraCount = rnd.next(8, 24);
    for (int i = 0; i < extraCount; ++i) {
        int mode = rnd.next(0, 4);
        if (mode <= 1) {
            words.push_back(makeSet(rnd.next(2, 7), rnd.next(4, 90)));
        } else if (mode == 2) {
            words.push_back(mutateWord(makeSet(rnd.next(2, 7), rnd.next(4, 90))));
        } else {
            words.push_back(randomWord());
        }
    }

    shuffle(words.begin(), words.end());
    println(static_cast<int>(words.size()));
    for (const string& word : words) {
        println(word.substr(0, kMaxWordLength));
    }

    return 0;
}
