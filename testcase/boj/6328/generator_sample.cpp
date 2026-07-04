#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

namespace {

string makeName(int id) {
    return "Author" + to_string(id) + ", " + char('A' + (id % 26)) + ".";
}

string makeTitle(int id) {
    return "Paper " + to_string(id);
}

void printPaper(const vector<string>& authors, int titleId) {
    for (int i = 0; i < (int)authors.size(); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << authors[i];
    }
    cout << ": " << makeTitle(titleId) << '\n';
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string erdos = "Erdos, P.";

    int scenarios = rnd.next(1, 3);
    int nextAuthorId = 1;
    for (int tc = 0; tc < scenarios; ++tc) {
        int chainLen = rnd.next(1, 5);
        int isolatedPapers = rnd.next(0, 3);
        int groupPapers = rnd.next(0, 2);

        vector<string> connected;
        for (int i = 0; i < chainLen; ++i) {
            connected.push_back(makeName(nextAuthorId++));
        }

        vector<vector<string>> papers;
        papers.push_back({erdos, connected[0]});
        for (int i = 1; i < chainLen; ++i) {
            papers.push_back({connected[i - 1], connected[i]});
        }

        vector<string> disconnected;
        for (int i = 0; i < isolatedPapers; ++i) {
            string a = makeName(nextAuthorId++);
            string b = makeName(nextAuthorId++);
            disconnected.push_back(a);
            disconnected.push_back(b);
            papers.push_back({a, b});
        }

        for (int i = 0; i < groupPapers; ++i) {
            int groupSize = rnd.next(3, 5);
            vector<string> group;
            if (rnd.next(0, 1) == 1) {
                group.push_back(erdos);
            }
            for (int j = (int)group.size(); j < groupSize; ++j) {
                group.push_back(makeName(nextAuthorId++));
            }
            shuffle(group.begin(), group.end());
            papers.push_back(group);
        }

        shuffle(papers.begin(), papers.end());

        vector<string> queries;
        queries.push_back(erdos);
        queries.push_back(rnd.any(connected));
        queries.push_back(connected.back());
        if (!disconnected.empty()) {
            queries.push_back(rnd.any(disconnected));
        }
        queries.push_back(makeName(nextAuthorId++));
        shuffle(queries.begin(), queries.end());

        println((int)papers.size(), (int)queries.size());
        for (int i = 0; i < (int)papers.size(); ++i) {
            printPaper(papers[i], tc * 100 + i + 1);
        }
        for (const string& query : queries) {
            println(query);
        }
    }

    println(0, 0);
    return 0;
}
