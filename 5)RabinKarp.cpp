#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
using namespace std;

long power(int num,int pow){
    while(pow>0){
        num*=10;
        pow--;
    }
    return num;
}
int hash1(string T){
     int val=0;
     for(int i=0;i<T.size();i++){
         val+=power(T[i],(T.size()-i-1));
     }
     return val;
}
int hash2(string T,int from,int to){
    int val=0,j=to-from;
    for(int i=from;i<to;i++){
        val+=power(T[i],j-1);
        j--;
    }
    return val;
}

void check(string P,string T,ofstream& ofile){
    int start=0,i=0,end=P.size(),temp=power(1,P.size()-1);
    long ahash=hash2(T,0,P.size()),bhash=hash1(P);
    while(start<T.size()){
        if(bhash==ahash){
            for(i=0;i<P.size();i++){
                if(P[i]!=T[start+i]){
                    break;
                }
            }
            if(i==P.size()){
                ofile<<"Matched at "<<start<<"\n";
                break;
            }
            ahash-=temp*T[start++];
            ahash*=10;
            ahash+=T[end++];
        }
        else{
            ahash-=temp*T[start++];
            ahash*=10;
            ahash+=T[end++];
        }
    }
}

int main(){
    std::fstream f("C:\\data.csv");
    std::ofstream t("C:\\findings.txt");
    unsigned int times=1000;
    std::chrono::nanoseconds total(0);
    string T="";
    string P="";
    std::chrono::nanoseconds current(0);
    for(unsigned int onetime=0;onetime<times;onetime++){
        current=std::chrono::nanoseconds::zero();
        auto start=std::chrono::steady_clock::now();
        check(P,T,t);
        auto end=std::chrono::steady_clock::now();
        total+=current;
        t<<"\n";
    }
    total=std::chrono::nanoseconds::zero();
    f<<total.count()/times<<",";
    std::cout<<total.count()/times<<",";    
    f<<"\n";
}