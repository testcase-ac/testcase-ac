//제 코드가 너무 느려서 ntopia님 1150815번 제출 코드를 올려요
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>
using namespace std;

bool isBetween(long long a, long long b, long long c) {
	return (a <= c && c <= b) || (b <= c && c <= a);
}

long long gcd(long long a, long long b) {
	if (a < 0 || b < 0) {
		return gcd(abs(a), abs(b));
	}
	if (b > a) {
		return gcd(b, a);
	}
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

pair<long long, long long> extended_gcd(long long a, long long b) {
	if (b == 0) {
		return make_pair(1, 0);
	}
	pair<long long, long long> t = extended_gcd(b, a % b);
	return make_pair(t.second, t.first - t.second * (a / b));
}

void proc() {
	long long a, b, c, x1, x2, y1, y2;
	long long ans = 0;
	scanf("%lld %lld %lld %lld %lld %lld %lld", &a, &b, &c, &x1, &x2, &y1, &y2);
	if (x1 > x2 || y1 > y2) {
		ans = 0;
	}
	else if (a == 0 && b == 0) {
		if (c == 0) {
			ans = (x2 - x1 + 1) * (y2 - y1 + 1);
		}
	}
	else if (a == 0) {
		if (isBetween(y1 * b, y2 * b, -c) && c % b == 0) {
			ans = x2 - x1 + 1;
		}
	}
	else if (b == 0) {
		if (isBetween(x1 * a, x2 * a, -c) && c % a == 0) {
			ans = y2 - y1 + 1;
		}
	}
	else {
		long long g = gcd(a, b);
		if (c % g == 0) {
			auto p = extended_gcd(abs(a), abs(b));
			p.first = a < 0 ? -p.first : p.first;
			p.second = b < 0 ? -p.second : p.second;

			long long k = (-c / g);
			//long long sx = p.first * k, sy = p.second * k;
			long long stepx = b / g, stepy = a / g;

			long long s, e;
			double l, r;

			l = p.first / (double)stepx * k - x2 / (double)stepx;
			r = p.first / (double)stepx * k - x1 / (double)stepx;
			if (stepx < 0) {
				swap(l, r);
			}
			s = (long long)ceil(l);
			e = (long long)floor(r);

			l = y1 / (double)stepy - p.second / (double)stepy * k;
			r = y2 / (double)stepy - p.second / (double)stepy * k;
			if (stepy < 0) {
				swap(l, r);
			}
			s = max(s, (long long)ceil(l));
			e = min(e, (long long)floor(r));

			ans = (s <= e) ? e - s + 1 : 0;
		}
	}
	printf("%lld", ans);
}

int main() {
	//freopen("input.txt", "r", stdin);
	proc();
	return 0;
}
