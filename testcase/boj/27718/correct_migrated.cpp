#include <stdio.h>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<b;i++)
using namespace std;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3);
int isIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int x[4001];
int y[4001];

int main() {
    int N;
    scanf("%d", &N);
    rep(i,0,N*2) scanf("%d %d", x+i, y+i);

    for (int i=0;i<N*2;i+=2) {
        for (int j=0;j<N*2;j+=2) {
            int ans = isIntersect(
                x[i], y[i], x[i+1], y[i+1], x[j], y[j], x[j+1], y[j+1]);
            printf("%d", ans);
        }
        printf("\n");
    }

}

int isIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int P123 = ccw(x1, y1, x2, y2, x3, y3);
    int P124 = ccw(x1, y1, x2, y2, x4, y4);
    int P341 = ccw(x3, y3, x4, y4, x1, y1);
    int P342 = ccw(x3, y3, x4, y4, x2, y2);

    // 모든 점이 일직선 상에 있을 경우
    if (!(P123 || P124 || P341 || P342)) {
        // 두 선이 완전히 겹칠 때
        if ((x1 == x3 && y1 == y3 && x2 == x4 && y2 == y4) ||
            (x1 == x4 && y1 == y4 && x2 == x3 && y2 == y3)) {
            return 3;
        }
        if (x1 != x2) {
            int minX = max(min(x1, x2), min(x3, x4));
            int maxX = min(max(x1, x2), max(x3, x4));
            if (minX < maxX) {
                return 3;
            } else if (minX == maxX) {
                return 1;
            }
        }
        else {
            int minY = max(min(y1, y2), min(y3, y4));
            int maxY = min(max(y1, y2), max(y3, y4));
            if (minY < maxY) {
                return 3;
            } else if (minY == maxY) {
                return 1;
            }
        }
        return 0;
    }

    
    if ((P123 * P124 <= 0) && (P341 * P342 <= 0)) {
        // 일단 교차점은 있는 상태, 끝점이 있는가? (ccw 하나라도 있다면)
        if (P123 * P124 * P341 * P342 == 0) return 1;
        return 2;
    }
    else return 0;
}

int ccw(int x1, int y1, int x2, int y2, int x3, int y3){
    long long res = 1LL*(x2-x1)*(y3-y1)-1LL*(y2-y1)*(x3-x1);
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}
