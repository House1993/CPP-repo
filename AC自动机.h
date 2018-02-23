#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int T,n,tot,ans;
struct node
{
    int next[26];
    int cnt,fail;
    void init()
    {
        memset(next,-1,sizeof(next));
        fail=cnt=0;
    }
}nd[500010];
int qu[500010];
int head,tail;
string word;

void mf()
{
    int i,j,idx,fa;
    head=tail=0;
    for(i=0;i<26;i++)
    {
        if(nd[0].next[i]!=-1)
            qu[tail++]=nd[0].next[i];
    }
    while(head<tail)
    {
        fa=qu[head++];
        for(i=0;i<26;i++)
        {
            if(nd[fa].next[i]!=-1)
            {
                qu[tail++]=nd[fa].next[i];
                idx=nd[fa].fail;
                while(idx>0&&nd[idx].next[i]==-1) idx=nd[idx].fail;
                if(nd[idx].next[i]!=-1) idx=nd[idx].next[i];
                nd[nd[fa].next[i]].fail=idx;
            }
        }
    }
}

void fd()
{
    int i,len,idx,trvl;
    len=word.size();
    for(i=idx=0;i<len;i++)
    {
        while(idx>0&&nd[idx].next[word[i]-'a']==-1) idx=nd[idx].fail;
        if(nd[idx].next[word[i]-'a']!=-1)
        {
            trvl=idx=nd[idx].next[word[i]-'a'];
            while(trvl>0&&nd[trvl].cnt!=-1)
            {
                ans+=nd[trvl].cnt;
                nd[trvl].cnt=-1;
                trvl=nd[trvl].fail;
            }
        }
    }
}

int main()
{
    int i,len,j,idx;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        tot=0;//建trie树
        nd[0].init();
        for(i=1;i<=n;i++)
        {
            cin>>word;
            len=word.size();
            for(j=idx=0;j<len;j++)
            {
                if(nd[idx].next[word[j]-'a']==-1)
                {
                    nd[idx].next[word[j]-'a']=++tot;
                    nd[tot].init();
                }
                idx=nd[idx].next[word[j]-'a'];
            }
            nd[idx].cnt++;
        }
        mf();//在trie上加fail指针
        ans=0;
        cin>>word;
        fd();//匹配
        printf("%d\n",ans);
    }
    return 0;
}
