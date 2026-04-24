#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of filenames
    int n = rnd.next(1, 10);

    // Alphabet size for filenames
    int alpha = rnd.next(2, 5);
    vector<char> letters;
    for (int i = 0; i < alpha; i++)
        letters.push_back(char('a' + i));

    // Maximum individual string length (ensure enough domain for uniqueness)
    int maxStrLen = rnd.next(3, 10);

    // Length distribution bias parameter
    int tLen = rnd.next(-2, 2);

    // Generate n distinct random strings
    set<string> S;
    while ((int)S.size() < n) {
        int len = rnd.wnext(maxStrLen, tLen) + 1;
        string s;
        for (int i = 0; i < len; i++)
            s += rnd.any(letters);
        S.insert(s);
    }

    // Sort lexicographically
    vector<string> v(S.begin(), S.end());
    sort(v.begin(), v.end());

    // Determine terminal width w: at least the longest string, plus some slack
    int maxFound = 0;
    for (auto &s : v)
        if ((int)s.size() > maxFound)
            maxFound = s.size();
    int wSlack = rnd.next(0, 5);
    int w = maxFound + wSlack;

    // Output
    println(n, w);
    for (auto &s : v)
        println(s);

    return 0;
}
