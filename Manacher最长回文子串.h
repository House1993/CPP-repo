//manacher 最长回文子串

//先把字符串处理为 $#x#x#x#x……#x#x#$ 的形式  开头和结尾加入 '$' 每个字符中间插入 '#'
//插入的字符必须是原串中不存在的  目的是将奇数回文串和偶数回文串同时处理  复杂度O(n)

//p[i]表示以i为中心的回文串长  mx表示之前搜到的回文串向右的最长延伸  id表示对应mx延伸的中间字符
void manacher()
{
    int i,id,mx = 0;
	for(i=n;str[i]!=0;i++) str[i] = 0; //串尾清零  有时不用
    for(i=1;i<n;i++)
    {
        if(mx>i) p[i]=min(p[2*id-i],mx-i);//加速关键
        else p[i]=1;
        for(;str[i+p[i]]==str[i-p[i]];p[i]++);//延伸
        if(p[i]+i>mx)//更新mx和id
        {
            mx=p[i]+i;
            id=i;
        }
    }
}
