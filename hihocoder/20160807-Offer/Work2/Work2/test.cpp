#include "stdafx.h"

#include<cstdio>
#include<cmath>
int a[15];
int b[15];
double b1[15];

int main()
{
	
	int n,k;
	while(scanf_s("%d%d",&n,&k)!=EOF)
	{
		for(int i=0;i<k;i++)
			scanf_s("%d",&a[i]);
		for(int i=0;i<k;i++)
		{
			scanf_s("%d",&b[i]);
			b1[i] = 1.0 / b[i];
		}
		while(n>0)
		{
			double max1,max2,temp;
			int ans1,ans2;
			max1 = max2 = 0;
			ans1 = ans2 = 0;
			for(int i=0;i<k;i++)
			{
				temp = b1[i] / a[i];
				if(temp >= max1)
				{
					max2 = max1;
					max1 = temp;
					ans2 = ans1;
					ans1 = i;
				}
				else if(temp >= max2)
				{
					max2 = temp;
					ans2 = i;
				}
			}
			temp = (b1[ans1]) / max2;
			int ci = (int)temp +1 - a[ans1];
			if(ci <=0)
				ci = 1;
			if(ci >= n)
				ci = n;
			n -= ci;
			a[ans1] += ci;
			//printf("%d\n",n);
		}
		double ans = 1;
		for(int i=0;i<k;i++)
		{
			ans *= pow(a[i],b1[i]);
		}
		printf("%lf\n",ans);
	}
}
