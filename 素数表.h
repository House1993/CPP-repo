//O(n)素数表

void get_prime()
{
	int i,j;
	for(i=2;i<n;i++)
	{
		if(!flag[i]) p[cnt++]=i;
		for(j=0;j<cnt&&p[j]*i<n;j++)
		{
			flag[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
