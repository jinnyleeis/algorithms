#include <bits/stdc++.h>
using namespace std;

int num=666;
int n;
int cnt;

int main()
{
  
  
  cin>>n;
  
  while(true){
      
     if(to_string(num).find("666")!=string::npos){
         cnt++;
     }
     if(cnt==n)break;
     
     num++;
      
  }
  
  
      cout<<num<<"\n";
    
    
    return 0;
}