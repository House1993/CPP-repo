//凸包graham算法  nlogn
struct point
{
    double x,y;
}lis[N];
int yes[N],top,n; //最后yes中的点就是凸包顶点

double cross(point p0,point p1,point p2) //叉积
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

double dis(point p1,point p2)
{
    return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

bool cmp(point p1,point p2)
{
    double tmp=cross(lis[0],p1,p2);
    if((fabs(tmp)<1e-8&&dis(lis[0],p1)<dis(lis[0],p2))||tmp>1e-8) return true;
    return false;
}

void init()
{
    int i,k;
    point p0;
    scanf("%lf%lf",&lis[0].x,&lis[0].y);
    p0=lis[0];
    k=0;
    for(i=1;i<n;i++)
    {
        scanf("%lf%lf",&lis[i].x,&lis[i].y);
        if( (p0.y>lis[i].y) || (fabs(p0.y-lis[i].y)<1e-8&&(p0.x>lis[i].x)) )
        {
            p0.x=lis[i].x;
            p0.y=lis[i].y;
            k=i;
        }
    }
    lis[k]=lis[0];
    lis[0]=p0;
    sort(lis+1,lis+n,cmp);
}

void graham()
{
    int i;
    if(n==1)
	{
		top=0;
		yes[0]=0;
	}
    if(n==2)
    {
        top=1;
        yes[0]=0;
        yes[1]=1;
    }
    if(n>2)
    {
        for(i=0;i<=1;i++) yes[i]=i;
        top=1;
        for(i=2;i<n;i++)
        {
            while(top>0&&cross(lis[yes[top-1]],lis[yes[top]],lis[i])<=0) top--;
            top++;
            yes[top]=i;
        }
    }
}