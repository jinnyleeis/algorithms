#include <bits/stdc++.h>


using namespace std;


string str;
int counterIndex;

int checkPalindrom(){
    
      cin >> str;
      

    
    if(str.size()%2==0){
        
                  

       
        for(int i=0; i<=(str.size()/2-1); i++ ){
             
             counterIndex=str.size()-1-i;
            if(str[i]==str[counterIndex]){continue;}
            else{return 0;}
        }
        
         
            
        }
    else if(str.size()%2==1) {
        
          for(int i=0; i<=((str.size()-1)/2); i++){
        counterIndex=str.size()-1-i;
        if(str[i]==str[counterIndex]){continue;}
            else{return 0;}

          }
          
          
        
       }
       
        return 1;
   
    
    
    
}

int main()
{
  

cout << checkPalindrom() <<endl;
    return 0;
}