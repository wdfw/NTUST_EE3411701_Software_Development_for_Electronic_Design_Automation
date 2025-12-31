#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include "Utils.hpp"
using namespace std;

class Coordinate{
    public :
        vector<float> cor = {-1,-1} ;
        Coordinate(float x, float y) ;
        Coordinate(){};
        friend ostream& operator<<(ostream& os,const Coordinate& r);
        float& operator[] (const int& idx) ;
} ;
class Region{
    public :
        vector<float> cor = {-1,-1,-1,-1} ;
        Region(const vector<float>& r) ;
        Region(){};
        friend ostream& operator<<(ostream& os,const Region& r);
        float& operator[] (const int& idx) ;
} ;

class Block{
    public :
        string block_name = "";

        int through_block_net_num = 0;
        
        int through_block_edge_net_num = 0 ; 
        Region in_out_region = Region(); 

        Region block_port_region = Region(); 
        
        bool is_feedthroughable = false;

        Block(){};
        friend ostream& operator<<( ostream& os, const Block& b) ;

};

class Net{
    public :
        string ID ;
        string TX ;
        vector<string> RX ;
        int track ;
        vector<pair<string,vector<Region>>> must_through ;
        vector<pair<string,vector<Region>>> hmft_must_through ;
        Coordinate TX_coordinate ; 
        vector<Coordinate> RX_coordinate ; 
        Net(){} ;
        friend ostream& operator<<( ostream& os, const Net& b) ;
} ;

class DEF_Block{
    public :
        string name ;
        Region diearea ;
        vector<pair<string,vector<Coordinate>>> components ;
        vector<Coordinate> bases ; 
        vector<string> orients ; 
        vector<pair<string,Region>> regions ;

} ;

typedef map<string, Block> Blocks ;
typedef map<string, Net> Nets ;
