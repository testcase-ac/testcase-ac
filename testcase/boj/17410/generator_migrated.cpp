#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 100);
    cout << n << endl;

    for(int i = 1; i <= n; i++){
        cout << rnd.next(1, 100);
        if(i != n) cout << ' ';
    }
    cout << endl;

    int m = rnd.next(2, 30);
    cout << m << endl;
    int forcedType2 = rnd.next(1, m);
    for(int q = 1; q <= m; q++){
        int mode = (q == forcedType2) ? 2 : rnd.next(1, 2);
        cout << mode << ' ';
        if(mode == 1){
            int i = rnd.next(1, n);
            cout << i << ' ';
            int v = rnd.next(1, 100);
            cout << v << endl;
        } else {
            int i = rnd.next(1, n);
            cout << i << ' ';
            int j = rnd.next(i, n);
            cout << j << ' ';
            int k = rnd.next(1, 100);
            cout << k << endl;
        }
    }

    return 0;
}
