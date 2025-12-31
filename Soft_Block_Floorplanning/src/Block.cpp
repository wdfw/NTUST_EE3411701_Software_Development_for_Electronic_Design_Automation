#include "Block.hpp"

Block::Block(string name, int h, int w, int x, int y){
    this->name = name ;
    this->h = h ;
    this->w = w ;
    this->x = x ;
    this->y = y ;
}
Block::Block(){} 

ostream& operator<<(ostream& os, Block b){
    os << b.name << " : (" << b.x << "," << b.y << ") " << b.w << " " << b.h  ; 
    return os ;
}
