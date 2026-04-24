#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int CAP = 10000;
    // Hyper-parameter: max boarding per station (small to moderate)
    vector<int> bmax_choices = {10, 20, 50, 100};
    int bmax = rnd.any(bmax_choices);

    // Hyper-parameters: bias for boarding at station 2 and 3
    int bias2 = rnd.next(-3, 3);
    int bias3 = rnd.next(-3, 3);

    // We have exactly 4 stations
    int cur = 0;
    vector<pair<int,int>> stops(4);

    // Station 1: no one gets off, some get on
    stops[0].first = 0;
    stops[0].second = rnd.wnext(bmax + 1, bias2); 
    cur += stops[0].second;

    // Station 2
    stops[1].first = rnd.next(0, cur);          // people getting off
    {
        int space = CAP - (cur - stops[1].first);
        int hi = min(bmax, space);
        if (hi <= 0) stops[1].second = 0;
        else stops[1].second = rnd.wnext(hi + 1, bias2);
    }
    cur = cur - stops[1].first + stops[1].second;

    // Station 3
    stops[2].first = rnd.next(0, cur);
    {
        int space = CAP - (cur - stops[2].first);
        int hi = min(bmax, space);
        if (hi <= 0) stops[2].second = 0;
        else stops[2].second = rnd.wnext(hi + 1, bias3);
    }
    cur = cur - stops[2].first + stops[2].second;

    // Station 4: last station, nobody boards
    stops[3].first = rnd.next(0, cur);
    stops[3].second = 0;
    cur -= stops[3].first;

    // Output the 4 lines
    for (int i = 0; i < 4; i++) {
        println(stops[i].first, stops[i].second);
    }
    return 0;
}
