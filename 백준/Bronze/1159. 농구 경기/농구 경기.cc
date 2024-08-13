#include <bits/stdc++.h>


using namespace std;

map<char, int> m; 
vector<char> resultVector;

void select(string* array,int num){
    
  for(int i=0; i<num; i++){
          m[array[i][0]]++;
      }
      
        for(auto c:m) {

        if(c.second>=5){
        resultVector.push_back(c.first);
        }


    }
    
   
  

    
}



int main()
{
    

int num;

cin >> num;

string names[num];

// 일단 전역 변수가 아니니까, ' '로 초기화 시키자 

for(int i=0; i<num; i++){
   cin>> names[i]; // 이름을 입력받는다. 
}

select(names,num);


 if(resultVector.size()==0){
        cout<<"PREDAJA"<<endl;
    }
   else{
       
      for(char i:resultVector){cout<<i<<"";}
   }


    return 0;
}