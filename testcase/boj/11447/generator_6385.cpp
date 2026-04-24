#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 4);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Direction indices 0..5 in CCW: 0=x+,1=y+,2=z+,3=x-,4=y-,5=z-
        vector<int> dirs;
        int lens[6] = {0,0,0,0,0,0};
        int type = rnd.next(0, 2);
        if (type == 0) {
            // Triangle: equilateral
            int L = rnd.next(1, 5);
            dirs = {0, 2, 4};
            lens[0] = L; lens[2] = L; lens[4] = L;
        } else if (type == 1) {
            // Parallelogram
            int p = rnd.next(0, 2);
            int q = rnd.next(0, 2);
            while (q == p) q = rnd.next(0, 2);
            int a = rnd.next(1, 5), b = rnd.next(1, 5);
            dirs = {p, q, p+3, q+3};
            lens[p] = a; lens[p+3] = a;
            lens[q] = b; lens[q+3] = b;
        } else {
            // Hexagon
            int a = rnd.next(1, 5), b = rnd.next(1, 5), c = rnd.next(1, 5);
            dirs = {0,1,2,3,4,5};
            lens[0]=a; lens[3]=a;
            lens[1]=b; lens[4]=b;
            lens[2]=c; lens[5]=c;
        }
        // Sort CCW and rotate start
        sort(dirs.begin(), dirs.end());
        int C = dirs.size();
        int k = rnd.next(0, C-1);
        rotate(dirs.begin(), dirs.begin()+k, dirs.end());
        // Output
        println(C);
        for (int d : dirs) {
            char ch = "xyz"[d%3];
            int step = (d < 3 ? lens[d] : -lens[d]);
            printf("%c %d\n", ch, step);
        }
    }
    return 0;
}
