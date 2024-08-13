#include <bits/stdc++.h>

using namespace std;

int n; // 포켓몬의 수 
int m; // 문제 수 



map<int, string> poketmonsByNumber;
map<string,int> poketmonsByName;

vector<string>searchId;

string name;
string question;



int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> n >> m;
    for(int i=0; i<n; i++){
        cin>>name;
        poketmonsByNumber[i+1]=name;
        poketmonsByName[name]=i+1;
        
        
    }
    for(int i=0; i<m; i++){
         cin>>question;
            if (isdigit(question[0])) {
            int id = stoi(question);
            searchId.push_back(poketmonsByNumber[id]);
            }
            else{
            string id=to_string(poketmonsByName[question]);
            searchId.push_back(id);
            }
        };
        
        
         
         

       
         
    
    
    for(auto id : searchId) {
       
        cout<<id<<"\n";
    }
    

    
    
   
    return 0;
}