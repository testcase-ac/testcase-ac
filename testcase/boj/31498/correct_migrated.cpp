// 출처: https://jengdeuk.tistory.com/176
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	ll A, B, C, D, K;
	cin >> A >> B >> C >> D >> K;

	ll End = ceil(double(A + C) / D);

	ll S = 1;
	ll E = End;
	ll Catch = End;
	ll Arrive = End + 1;
	while (S <= E)
	{
		ll T = (S + E) / 2;
		if (B - K * (T - 1) <= 0)
		{
			E = T - 1;
			continue;
		}

		ll Toca = A - (T * (2 * B - K * (T - 1)) / 2);
		ll Doldol = A + C - T * D;
		if (Toca <= 0)
		{
			Arrive = min(Arrive, T);
			E = T - 1;
		}
		else
		{
			if (Toca >= Doldol)
			{
				Catch = min(Catch, T);
			}
			S = T + 1;
		}
	}

	if (Arrive < Catch)
	{
		cout << Arrive;
	}
	else
	{
		cout << -1;
	}
}
