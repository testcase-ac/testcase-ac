#include "testlib.h"
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate string S with length between 1 and 10
    int len = rnd.next(1, 5);
    string S;
    const char *chars = "[a-h]";
    for (int i = 0; i < len; i++) {
        S += rnd.next(chars);
    }

    // Collect unique characters in S
    unordered_set<char> available_chars;
    for (char c : S) {
        available_chars.insert(c);
    }
    vector<char> possible_chars(available_chars.begin(), available_chars.end());

    // Generate n between 1 and 10
    int n = rnd.next(1, 10);

    vector<string> queries;
    int type2Count = 0;

    auto generateType1 = [&]() {
        char i1, i2;
        // 70% chance to pick i1 from possible_chars if available
        if (!possible_chars.empty() && rnd.next(0, 9) < 7) {
            int idx = rnd.next(0, (int)possible_chars.size() - 1);
            i1 = possible_chars[idx];
        } else {
            i1 = rnd.next(chars)[0];
        }
    
        // Ensure i2 is different from i1
        do {
            i2 = rnd.next(chars)[0];
        } while (i2 == i1);

        return string("1 ") + i1 + " " + i2;
    };

    if (n == 1) {
        // Only query must be type 2
        queries.push_back("2");
        type2Count++;
    } else {
        bool prevWasType2 = false;
        for (int i = 0; i < n - 1; ++i) {
            if (prevWasType2) {
                // Must generate type 1
                queries.push_back(generateType1());
                prevWasType2 = false;
            } else {
                // Decide type 2 or 1
                if (rnd.next(0, 9) < 3) { // 30% chance for type 2
                    queries.push_back("2");
                    type2Count++;
                    prevWasType2 = true;
                } else {
                    queries.push_back(generateType1());
                    prevWasType2 = false;
                }
            }
        }

        // Check if the last of the first n-1 queries is type 2
        if (!queries.empty() && queries.back()[0] == '2') {
            queries.pop_back();
            queries.push_back(generateType1());
            type2Count--;
        }

        // Add the last query as type 2
        queries.push_back("2");
        type2Count++;
    }

    // Output the test case
    println(S, n);
    for (const string& q : queries) {
        println(q);
    }

    return 0;
}
