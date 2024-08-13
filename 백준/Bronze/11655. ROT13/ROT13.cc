#include <bits/stdc++.h>


using namespace std;




string stringInput;
string stringOutput;


int main()
{
    




    getline(cin, stringInput);  // 공백을 포함한 전체 줄 입력
   for(int i=0; i<stringInput.size(); i++){
       
        
 if(isupper(stringInput[i])){
    int originIndex= stringInput[i]-'A';
    int encodeIndex=(originIndex+13)%26;
     stringOutput+='A'+encodeIndex;
     
 }else if(islower(stringInput[i])){ 
 int originIndex= stringInput[i]-'a';
    int encodeIndex=(originIndex+13)%26;
     stringOutput+='a'+encodeIndex;
     
 }
 else {stringOutput+=stringInput[i];}

}
 




   cout<<stringOutput<<endl;




    return 0;
}