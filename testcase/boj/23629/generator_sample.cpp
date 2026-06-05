#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const vector<string> DIGIT_WORDS = {"ZERO", "ONE", "TWO",   "THREE", "FOUR",
                                    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
const string OPS = "+-x/";

string encodeNumber(int value) {
    string digits = to_string(value);
    string encoded;
    for (char digit : digits) {
        encoded += DIGIT_WORDS[digit - '0'];
    }
    return encoded;
}

int randomNumber(int mode) {
    if (mode == 0) {
        return rnd.next(1, 99);
    }
    if (mode == 1) {
        return rnd.next(1, 1000000);
    }

    vector<int> boundary_values = {1, 2, 9, 10, 11, 99, 100, 101,
                                   999999, 1000000};
    return rnd.any(boundary_values);
}

string randomExpression(int terms, bool division_heavy, int number_mode) {
    string result = encodeNumber(randomNumber(number_mode));
    for (int i = 1; i < terms; ++i) {
        char op = division_heavy ? rnd.any(string("///+-x")) : rnd.any(OPS);
        int value = randomNumber(number_mode);
        result += op;
        result += encodeNumber(value);
    }
    result += '=';
    return result;
}

string randomUndecodableSegment() {
    vector<string> fragments = {"A", "B", "TEN", "ELEVEN", "ON", "TW", "NIN",
                                "THRE", "XYZ"};
    string segment = rnd.any(fragments);
    int extra = rnd.next(0, 2);
    for (int i = 0; i < extra; ++i) {
        segment += rnd.any(fragments);
    }
    return segment;
}

string randomMadnessExpression() {
    int terms = rnd.next(1, 5);
    int broken_index = rnd.next(terms);

    string result;
    for (int i = 0; i < terms; ++i) {
        if (i > 0) {
            result += rnd.any(OPS);
        }

        if (i == broken_index) {
            result += randomUndecodableSegment();
        } else {
            result += encodeNumber(randomNumber(rnd.next(0, 2)));
        }
    }
    result += '=';
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    string output;

    if (mode == 0) {
        output = randomExpression(rnd.next(1, 4), false, 0);
    } else if (mode == 1) {
        output = randomExpression(rnd.next(2, 5), true, 0);
    } else if (mode == 2) {
        output = randomExpression(rnd.next(1, 2), false, rnd.next(1, 2));
    } else if (mode == 3) {
        output = randomMadnessExpression();
    } else {
        string left = encodeNumber(rnd.next(1, 999));
        string right = encodeNumber(rnd.next(1, 999));
        output = left + rnd.any(string("+-")) + rnd.any(string("+-")) + right + '=';
    }

    println(output);
    return 0;
}
