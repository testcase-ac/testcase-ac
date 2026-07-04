#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string decimal(int value) {
    return to_string(value);
}

static string zeroPaddedTerm(int value, int width) {
    string text = decimal(value);
    if ((int)text.size() < width) {
        text = string(width - text.size(), '0') + text;
    }
    return text;
}

static vector<int> splitPositiveSum(int sum, int parts) {
    vector<int> values(parts, 1);
    int remaining = sum - parts;
    for (int i = 0; i < parts && remaining > 0; ++i) {
        int add = (i == parts - 1) ? remaining : rnd.next(0, remaining);
        values[i] += add;
        remaining -= add;
    }
    shuffle(values.begin(), values.end());
    return values;
}

static string joinTerms(const vector<string>& terms) {
    string result;
    for (const string& term : terms) {
        result += term;
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int target = rnd.next(2, 300);
    vector<string> terms;

    if (mode == 0) {
        int parts = rnd.next(2, min(target, 8));
        for (int value : splitPositiveSum(target, parts)) {
            terms.push_back(decimal(value));
        }
    } else if (mode == 1) {
        target = rnd.next(2, 80);
        int parts = rnd.next(2, min(target, 6));
        for (int value : splitPositiveSum(target, parts)) {
            terms.push_back(zeroPaddedTerm(value, rnd.next((int)decimal(value).size(), 4)));
        }
    } else if (mode == 2) {
        target = rnd.next(1, 30);
        terms.push_back(decimal(target));
        int zeroBlocks = rnd.next(1, 12);
        for (int i = 0; i < zeroBlocks; ++i) {
            terms.push_back(string(rnd.next(1, 5), '0'));
        }
        shuffle(terms.begin() + 1, terms.end());
    } else if (mode == 3) {
        target = rnd.next(4500, 5000);
        int parts = rnd.next(2, 10);
        for (int value : splitPositiveSum(target, parts)) {
            terms.push_back(decimal(value));
        }
    } else if (mode == 4) {
        target = rnd.next(20, 200);
        int parts = rnd.next(8, 25);
        vector<int> values(parts, 0);
        for (int i = 0; i < target; ++i) {
            ++values[rnd.next(parts)];
        }
        for (int value : values) {
            terms.push_back(value == 0 ? string(rnd.next(1, 4), '0') : decimal(value));
        }
    } else {
        target = rnd.next(2, 120);
        int parts = rnd.next(2, min(target, 12));
        for (int value : splitPositiveSum(target, parts)) {
            terms.push_back(zeroPaddedTerm(value, rnd.next((int)decimal(value).size(), 5)));
        }
    }

    auto firstPositive = find_if(terms.begin(), terms.end(), [](const string& term) {
        return term.find_first_not_of('0') != string::npos;
    });
    if (firstPositive != terms.end()) {
        size_t firstDigit = firstPositive->find_first_not_of('0');
        *firstPositive = firstPositive->substr(firstDigit);
        iter_swap(terms.begin(), firstPositive);
    }

    string a = joinTerms(terms);
    if (a == decimal(target)) {
        a += "0";
    }

    println(a + "=" + decimal(target));
    return 0;
}
