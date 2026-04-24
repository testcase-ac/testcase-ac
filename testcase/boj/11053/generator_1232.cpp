#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    vector<int> cands;
    int mx = rnd.next() < 0.5 ? 9 : 20;
    for(int i=1; i<=mx; i++) {
        cands.push_back(i);
    }
    int cand_count = min(rnd.next(2, 15), (int)cands.size());
    shuffle(cands.begin(), cands.end());
    cands.erase(cands.begin()+cand_count, cands.end());
    println(N);
    vector<int> out;
    for(int i=0; i<N; i++) {
        out.push_back(rnd.any(cands));
    }
    println(out);
}
