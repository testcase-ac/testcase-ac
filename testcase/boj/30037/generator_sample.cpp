#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

string capitalize(string s) {
    s[0] = char(toupper(static_cast<unsigned char>(s[0])));
    return s;
}

string punctuated(string s) {
    static const string punct = "!?,";
    if (rnd.next(2)) {
        s += punct[rnd.next(int(punct.size()))];
    }
    return s;
}

string word() {
    static const vector<string> words = {
        "aheui", "Artichoke", "language", "report", "culture", "summary",
        "program", "student", "course", "assignment", "Korean", "alpha",
        "Beta", "camelCase", "ofKorea", "koRea", "korea", "Of"
    };

    string result = rnd.any(words);
    if (rnd.next(4) == 0) {
        result = capitalize(result);
    }
    return result;
}

string maybePunctuatedWord() {
    return punctuated(word());
}

void appendFiller(vector<string>& tokens, int count) {
    for (int i = 0; i < count; ++i) {
        tokens.push_back(maybePunctuatedWord());
    }
}

vector<string> makeSentence() {
    vector<string> tokens;
    int mode = rnd.next(8);

    if (mode == 0) {
        appendFiller(tokens, rnd.next(0, 3));
        tokens.push_back("Korea");
        tokens.push_back(word());
        appendFiller(tokens, rnd.next(0, 3));
    } else if (mode == 1) {
        appendFiller(tokens, rnd.next(0, 2));
        tokens.push_back(word());
        tokens.push_back("of");
        tokens.push_back("Korea");
        appendFiller(tokens, rnd.next(0, 2));
    } else if (mode == 2) {
        tokens.push_back("Korea");
        tokens.push_back("Korea");
        tokens.push_back(word());
        if (rnd.next(2)) {
            tokens.push_back("of");
            tokens.push_back("Korea");
        }
    } else if (mode == 3) {
        tokens.push_back(punctuated("Korea"));
        tokens.push_back(word());
        tokens.push_back(punctuated(word()));
        tokens.push_back("of");
        tokens.push_back(rnd.next(2) ? punctuated("Korea") : string("korea"));
    } else if (mode == 4) {
        tokens.push_back("of");
        tokens.push_back("Korea");
        tokens.push_back(punctuated(word()));
        tokens.push_back("of");
        tokens.push_back("Korea");
    } else if (mode == 5) {
        appendFiller(tokens, rnd.next(1, 4));
        tokens.push_back("of");
        tokens.push_back("Korea");
        tokens.push_back("Korea");
        tokens.push_back(word());
    } else if (mode == 6) {
        int len = rnd.next(3, 10);
        for (int i = 0; i < len; ++i) {
            int choice = rnd.next(6);
            if (choice == 0) tokens.push_back("Korea");
            else if (choice == 1) tokens.push_back("of");
            else tokens.push_back(maybePunctuatedWord());
        }
    } else {
        appendFiller(tokens, rnd.next(1, 12));
    }

    if (tokens.empty()) {
        tokens.push_back(word());
    }

    if (!tokens.back().empty()) {
        char last = tokens.back().back();
        if (last == '!' || last == '?' || last == ',') {
            tokens.back().pop_back();
        }
    }
    tokens.back() += ".";
    return tokens;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    vector<vector<string>> sentences;
    int totalWords = 0;

    for (int i = 0; i < n; ++i) {
        vector<string> sentence = makeSentence();
        totalWords += int(sentence.size());
        sentences.push_back(sentence);
    }

    println(n);
    for (const auto& sentence : sentences) {
        for (int i = 0; i < int(sentence.size()); ++i) {
            if (i) printf(" ");
            printf("%s", sentence[i].c_str());
        }
        printf("\n");
    }

    ensure(totalWords <= 5000);
    return 0;
}
