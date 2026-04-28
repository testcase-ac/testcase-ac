#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#pragma GCC optimize ("Ofast")

using namespace std;

using ld = double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using ushort = unsigned short;
using uchar = unsigned char;

const int mod = int(1e4 + 7);
const int prime = int(2e9 + 11);
const ld pi = acosl(-1);
const ld eps = 1e-13;
const int dirs[4][2] = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } };

template<typename T>
constexpr T inf() { return numeric_limits<T>::max() / 2; }

void error()
{
	cout << -1 << endl;
	exit(0);
}

char stdinBuffer[22000000];
char* stdinDataEnd = stdinBuffer + sizeof(stdinBuffer);
const char* stdinPos = stdinDataEnd;

void initReadInt()
{
	memmove(stdinBuffer, stdinPos, 0);
	size_t sz = fread(stdinBuffer, 1, sizeof(stdinBuffer), stdin);
	stdinPos = stdinBuffer;
	stdinDataEnd = stdinBuffer + sz;
	if (stdinDataEnd != stdinBuffer + sizeof(stdinBuffer))
		*stdinDataEnd = 0;
}

int readInt()
{
	int x = 0;
	bool neg = 0;

	while (*stdinPos < '0' || *stdinPos > '9')
	{
		if (*stdinPos == '-')
		{
			++stdinPos;
			neg = true;
			break;
		}
		++stdinPos;
	}

	while (*stdinPos >= '0' && *stdinPos <= '9')
	{
		x = *stdinPos - '0' + 10 * x;
		++stdinPos;
	}
	return neg ? -x : x;
}

hash<int> hashf;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

	initReadInt();
	int t = readInt();
	while (t--)
	{
		vector<int> bucket[mod];
		int n = readInt();
		forh(i, 0, n)
		{
			int x = readInt();
			bucket[hashf(x) % mod].push_back(x);
		}
		n = readInt();
		forh(i, 0, n)
		{
			int x = readInt();
			auto &v = bucket[hashf(x) % mod];
			cout << (find(v.begin(), v.end(), x) != v.end()) << endl;
		}
	}

	return 0;
}

// https://www.acmicpc.net/source/10426650
