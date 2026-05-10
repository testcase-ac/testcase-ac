#include "testlib.h"
#include <string>
#include <set>
using namespace std;

// Checks if a string is a valid MBTI type
bool isValidMBTI(const string& s) {
    if (s.size() != 4) return false;
    if (s[0] != 'I' && s[0] != 'E') return false;
    if (s[1] != 'S' && s[1] != 'N') return false;
    if (s[2] != 'T' && s[2] != 'F') return false;
    if (s[3] != 'J' && s[3] != 'P') return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // 2. Read N lines for men's MBTI
    set<string> men_mbti;
    for (int i = 0; i < N; ++i) {
        string mbti = inf.readToken("[A-Z]{4}", "men_mbti");
        inf.readEoln();
        ensuref(isValidMBTI(mbti), "Invalid MBTI for man at line %d: %s", i+2, mbti.c_str());
        // Duplicates are allowed as per problem statement
    }

    // 3. Read N lines for women's MBTI
    set<string> women_mbti;
    for (int i = 0; i < N; ++i) {
        string mbti = inf.readToken("[A-Z]{4}", "women_mbti");
        inf.readEoln();
        ensuref(isValidMBTI(mbti), "Invalid MBTI for woman at line %d: %s", i+N+2, mbti.c_str());
        // Duplicates are allowed as per problem statement
    }

    // 4. Check for extra input
    inf.readEof();
}
