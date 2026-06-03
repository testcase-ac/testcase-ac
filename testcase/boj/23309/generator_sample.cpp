#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxLabel = 200;
    vector<int> labels;
    for (int i = 1; i <= maxLabel; ++i) {
        labels.push_back(i);
    }
    shuffle(labels.begin(), labels.end());

    int n;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else {
        n = rnd.next(3, 12);
    }

    vector<int> order(labels.begin(), labels.begin() + n);
    vector<int> inactive(labels.begin() + n, labels.end());
    int m = rnd.next(8, 60);

    vector<string> ops;
    for (int q = 0; q < m; ++q) {
        bool mustInsert = order.size() == 1 || (!inactive.empty() && rnd.next(100) < 45);
        if (inactive.empty()) {
            mustInsert = false;
        }

        int pos = rnd.next((int)order.size());
        int i = order[pos];

        if (mustInsert) {
            int pick = rnd.next((int)inactive.size());
            int j = inactive[pick];
            inactive[pick] = inactive.back();
            inactive.pop_back();

            if (rnd.next(2) == 0) {
                ops.push_back("BN " + to_string(i) + " " + to_string(j));
                order.insert(order.begin() + pos + 1, j);
            } else {
                ops.push_back("BP " + to_string(i) + " " + to_string(j));
                order.insert(order.begin() + pos, j);
            }
        } else {
            if (rnd.next(2) == 0) {
                int removedPos = (pos + 1) % (int)order.size();
                ops.push_back("CN " + to_string(i));
                inactive.push_back(order[removedPos]);
                order.erase(order.begin() + removedPos);
            } else {
                int removedPos = (pos + (int)order.size() - 1) % (int)order.size();
                ops.push_back("CP " + to_string(i));
                inactive.push_back(order[removedPos]);
                order.erase(order.begin() + removedPos);
            }
        }
    }

    println(n, m);
    vector<int> initial(labels.begin(), labels.begin() + n);
    println(initial);
    for (const string& op : ops) {
        println(op);
    }

    return 0;
}
