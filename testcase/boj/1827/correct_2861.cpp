#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

int n;

double speed;
double ppl[N][6];

int perm[N];

double dist(double x1, double y1, double x2, double y2) {
    double xd = x1 - x2;
    double yd = y1 - y2;
    return sqrtl(xd * xd + yd * yd);
}

void getpos(int p, double t, double *xp, double *yp) {
    double x = ppl[p][0];
    double y = ppl[p][1];

    double v = ppl[p][2];
    double a = ppl[p][3];

    *xp = x + t * v * ppl[p][4];
    *yp = y + t * v * ppl[p][5];
}

double bsrch(int p, double x, double y, double t) {
    double lo = t;  // actually t + d/s
    double hi = 1e6;

    while(hi - lo > 1e-2) {
        double mid = (hi + lo) / 2;
        double x2, y2;
        getpos(p, mid, &x2, &y2);

        double d = dist(x, y, x2, y2);
        if((mid - t) * speed < d)
            lo = mid;
        else
            hi = mid;
    }

    // printf("D: %Lf\n", lo);
    return lo;
}

double solve(void) {
    double x = 0, y = 0;
    double t = 0;

    double last = -1;

    for(int i = 0; i < n; i++) {
        t = bsrch(perm[i], x, y, t);
        getpos(perm[i], t, &x, &y);
        // printf("D: pos %Lf %Lf\n", x, y);

        double otime = dist(x, y, 0, 0) / ppl[perm[i]][2] + t;
        if(last < 0 || otime > last)
            last = otime;
    }

    // printf("D: last %Lf\n", last);
    return last;
}

void swap(int *i, int *j) {
    int t = *i;
    *i = *j;
    *j = t;
}

double permute(int c) {
    if(c == n) {
        //		printf("D: perm ");
        //		for (int i = 0; i < n; i++)
        //			printf("%d ", perm[i]);
        //		printf("\n");
        //
        return solve();
    }

    double ans = -1;

    for(int i = c; i < n; i++) {
        swap(&perm[i], &perm[c]);
        double cur = permute(c + 1);
        swap(&perm[i], &perm[c]);

        if(ans < 0 || cur < ans)
            ans = cur;
    }

    return ans;
}

void run(void) {
    n = 0;
    scanf("%d", &n);
    if(n == 0)
        exit(0);

    scanf("%lf", &speed);

    for(int i = 0; i < n; i++) {
        scanf("%lf%lf%lf%lf",
              &ppl[i][0], &ppl[i][1],
              &ppl[i][2], &ppl[i][3]);
        ppl[i][4] = cosl(ppl[i][3]);
        ppl[i][5] = sinl(ppl[i][3]);
    }

    for(int i = 0; i < n; i++)
        perm[i] = i;

    printf("%d\n", (int)roundl(permute(0)));
}

int main(void) {
    while(1)
        run();
}
