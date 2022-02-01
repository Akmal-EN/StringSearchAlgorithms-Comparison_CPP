#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include<map>
using namespace std;

void check(string P,string T,ofstream& ofile){
        if(P==""||T=="") return ;
        
        int len1 = T.length(), len2 = P.length();
        
        if(len1<len2) return ;
        
        map<char, int> mapping;
        
        for(int i = 0;i<P.size();++i)
            mapping[P[i]] = i;

        int i = 0;
        
        while(i<=len1-len2){
            int j = 0;
            for(;j<len2;++j){
                if(T[i+j] != P[j]){
                    char c = T[i+len2];
                    if(mapping.find(c)==mapping.end()) i += len2+1;
                    else i += len2-mapping[c];
                        break;
            }
        }
            if(j == len2){
                ofile<<"Matched at "<<i<<endl;
                i+=P.size();
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
