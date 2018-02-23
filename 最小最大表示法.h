//最小、最大表示法
//时间复杂度O(n)

int GetMin(char *str) //str为所求串的s的二倍  即ss
{
    int i,j,k,len=strlen(str)/2;
    for(i=0,j=1;i<len&&j<len;)
    {
        for(k=0;k<len&&str[i+k]==str[j+k];k++);
        if(k>=len) break;
        if(str[i+k]<str[j+k]) j+=k+1; //如果是最大表示法  把if里面改成>
        else i+=k+1;
        if(i==j) j++;
    }
    return i; //返回字典序最小的串的首字母位置
}
