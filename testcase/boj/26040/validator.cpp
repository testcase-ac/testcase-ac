#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[A-Za-z]{3,100000}", "A");
    inf.readEoln();

    string bLine = inf.readLine("[A-Z\\ ]{1,51}", "B");
    ensuref(bLine.front() != ' ', "B must not start with a space");
    ensuref(bLine.back() != ' ', "B must not end with a space");

    vector<bool> seen(26, false);
    int count = 0;
    for (int i = 0; i < (int)bLine.size(); ++i) {
        if (i % 2 == 0) {
            ensuref('A' <= bLine[i] && bLine[i] <= 'Z',
                    "B item %d must be an uppercase letter", count + 1);
            int idx = bLine[i] - 'A';
            ensuref(!seen[idx], "duplicate letter in B: %c", bLine[i]);
            seen[idx] = true;
            ++count;
        } else {
            ensuref(bLine[i] == ' ', "B letters must be separated by single spaces");
        }
    }

    ensuref(1 <= count && count <= 26, "B must contain between 1 and 26 letters");
    inf.readEof();
}
