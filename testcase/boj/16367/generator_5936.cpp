#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lamps
    int k = rnd.next(4, 10);
    // Decide solvable or not
    bool solvable = rnd.next(0, 1) == 1;

    // Generate a hidden solution for creating "solvable" participants
    vector<char> sol(k+1);
    for (int i = 1; i <= k; i++) {
        sol[i] = rnd.next(0,1) ? 'B' : 'R';
    }

    struct Part { int l[3]; char c[3]; };
    vector<Part> parts;

    // Helper: generate a participant that has >=2 matches with sol
    auto genGood = [&](){
        Part p;
        // pick 3 distinct lamps
        vector<int> ids(k);
        for (int i = 0; i < k; i++) ids[i] = i+1;
        shuffle(ids.begin(), ids.end());
        for (int i = 0; i < 3; i++) {
            p.l[i] = ids[i];
            p.c[i] = sol[ p.l[i] ];
        }
        // decide if we flip one to get exactly 2 correct
        if (rnd.next(0,1) == 0) {
            int f = rnd.next(0,2);
            p.c[f] = (p.c[f]=='B'?'R':'B');
        }
        return p;
    };

    if (solvable) {
        // generate only good participants
        int n = rnd.next(1, k*2);
        for (int i = 0; i < n; i++) {
            parts.push_back(genGood());
        }
    } else {
        // generate some that are good
        int n0 = rnd.next(0, k);
        for (int i = 0; i < n0; i++) {
            parts.push_back(genGood());
        }
        // create a contradictory pair on the same triple
        // pick a triple
        vector<int> ids(k);
        for (int i = 0; i < k; i++) ids[i] = i+1;
        shuffle(ids.begin(), ids.end());
        int a = ids[0], b = ids[1], c = ids[2];
        // participant: all B -> requires >=2 B among (a,b,c)
        Part p1;
        p1.l[0]=a; p1.l[1]=b; p1.l[2]=c;
        p1.c[0]=p1.c[1]=p1.c[2]='B';
        parts.push_back(p1);
        // participant: all R -> requires >=2 R among (a,b,c)
        Part p2 = p1;
        p2.c[0]=p2.c[1]=p2.c[2]='R';
        parts.push_back(p2);
    }

    // shuffle all participants for variety
    shuffle(parts.begin(), parts.end());

    // output
    println(k, (int)parts.size());
    for (auto &p : parts) {
        printf("%d %c %d %c %d %c\n",
               p.l[0], p.c[0],
               p.l[1], p.c[1],
               p.l[2], p.c[2]);
    }

    return 0;
}
