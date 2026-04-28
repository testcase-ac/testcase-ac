#include<cstdio>

int N, i, j, k;
long long B;
int r[5][5], m[5][5], t[5][5];

void matmul(int a[][5], int b[][5])
{
  for(i=0;i<N*N;i++) t[i/N][i%N]=0;

  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      for(k=0;k<N;k++)
        t[i][j]+=a[i][k]*b[k][j];

  for(i=0;i<N*N;i++) a[i/N][i%N]=t[i/N][i%N]%1000;

}

int main()
{
  scanf("%d%lld",&N,&B);
  for(;i<N;i++)
    for(j=0,r[i][i]=1;j<N;j++)
      scanf("%d",m[i]+j);

  for(;B;B>>=1)
  {
    if(B%2)
      matmul(r,m);
    
    matmul(m,m);
  }

  for(i=0;i<N;i++,printf("\n"))
    for(j=0;j<N;j++)
      printf("%d ",r[i][j]);
}

// #include <cstdio>
// int n, i, j, k;
// long long int b;
// void cal(int a1[][5], int a2[][5]) {
//   int c[5][5] = {0};
//   for (i = 0; i < n; i++)
//     for (j = 0; j < n; j++)
//       for (k = 0; k < n; k++) c[i][j] += a1[i][k] * a2[k][j];
//   for (i = 0; i < n; i++)
//     for (j = 0; j < n; j++) a1[i][j] = c[i][j] % 1000;
// }
// int main() {
//   int a[5][5], aa[5][5] = {0};
//   scanf("%d %lld", &n, &b);
//   for (i = 0; i < n; aa[i][i] = 1, i++)
//     for (j = 0; j < n && scanf("%d", &a[i][j]); j++);
//   while (b) b % 2 ? (cal(aa, a), b--) : (cal(a, a), b /= 2);
//   for (i = 0; i < n; printf("\n"), i++)
//     for (j = 0; j < n; j++) printf("%d ", aa[i][j] % 1000);
// }

