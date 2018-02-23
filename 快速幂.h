//*******************************************************//
//1.整数的快速幂 m^n  % k 的快速幂：
long long quickpow(long long m , long long n , long long k)
{
    long long ans = 1;
    while(n)
    {
        if(n&1) ans = (ans * m) % k; //如果n是奇数
        n = n >> 1; //位运算“右移1类似除2”
        m = (m * m) % k;
    }
    return ans;
}
//*******************************************************//

//*******************************************************//
//2.矩阵快速幂： 求（A^n）%mod
typedef unsigned __int64 uint64;
const int mat_n=2; //矩阵的维度
void matrix_mul(uint64 a[][mat_n],uint64 b[][mat_n],uint64 mod) //a=a*b 进行矩阵乘法的函数
{
    uint64 c[mat_n][mat_n];
    int i,j,k;
    for(i=0;i<mat_n;i++)
    {
        for(j=0;j<mat_n;j++)
        {
            c[i][j]=0;
            for(k=0;k<mat_n;k++)
            {
                c[i][j]=(c[i][j]+(a[i][k]*b[k][j])%mod)%mod;
            }
        }
    }
 
    for(i=0;i<mat_n;i++)
        for(j=0;j<mat_n;j++)
            a[i][j]=c[i][j];
}

void matrix_power(uint64 s[][mat_n],uint64 k,uint64 mod) // return s[n][n]^k%mod
{
    uint64 ans[mat_n][mat_n];
    memset(ans,0,sizeof(ans));
    int i,j;
    for(i=0;i<mat_n;i++)
        ans[i][i]=1;

    while(k>0)
    {
        if(k%2==1) matrix_mul(ans,s,mod);
        k=k/2;
        matrix_mul(s,s,mod);
    }

    for(i=0;i<mat_n;i++)
        for(j=0;j<mat_n;j++)
            s[i][j]=ans[i][j];
}
//*********************************************************//