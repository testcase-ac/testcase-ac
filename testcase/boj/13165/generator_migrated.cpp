//GPT 코드
#include<bits/stdc++.h>
#include <random>
#include <cstdlib>
#include <chrono>
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device

using ll=long long;

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	ios::sync_with_stdio(0);
	cin.tie(0);

	random_device rd;
	mt19937_64 r(rd());

	int N=r()%20+1;

	int mx=140/N;
	int L=r()%mx+1;

	vector<vector<ll>> a(N,vector<ll>(L));

	for(int i=0;i<N;i++)
		for(int j=0;j<L;j++)
			a[i][j]=r()%7676768;

	if(L>=3*N){
		int t=r()%5+1;
		while(t--){
			int s=r()%(L-3*N+1);

			vector<vector<ll>> A(N,vector<ll>(N));
			vector<vector<ll>> B(N,vector<ll>(N));
			vector<vector<ll>> C(N,vector<ll>(N));

			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++){
					A[i][j]=r()%10;
					B[i][j]=r()%10;
				}

			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++){
					ll v=0;
					for(int k=0;k<N;k++)
						v+=A[i][k]*B[k][j];
					C[i][j]=v;
				}

			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++){
					a[i][s+j]=A[i][j];
					a[i][s+N+j]=B[i][j];
					a[i][s+2*N+j]=C[i][j];
				}
		}
	}

	cout<<N<<' '<<L<<'\n';
	for(int i=0;i<N;i++){
		for(int j=0;j<L;j++){
			cout<<a[i][j];
			if(j+1<L)cout<<' ';
		}
		cout<<'\n';
	}
}
