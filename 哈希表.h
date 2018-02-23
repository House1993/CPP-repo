/*
手模HashTable

枚举长度
计算当前枚举长度的字符串hash值  通过hash值来判断子串是否一致
每次清空hashtable  再将子串hash值插入  插完后判断是否满足子串在s1和s2中均只出现一次
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 10010
typedef unsigned __int64 ll;

ll base=13131,nbase[N];
ll f1[N],f2[N];
char s1[N],s2[N];
int ans,len1,len2,len;
struct hashtable
{
    int head[N];
    int next[N];
    ll state[N];
    int num_s1[N];
    int num_s2[N];
    int sz;
    void init() //清空
    {
        sz=0;
        memset(head,-1,sizeof(head));
    }
    int insert(ll val,int num) //插入值  类似邻接表构建hashtable
    {
        int h=val%N,i;
        for(i=head[h];~i;i=next[i])
        {
            if(val==state[i])
            {
                if(num) num_s1[i]++;
                else num_s2[i]++;
                return 1;
            }
        }
        num_s1[sz]=0;
        num_s2[sz]=0;
        state[sz]=val;
        next[sz]=head[h];
        if(num)num_s1[sz]++;
        else num_s2[sz]++;
        head[h] = sz++;
        return 0;
    }
    bool check()
    {
        for(int i=0;i<sz;i++)
        {
            if(num_s1[i]==num_s2[i]&&num_s1[i]==1) return true;
        }
        return false;
    }
}H;

int main()
{
    int i,j;
    nbase[0]=1;
    for(i=1;i<N;i++) nbase[i]=nbase[i-1]*base; // 计算种子的x次方
    scanf("%s%s",s1,s2);
    len1=strlen(s1);
    len2=strlen(s2);
    len=min(len1,len2);
    f1[len1]=0;
    for(i=len1-1;i>=0;i--) f1[i]=f1[i+1]*base+1+s1[i]-'a'; //hash s1
    f2[len2]=0;
    for(i=len2-1;i>=0;i--) f2[i]=f2[i+1]*base+1+s2[i]-'a'; //hash s2
    for(i=1,ans=-1;i<=len;i++)
    {
        H.init(); //清空hashtable
        for(j=0;j+i-1<len1;j++) H.insert(f1[j]-f1[j+i]*nbase[i],0); //计算长度为i的s1子串的hashval
        for(j=0;j+i-1<len2;j++) H.insert(f2[j]-f2[j+i]*nbase[i],1); //计算长度为i的s2子串的hashval
        if(H.check()) // 找在s1和s2中各出现一次的
        {
            ans=i;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}