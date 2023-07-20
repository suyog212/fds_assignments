#include<iostream>
#include<fstream>

using namespace std;

int main(){
    string st;
    ifstream in("sample.txt");
    getline(in,st);
    cout<<st;
}