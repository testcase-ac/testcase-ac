#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string randomString(int length, int alphabetSize) {
    string result;
    while (length--) result += char('a' + rnd.next(alphabetSize));
    return result;
}

string embed(const string& subsequence, int extra, int alphabetSize) {
    vector<int> slot(subsequence.size() + 1);
    while (extra--) ++slot[rnd.next(static_cast<int>(slot.size()))];

    string result;
    for (size_t i = 0; i < subsequence.size(); ++i) {
        result += randomString(slot[i], alphabetSize);
        result += subsequence[i];
    }
    result += randomString(slot.back(), alphabetSize);
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int alphabetSize = rnd.next(1, 5);
        string w = randomString(rnd.next(1, 10), alphabetSize);
        println(embed(w, rnd.next(0, 12), alphabetSize));
        println(embed(w, rnd.next(0, 12), alphabetSize));
        println(w);
    }
}
