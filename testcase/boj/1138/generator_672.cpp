#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }
    vector<int> res(N);
    shuffle(v.begin(), v.end());
    for(int i=0; i<N; i++) {
        int cnt = 0;
        for(int j=0; j<i; j++) {
            if(v[j] > v[i]) cnt++;
        }
        res[v[i]] = cnt;
    }
    println(N);
    println(res);
}
