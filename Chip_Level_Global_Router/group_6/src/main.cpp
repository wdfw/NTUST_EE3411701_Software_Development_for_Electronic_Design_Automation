#include "Parser.hpp"
#include "Utils.hpp"
#include "CircuitStructure.hpp"
#include "NewCircuitStructure.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std ;

int main(int argc, char* argv[]){
    
    if(argc<5){
        cout << "Error: Invalid input.";
        return -1 ;
    }
    int tracksNum = stoi(argv[1]), maxnumumTracksNum=0 ;
    string fileName = "net.rpt";
    int isMute = 0 ;
    for(int i=5; i<argc; i++){
        if(string(argv[i])=="-f" && isMute!=2) isMute = 1 ;
        else if(string(argv[i])=="-s") isMute = 2 ;
        else fileName = string(argv[i]) ;
    } 

    DEF_Block def_blocks = Top_DEF_Parser(argv[2]) ;

    // cout << "\n---------------------------------\n";
    Blocks blocks = CFG_Parser(argv[3]) ;
    // cout << "\n---------------------------------\n";
    Nets nets = CM_Parser(argv[4]) ;
    // cout << "-------------------FINISH-------------------\n" ;

    for(auto& it : nets) maxnumumTracksNum = max(maxnumumTracksNum, it.second.track) ;
    if(maxnumumTracksNum>tracksNum) {
        cout << "Error: Invalid tracks/num (maxnimum tracks/num is larger than input).\n" << "Maxnimum tracks/num in file: " << maxnumumTracksNum << ".\n" ;
        return -1 ;
    }

    //CreateBlockTable(blocks,def_blocks) ;
    BlockTable  blocktable = CreateBlockTable(blocks,def_blocks) ;
    NetTable nettable = CreateNetTable(nets) ;
    NewMaze maze(blocktable,def_blocks.diearea[3],def_blocks.diearea[2]) ;
    //maze.mazeImage() ;
    maze.ASartRouterH(nettable,blocktable,tracksNum,isMute) ;
    maze.outputNets(nettable,fileName);
    return 0 ;
    
}