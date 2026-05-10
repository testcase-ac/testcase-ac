#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string S1
    string S1 = inf.readLine("[A-Z\\*]{1,50}", "S1");
    int n1 = S1.size();
    ensuref(n1 >= 1 && n1 <= 50, "Length of S1 must be between 1 and 50, got %d", n1);

    int star_count1 = 0;
    for (char c : S1) {
        ensuref((c == '*' || (c >= 'A' && c <= 'Z')), "S1 contains invalid character: '%c'", c);
        if (c == '*') star_count1++;
    }
    ensuref(star_count1 == 1, "S1 must contain exactly one '*' character, found %d", star_count1);

    // Read second string S2
    string S2 = inf.readLine("[A-Z\\*]{1,50}", "S2");
    int n2 = S2.size();
    ensuref(n2 >= 1 && n2 <= 50, "Length of S2 must be between 1 and 50, got %d", n2);

    int star_count2 = 0;
    for (char c : S2) {
        ensuref((c == '*' || (c >= 'A' && c <= 'Z')), "S2 contains invalid character: '%c'", c);
        if (c == '*') star_count2++;
    }
    ensuref(star_count2 == 1, "S2 must contain exactly one '*' character, found %d", star_count2);

    inf.readEof();
}
