#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string quoted(const string& value) {
    return "\"" + value + "\"";
}

string randomWord(const string& alphabet, int minLength, int maxLength) {
    int length = rnd.next(minLength, maxLength);
    string result;
    for (int i = 0; i < length; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

void addRule(vector<pair<string, string>>& rules, const string& from, const string& to) {
    rules.push_back({from, to});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string lower = "abcxyz";
    const string mixed = "ABCDabcdxy";
    int mode = rnd.next(0, 5);

    string initial;
    vector<pair<string, string>> rules;

    if (mode == 0) {
        initial = randomWord("ABCD", 2, 6);
        int symbols = rnd.next(2, 4);
        for (int i = 0; i < symbols; ++i) {
            string from(1, char('A' + i));
            int choices = rnd.next(1, 3);
            for (int j = 0; j < choices; ++j) {
                addRule(rules, from, randomWord(lower, 0, 3));
            }
        }
    } else if (mode == 1) {
        initial = randomWord("AaBb", 4, 8);
        addRule(rules, "A", "");
        addRule(rules, "B", "");
        addRule(rules, "a", randomWord("xy", 1, 2));
        addRule(rules, "b", randomWord("xy", 0, 2));
        if (rnd.next(0, 1)) addRule(rules, "Aa", randomWord("mn", 0, 3));
    } else if (mode == 2) {
        initial = randomWord("abc", 3, 7);
        int chainLength = rnd.next(3, 6);
        for (int i = 0; i < chainLength; ++i) {
            string from(1, char('a' + i));
            string to(1, char('a' + i + 1));
            addRule(rules, from, to);
        }
        addRule(rules, string(1, char('a' + chainLength)), randomWord("uv", 0, 2));
    } else if (mode == 3) {
        initial = rnd.next(0, 1) ? "" : randomWord(mixed, 1, 10);
        int ruleCount = rnd.next(0, 8);
        for (int i = 0; i < ruleCount; ++i) {
            addRule(rules, randomWord(mixed, 1, 3), randomWord(mixed, 0, 3));
        }
    } else if (mode == 4) {
        initial = randomWord("S", 1, 3);
        addRule(rules, "S", "SS");
        addRule(rules, "S", "a");
        if (rnd.next(0, 1)) addRule(rules, "SS", "S");
    } else {
        initial = randomWord("ABCabc", 4, 10);
        int ruleCount = rnd.next(10, 25);
        for (int i = 0; i < ruleCount; ++i) {
            string from = randomWord(mixed, 1, rnd.next(1, 4));
            string to = randomWord(mixed, 0, rnd.next(0, 4));
            addRule(rules, from, to);
        }
    }

    shuffle(rules.begin(), rules.end());

    println(quoted(initial));
    for (const auto& rule : rules) {
        println(quoted(rule.first) + "->" + quoted(rule.second));
    }

    return 0;
}
