#include <iostream>
#include <vector> 
#pragma once
using namespace std ;

class Block{
    public :
        string name = "" ; //Block ID
        int h = 0 ; //Height
        int w = 0 ; //Width
        int x = 0 ; //X-Cordinate
        int y = 0 ; //Y-Cordinate
        Block(string name, int h, int w, int x, int y) ;
        Block() ;
} ;

ostream& operator<<(ostream& os, Block b) ;

template <typename T> //Cout Vector
ostream& operator<<(ostream& os, vector<T> v){
    for(auto &it : v) os << it << " " ;
    cout << "% "; 
    return os ;
} 

template <typename T1, typename T2> //Cout Pair
ostream& operator<<(ostream& os, pair<T1,T2> p){
    os << "(" <<  p.first << "," << p.second << ") " ;
    return os ;
} 

template <typename T> //Combine 2 vectors A & B, you will get C = A+B.
vector<T> combine_vector(vector<T>& a, vector<T>& b){
    vector<T> c(a.size()+b.size()) ;
    for(int i=0; i<a.size(); i++) c[i] = a[i] ;
    for(int i=0; i<b.size(); i++) c[i+a.size()] = b[i] ;
    return c ;
} 
