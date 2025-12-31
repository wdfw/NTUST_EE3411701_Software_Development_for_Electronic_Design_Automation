#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std ;

template <typename T>
ostream& operator<<(ostream& os, vector<T> v){
    os << "[ " ;
    for(auto &it : v) os << it << " " ; 
    os << " ]" ;
    return os ;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> v){
    os << v.first << " " << v.second ; 
    return os ;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, map<T1,T2> m){
    os << "[ " ;
    for(auto& it : m) os << "(" << it.first << "," << it.second << ") " ; 
    os << "]" ;
    return os ;
}


template <typename T>
class Heap {
    public :
        vector<T> heap ;
        Heap(vector<T> heap){
            this->heap = heap ;
            make_heap(this->heap.begin(), this->heap.end()) ;
        }
        void push(T v){
            heap.push_back(v) ;
            push_heap(heap.begin(), heap.end()) ;
        }

        T pop(){
            pop_heap(heap.begin(), heap.end()) ;
            return heap.pop_back() ;
        }

} ;


template <typename T>
ostream& operator<<(ostream& os, Heap<T> heap){
    os << "[ " ;
    for(auto &it : heap) os << it << " " ; 
    os << " ]" ;
    return os ;
}

string ShowBool(bool b) ;