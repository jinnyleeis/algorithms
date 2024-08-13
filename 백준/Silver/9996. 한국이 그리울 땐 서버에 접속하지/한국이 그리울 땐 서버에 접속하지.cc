#include <bits/stdc++.h>


using namespace std;



int num;
string pattern;
string fileName;
int asteridIndex=0;

int isValid;

vector<char> patternFront;
vector<char> patternBack;
vector<string> output;

int checkValid(string fileName){
    
 
    string fileNameReverse;
    fileNameReverse=fileName;
    reverse(fileNameReverse.begin(),fileNameReverse.end());
    
    if(patternFront.size()+patternBack.size()>fileName.size())return 0;
    
       for(size_t i = 0; i<patternFront.size(); i++){
       if(fileName[i]==patternFront[i])continue;
       else{return 0;}
       
   }

   for(size_t i = 0; i<patternBack.size(); i++){
       if(fileNameReverse[i]==patternBack[i])continue;
       else{return 0;}
       
   }
   
   return 1;

 
}



int main()
{
    



cin>>num;
cin>>pattern;





for(size_t i=0; i<pattern.size(); i++){
    
    if(pattern[i]=='*'){asteridIndex=i; 
    continue; // 이번껀 패턴으로 저장 안하고, 다음 문자로 넘어가기 위해
    }
    if(asteridIndex==0){
        patternFront.push_back(pattern[i]);
    }else if(asteridIndex!=0){
          patternBack.insert(patternBack.begin(), pattern[i]);
    }
        
    }
    
    
   for(int i = 0; i<num; i++){
    cin>>fileName;
   isValid=checkValid(fileName);
   if(isValid==0){output.push_back("NE");}
   else if(isValid==1){output.push_back("DA");}
   }
  
  
  for(auto o:output){cout<<o<<"\n";}
      
  
    



    return 0;
}