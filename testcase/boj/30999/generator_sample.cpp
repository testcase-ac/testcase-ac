#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> oddM;
    for (int m = 1; m <= 25; m += 2) oddM.push_back(m);
    if (rnd.next(5) == 0) oddM.push_back(99);

    int n = rnd.next(1, 12);
    if (rnd.next(8) == 0) n = rnd.next(50, 100);
    int m = rnd.any(oddM);

    vector<string> votes;
    votes.reserve(n);
    for (int i = 0; i < n; ++i) {
        int majority = m / 2 + 1;
        vector<int> choices = {0, m / 2, majority, m};
        if (m > 1) {
            choices.push_back(rnd.next(0, m));
            choices.push_back(rnd.next(max(0, majority - 1), min(m, majority + 1)));
        }

        int yesCount = rnd.any(choices);
        string row(yesCount, 'O');
        row += string(m - yesCount, 'X');
        shuffle(row.begin(), row.end());
        votes.push_back(row);
    }

    println(n, m);
    for (const string& row : votes) println(row);

    return 0;
}
