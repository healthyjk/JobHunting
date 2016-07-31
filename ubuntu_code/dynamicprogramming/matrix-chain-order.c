/*======================================================
#
# Filename: matrix-chain-order.c
#
# Version: 
#
# Last modified: 2016-02-28 17:05
#
# Description: 
#
# Author: jkyan - jkyan@fudan.edu.cn
#
# Copyright (c) 2014, All Right Reserved, MicroSystems, Fudan University
#
# Mode: C++; tab-width: 2;
# vim: set tabstop=2 softtabstop=2 shiftwidth=2 expandtab: 
#
=====================================================*/
          
#include <stdio.h>
#include <stdlib.h>

int p[7]={30,35,15,5,10,20,25};

int m[6+1][6+1];
int s[6+1][6+1];

void MATRIX_CHAIN_ORDER()
{
	int n=7-1;
	int i,l,j,k,q;
	for(i=1;i<=n;i++)
		m[i][i]=0;
	for(l=2;l<=n;l++)
	{
		for(i=1;i<=n-l+1;i++)
		{
			j=i+l-1;
			m[i][j]=1000000;
			for(k=i;k<=j-1;k++)
			{
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
}

void PRINT_OPTIMAL_PARENS(int i,int j)
{
	if(i==j)
		printf("A%d",i);
	else
	{
		printf("(");
		PRINT_OPTIMAL_PARENS(i,s[i][j]);
		PRINT_OPTIMAL_PARENS(s[i][j]+1,j);
		printf(")");
	}
}

int main()
{
	int i,j;
	printf("输入的矩阵维数如下：\n");
	for(i=0;i<6;i++)
		printf("A%d=%d*%d ",i+1,p[i],p[i+1]);
	printf("\n");
	printf("得到的矩阵为：\n");
	MATRIX_CHAIN_ORDER();
	for(i=1;i<=6;i++)
	{
		for(j=1;j<=6;j++)
			printf("%6d ",m[i][j]);
		printf("\n");
	}
	printf("\n加括号的顺序是\n");
	PRINT_OPTIMAL_PARENS(1,6);
	return 0;
}
