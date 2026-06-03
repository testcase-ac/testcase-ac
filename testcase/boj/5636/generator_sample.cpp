#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

const vector<string> kPrimes = {
    "2",     "3",     "5",     "7",     "11",    "13",    "17",
    "19",    "23",    "29",    "31",    "37",    "41",    "43",
    "47",    "53",    "59",    "61",    "67",    "71",    "73",
    "79",    "83",    "89",    "97",    "101",   "997",   "1009",
    "7919",  "99991",
};

string randomDigits(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('0' + rnd.next(0, 9)));
    }
    return s;
}

string randomCompositeLikeDigits(int len) {
    string s;
    s.reserve(len);
    const string digits = "014689";
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(digits));
    }
    return s;
}

void injectSubstring(string& s, const string& t) {
    int pos = rnd.next(0, static_cast<int>(s.size()) - static_cast<int>(t.size()));
    s.replace(pos, t.size(), t);
}

string makeCase() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        string prime = rnd.any(kPrimes);
        int extraLeft = rnd.next(0, 4);
        int extraRight = rnd.next(0, 4);
        return randomDigits(extraLeft) + prime + randomDigits(extraRight);
    }

    if (mode == 1) {
        int len = rnd.next(8, 28);
        string s = randomCompositeLikeDigits(len);
        injectSubstring(s, rnd.any(kPrimes));
        return s;
    }

    if (mode == 2) {
        int zeros = rnd.next(1, 18);
        string prime = rnd.any(kPrimes);
        return string(zeros, '0') + prime;
    }

    if (mode == 3) {
        vector<string> boundary = {"99991", "1000002", "0999910", "9999199991"};
        string s = rnd.any(boundary);
        if (rnd.next(0, 1) == 1) {
            s = randomDigits(rnd.next(0, 3)) + s + randomDigits(rnd.next(0, 3));
        }
        return s;
    }

    if (mode == 4) {
        int len = rnd.next(20, 60);
        string s = randomDigits(len);
        injectSubstring(s, rnd.any(kPrimes));
        return s;
    }

    string prime = rnd.any(kPrimes);
    string s = randomCompositeLikeDigits(rnd.next(static_cast<int>(prime.size()), 30));
    injectSubstring(s, prime);
    return s;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(4, 20);
    for (int i = 0; i < cases; ++i) {
        println(makeCase());
    }
    println("0");

    return 0;
}
