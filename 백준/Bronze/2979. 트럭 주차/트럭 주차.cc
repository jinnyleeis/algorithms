#include <bits/stdc++.h>


using namespace std;

int a,b,c;
int carCame[3];
int carLeft[3];
vector<int> timeNum;
vector<int> truckNum;
int sum=0;


vector<pair<int, int>> vec;



int main(){


    
    // 가격
    cin >> a >> b >> c;
    // 도착한 시각과 떠난 시각 
    for(int i=0; i<3; i++){
    cin >> carCame[i] >> carLeft[i];
    timeNum.push_back(carCame[i]);
    timeNum.push_back(carLeft[i]);


 

    }
    
   
sort(timeNum.begin(),timeNum.end());

    timeNum.erase(unique(timeNum.begin(), timeNum.end()), timeNum.end());
  
   // 트럭 개수를 시간 간격 크기만큼 초기화
    truckNum.resize(timeNum.size(), 0);

 
 
    
    for(int i=0; i<timeNum.size(); i++){
        
        int timeLength;
        
       if(i==timeNum.size()-1)timeLength=0;
       else{
        timeLength=timeNum[i+1]-timeNum[i];}
       
        

      
        for(int truck=0; truck<3; truck++){
            // 트럭별로 해당 슬롯에 속해 있는지 확인하기 
            if(carCame[truck]<= timeNum[i] && carLeft[truck]>timeNum[i]){
               truckNum[i]++;// 해당 간격의 트럭 개수 추가 
            }
        }
        
        if(truckNum[i]==1){sum+=a*1*timeLength;}
        else if(truckNum[i]==2){sum+=b*2*timeLength;}
       else if(truckNum[i]==3){sum+=c*3*timeLength;}
        
        
    }
    

cout << sum << endl;


    return 0;
}