#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "Block.hpp"
#pragma once
using namespace std ;
// (H, W) for every pairs in my code & cout
// but (W,H) for output file 
class SlicingTree {
    public: 
        bool M1(int pos) ;
        bool M2(int pos) ;
        bool M3(int pos) ;

        vector<Block> blocks ; //Output Translation 
        vector<int> sequence ; //Slicingtree Representation 
        vector<int> sub_count ; //Property2 Checking
        float aspect_ratio = 0 ;
        
        SlicingTree(const vector<Block>& blocks) ; 

        float caculate_cost(int strategy=0) ;
        pair<float, float> caculate_cost_pair() ;
        pair<float, float> caculate_fit_aspect_ratio_pair() ;

        vector<float> caculate_ideal_result() ;

        int random_operand_index() ; //get random index which map to operand in sequence 
        int random_operator_index() ; //get random index which map to operator in sequence 

        void place() ; //place blocks by sequence 
        void initial() ;
        friend ostream& operator<<(ostream& os, SlicingTree st) ; //cout SlicingTree
} ;

extern float MinAspectRatio ;
extern float MaxAspectRatio ;
