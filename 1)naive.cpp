#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
using namespace std;

bool check(string P,string T){
    int i=0,j=0,three=0;
    while(i<T.size()){
        i=three;
        while(T[i]==P[j]){
            j++;
            i++;
            if(j==P.size()){
                return true;
            }
        }
        three++;
    }
    return false;
}
//start position printer
void check2(string P, string T,ofstream& ofile){
    int i=0,j=0,t;
    while(i<T.size()){
        j=0;
        i=t;
        while(T[i]==P[j]){
            j++;
            i++;
            if(j==P.size()){
                ofile<<t<<",";
            }
        }
        t++;
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
        check2(P,T,t);
        auto end=std::chrono::steady_clock::now();
        total+=current;
        t<<"\n";
    }
    total=std::chrono::nanoseconds::zero();
    f<<total.count()/times<<",";
    std::cout<<total.count()/times<<",";    
    f<<"\n";
}