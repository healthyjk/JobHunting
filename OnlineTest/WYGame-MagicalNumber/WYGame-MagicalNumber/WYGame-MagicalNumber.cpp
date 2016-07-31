// WYGame-MagicalNumber.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>  
#include <string.h>  
#include <algorithm>  

using namespace std;  

int dp[20][2][2][7];
int digit[20];  

long long dfs(int len, bool state, int has, int sum, bool fp)  
{  
   if(!len)
   {
      if(has == 1 && sum == 0)  
      {
         return 1;
      }
      else return 0;  
   }

   if(!fp && dp[len][state][has][sum] != -1)  
   {
      return dp[len][state][has][sum]; 
   }

   long long ret = 0 , fpmax = fp ? digit[len] : 9;  
   for(int i = 0; i <= fpmax; i++)  
   {  
      // 不含18
      if(state && i == 8)  
         continue;  

      //含有2，3，5
      int prehas = has;
      int presum = sum;
      sum *= 10;
      sum += i;
      sum %= 7;
      
      if(!has && (i == 2 || i == 3 || i == 5))
      {
         has = 1;
      }

      ret += dfs(len - 1,i == 1, has, sum, fp && i == fpmax);  
      has = prehas;
      sum = presum;
   }  

   if(!fp)  
   {
      dp[len][state][has][sum] = ret;  
   }

   return ret; 
}  

long long f(long long n)  
{  
   long long len = 0;  
   while(n)  
   {  
      digit[++len] = n % 10;  
      n /= 10;  
   } 
   return dfs(len,false, 0, 0, true);  
}  

int main()  
{  
   long long a,b;  
   memset(dp, -1, sizeof(dp));  

   while(scanf_s("%lld %lld", &a, &b) != EOF)  
   {   
      printf("%lld\n", f(b) - f(a - 1));  
   }  

   return 0;  
} 