#include<string>
#include<iostream>
#include<chrono>
#include<fstream>
using namespace std;

void lps(string T,unsigned int *table){
    int i=1,j=0;
    table[0]=0;
    while(i<T.size()){
        j=0;
        while(T[i]==T[j]){
            j++;
            table[i]=j;
            i++;
        }
        if(j==0){
            table[i]=0;
            i++;
        }
    }
}
// bool check(string P,string T){
//     int i=0,j=0,temp=0;
//     string lps[]=;
//     while(){
//         while(){
//             if(j=size){
//             }
//         }
//     }
//     return 0;
// }
void check(string P, string T,ofstream& ofile){
    int i=0,j=0;
    unsigned int *table=new unsigned int[P.size()];
    lps(P,table);
    while(i<T.size()){
        while(T[i]==P[j]){
            j++;
            i++;
            if(j==P.size()){
                ofile<<"Matched at "<<i-P.size()<<"\n";
            }
            while(T[i]!=P[j]&&j>0){
                j=table[j-1];
            }
        }
        i++;
    }
    delete table;
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