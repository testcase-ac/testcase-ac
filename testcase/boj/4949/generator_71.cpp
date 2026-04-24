#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
string generate_balanced_brackets_shuffled() {
    int num_pairs = rnd.next(1, 5); // Generate 0 to 4 pairs of brackets
    if(rnd.next() < 0.1) {
        num_pairs = 49;
    }
    vector<char> lefts;
    for (int i = 0; i < num_pairs; i++) {
        if (rnd.next(0, 1)) {
            lefts.push_back('(');
        } else {
            lefts.push_back('[');
        }
    }
    string s;
    for (char c : lefts) {
        s += c;
    }
    reverse(lefts.begin(), lefts.end());
    for (char c : lefts) {
        s += (c == '(' ? ')' : ']');
    }
    int do_shuffle = rnd.next(0, 1);
    if (do_shuffle) {
        int swap_count = rnd.next(1, 10);
        for (int i = 0; i < swap_count; i++) {
            int a = rnd.next(0, (int)s.size() - 1);
            int b = rnd.next(0, (int)s.size() - 1);
            swap(s[a], s[b]);
        }
    }
    return s;
}
string replace_random_chars(const string& brackets) {
    string result;
    int do_replace = rnd.next() < 0.3;
    if(!do_replace) {
        return brackets;
    }

    vector<char> replace_chars = {'a', 'b', '[', ']', '(', ')', ' '};
    double replace_prob = rnd.next();
    if (rnd.next() < replace_prob) {
        result += replace_chars[rnd.next(0, (int)replace_chars.size() - 1)];
    }
    for (char c : brackets) {
        if (rnd.next() < replace_prob) {
            result += replace_chars[rnd.next(0, (int)replace_chars.size() - 1)];
        } else {
            result += c;
        }
    }
    return result;
}


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int num_datasets = rnd.next(1, 10); // Generate 1 to 3 datasets

    for (int i = 0; i < num_datasets; ++i) {
        string brackets = generate_balanced_brackets_shuffled();
        brackets = replace_random_chars(brackets);
        if(brackets.size() == 98) {
            brackets += 'a'; // to get to max tc
        }
        brackets += ".";
        println(brackets);
    }

    println("."); // End of input

    return 0;
}
