#include "testlib.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of robot ant reports
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Prepare a trie to validate uniqueness and structure
    // Each node has a map from food name to child node index
    vector< map<string,int> > children;
    vector<bool> isEnd;  // Marks if a sequence ends here
    children.emplace_back();
    isEnd.push_back(false);

    // Process each ant's path
    for (int i = 0; i < N; i++) {
        // Sequence length K
        int K = inf.readInt(1, 15, "K");
        int cur = 0; // start at root
        // Read K food names
        for (int j = 0; j < K; j++) {
            inf.readSpace();
            string food = inf.readToken("[A-Z]{1,15}", "food");
            // Insert or move in trie
            auto &mp = children[cur];
            if (mp.count(food)) {
                // move to existing child
                cur = mp[food];
            } else {
                // create new child
                int nxt = (int)children.size();
                mp[food] = nxt;
                children.emplace_back();
                isEnd.push_back(false);
                cur = nxt;
            }
        }
        inf.readEoln();
        // Ensure no duplicate full paths
        ensuref(!isEnd[cur],
                "Duplicate full path detected at sequence index %d (1-based)", i+1);
        isEnd[cur] = true;
    }

    inf.readEof();
    return 0;
}
