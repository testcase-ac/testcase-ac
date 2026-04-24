#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of measurements (at least 2, up to 10)
    int n = rnd.next(2, 10);

    for (int i = 0; i < n; i++) {
        // Hyper‐parameter: pick integer part region for diversity
        double pr = rnd.next();
        int ip;
        if (pr < 0.3) {
            // Cold region [-10,0]
            ip = rnd.next(-10, 0);
        } else if (pr < 0.6) {
            // Mild region [1,50]
            ip = rnd.next(1, 50);
        } else if (pr < 0.8) {
            // Warm region [51,100]
            ip = rnd.next(51, 100);
        } else {
            // Hot region [101,200]
            ip = rnd.next(101, 200);
        }

        // Hyper‐parameter: choose decimal places
        double pd = rnd.next();
        int dt;  // 0 = integer, 1 = one decimal, 2 = two decimals
        if (pd < 0.2) dt = 0;
        else if (pd < 0.6) dt = 1;
        else dt = 2;

        // Enforce bounds: if ip at extreme and dt>=1, revert to integer
        if (dt >= 1 && (ip == -10 || ip == 200)) {
            dt = 0;
        }

        // Build the string representation
        string s = to_string(ip);
        if (dt == 1) {
            int fp = rnd.next(0, 9);
            s.push_back('.');
            s.push_back(char('0' + fp));
        } else if (dt == 2) {
            int fp = rnd.next(0, 99);
            s.push_back('.');
            if (fp < 10) {
                s.push_back('0');
            }
            s += to_string(fp);
        }

        println(s);
    }

    // Sentinel
    println("999");

    return 0;
}
