#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>
#include "Utils.hpp"
#include "CircuitStructure.hpp"
#include "DrawBmp.hpp"
using namespace std;

class NewCoordinate ;
class NewRegion ;
class NewNet ;
class NewBlock ;

typedef map<string, NewBlock> BlockTable ;
typedef vector<NewCoordinate> NewCoordinates ;

typedef map<string, NewNet> NetTable ;

void operator+=(NewCoordinates& cordinates, NewCoordinate position);

class NewCoordinate{
    private :
        vector<float> cordinate = {-1,-1} ;
    public :
        NewCoordinate(Coordinate cordinate) ;
        NewCoordinate(vector<float> cordinate) ;
        NewCoordinate(float x, float y) ;
        NewCoordinate(){};

        NewCoordinate operator+( NewCoordinate cordinate2) ;
        NewCoordinate operator-( NewCoordinate cordinate2) ;
        NewCoordinate operator*( NewCoordinate cordinate2) ;
        NewCoordinate operator/( NewCoordinate cordinate2) ;

        NewCoordinate operator+(float n) ;
        NewCoordinate operator-(float n) ;
        NewCoordinate operator*(float n) ;
        NewCoordinate operator/(float n) ;

        //bool operator==(NewCoordinate& a, NewCoordinate& b) ;
        
        bool operator!(void) ;
        float& operator[] (int idx) ;
        friend ostream& operator<<(ostream& os, NewCoordinate newCordinate) ;
} ;
class NewRegion{
    private :
        vector<float> region = {-1,-1,-1,-1} ;
    public :
        NewRegion(NewCoordinate cordinateLB, NewCoordinate cordinateUR) ;
        NewRegion(Region region) ;
        NewRegion(vector<float> region) ;
        NewRegion(float xl, float yb, float xr, float yt) ;
        NewRegion(){};

        NewRegion operator+(NewRegion region2) ;
        NewRegion operator-(NewRegion region2) ;
        NewRegion operator*(NewRegion region2) ;
        NewRegion operator/(NewRegion region2) ;

        NewRegion operator+(float n) ;
        NewRegion operator-(float n) ;
        NewRegion operator*(float n) ;
        NewRegion operator/(float n) ;

        NewRegion operator+(NewCoordinate cordinate2) ;
        NewRegion operator-(NewCoordinate cordinate2) ;
        NewRegion operator*(NewCoordinate cordinate2) ;
        NewRegion operator/(NewCoordinate cordinate2) ;
        
        bool operator!(void) ;
        float& operator[] (int idx) ;
        friend ostream& operator<<(ostream& os, NewRegion newRegion) ;
} ;

class NewNet{
    public :
        string ID ;
        string TX ;
        vector<string> RX ;
        int num ;
        map<string, vector<NewRegion>> mustThrough ;
        map<string, vector<NewRegion>> hmftMustThrough ;
        NewCoordinate TXCoordinate ; 
        vector<NewCoordinate> RXCoordinate ; 
        vector<vector<NewCoordinate>> path ;
        NewNet(string ID, string TX, vector<string> RX, int num=0,map<string, vector<NewRegion>> mustThrough={},
               map<string, vector<NewRegion>> hmftMustThrough={}, NewCoordinate TXCoordinate=NewCoordinate(), 
               vector<NewCoordinate> RXCoordinate=vector<NewCoordinate>{}) ;
        NewNet(Net net) ;
        NewNet(){} ;
        
        friend ostream& operator<<( ostream& os, const NewNet& newNet) ;
       
} ;

class NewBlock{
    public :
        string ID ;
        int gridCode ;
        NewCoordinates blockRegion ; //region = diearea + position
        NewCoordinates dieRegion ;
        NewCoordinate position ;
    
        int throughBlockNetNum = 0 ;
        int throughEdgeNetNum = 0 ;
        bool feedthroughable = false ;
        bool isRegion = false ;
        NewRegion inOutRegion = NewRegion() ;
        NewRegion portRegion = NewRegion() ;

        NewBlock(){} ;
        NewBlock(string ID, NewCoordinates dieRegion, NewCoordinate position,
                 int throughBlockNetNum=0, int throughEdgeNetNum=0, bool feedthroughable=false, bool isRegion=false, 
                 NewRegion inOutRegion=Region(), NewRegion portRegion=NewRegion()) ;

        friend ostream& operator<<(ostream& os, NewBlock newBlock) ;      
};

class NewMaze{
    private :
        void bruteForcePolygon(NewBlock& black, int value=1);
        void polygonToRetangle(NewBlock& coordinates, int value=1) ;

    public :
        class Cost{
            public :
                int total ;
                int startLength ;
                int endLength ;
                int trackCost ;
                NewCoordinate parent ;
                Cost(int startLength=0, int endLength=0, int trackCost=0, NewCoordinate parent=NewCoordinate()) ;
                Cost() ;
                void setStartLength(int newValue) ;
                void setEndLength(int newValue) ;
                void setTrackCost(int newValue) ;
                friend ostream& operator<<(ostream& os, NewBlock newBlock) ;
                bool operator>(const Cost& c2) ;
                
        } ;
        vector<vector<int>> grid ;
        //vector<vector<int>> trackGrid ;
        int h = 0 ;
        int w = 0 ;
        int gcellWidth = 1 ;
        NewMaze(BlockTable& blockTable, int height, int width) ;
        NewMaze(){} ; 

        void ASartRouterH(NetTable& nets, BlockTable& blocks, int tracksNum, int isMute=0) ;

        void mazeImage(string fileName="output.bmp") ;
        void drawLine(vector<vector<NewCoordinate>>& segement, string fileName="output.bmp",
                    NewCoordinate rx=NewCoordinate(), vector<NewCoordinate> txs={}) ;
        void drawAll(NetTable& nets,BlockTable& blocks,string fileName="output.bmp") ;
        
        void gcellInitialize(float gcellWidth=1) ;
        void outputNets(NetTable& nets, string fileName = "net.rpt") ;
        
        
} ;

BlockTable CreateBlockTable(Blocks& blocks, DEF_Block& defBlock) ;
NetTable CreateNetTable(Nets& nets) ;