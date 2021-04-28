#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include<map>
using namespace std;
typedef map<char,int> MAP;
string prefix(string T,int size){
    return T.substr(0,size);
}
string suffix(string T,int size){
    return T.substr(T.size()-size,size);
}
bool comparator(string A,string B){
    for(int i=0;i<A.size();i++){
        if(A[i]!=B[i]){
            return false;
        }
    }
    return true;
}
//returns the length of the longest prefix of T, which is also a suffix of P
int sigma(string P,string T){
    if(P.size()>T.size()) return -1;

    int i=0;
    for(i=P.size();i>-1;i--){
        // cout<<i<<")"<<prefix(P,i)<<endl<<"\t"<<suffix(T,i)<<endl;
        if(comparator(suffix(T,i),prefix(P,i))){
            break;
        }
    }
    
    return i;
}
//transition function 
int delta(string T,char a){
    return sigma(T,(T.substr(0,T.size()-1))+a);
}
//make alphabet
char *alphabet(string T,int &size){
    bool temp[256];
    for(int i=0;i<256;i++){
        temp[i]=false;
    }
    int counter=0;
    for(int i=0;i<T.size();i++){
        temp[(int)T[i]]=true;
        counter++;
    }
    char *myarr = new char[counter];
    size=counter; 
    for(int i=0;i<256;i++){
        if(temp[i]) myarr[--counter]=(char)i;
    }
    return myarr;
}
//transition table
unsigned int *table(string P,char *alphab,int size){
    unsigned int *myarr = new unsigned int[size*(P.size())];
    
    for(int i=0;i<P.size();i++){
        for(int j=0;j<size;j++){
            *(myarr+i*size+j)=delta(P.substr(0,i+1),alphab[j+1]);        
        }
    }
    return myarr;
}
//matcher using delta itself
void process(string T,string P){
    int state=0,n=T.size(),m=P.size();
    for(int i=0;i<=n; i++){
        state=delta(P.substr(0,state+1),(char)T[i]);
        if(state == m){
            cout<<"Matched at "<<i<<"\n";
        }
    }
}
//matcher using table
void check(string P,string T,ofstream& ofile){
    int alpha_size=0;
    char *alphab=alphabet(P,alpha_size);
    MAP alpha;
    for(int i=0;i<alpha_size;i++){
        alpha.insert(pair<char,int>((char)alphab[i],i));
    }
    unsigned int *transtable=table(P,alphab,alpha_size);
    int state=0,n=T.size(),m=P.size();
    int i=0;
    for(i=0;i<n;i++){
        cout<<"ALPHA! "<<alpha[(char)T[i]]<<"\n";
        if(alpha[(char)T[i]]==0){
           state=0; 
        }
        else{
            state=*(transtable+state*alpha_size+(alpha[(char)T[i]]-1));
        }
        if(state==m){
            ofile<<"Matched at "<<i-(m-1)<<endl;
            state=0;
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