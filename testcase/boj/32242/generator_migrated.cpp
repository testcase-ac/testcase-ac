//GPT 코드
#include "testlib.h"
using namespace std;

int main(int argc,char*argv[]){
	registerGen(argc,argv,1);
    while(1) {
	long long b=1e9;

	long long A=rnd.next(1LL,1000000LL);
	if(rnd.next(0,1)) A=-A;

	long long K=rnd.next(-1000000000LL,1000000000LL);
	while(K==0) K=rnd.next(-1000000000LL,1000000000LL);

	long long d=rnd.next(1LL,1000000LL);
	if(rnd.next(0,1)) d=-d;

	long long e=K/d;
	if(d*e!=K) e=1;

	long long C=d-A*rnd.next(-1000LL,1000LL);
	long long B=e-A*rnd.next(-1000LL,1000LL);

	long long D=(B*C-K)/A;
    if(abs(A)<=1e9&&abs(B)<=1e9&&abs(C)<=1e9&&abs(D)<=1e9) {cout<<A<<" "<<B<<" "<<C<<" "<<D;break;}
    }
}
