#include "CircuitStructure.hpp"


Region::Region(const vector<float>& r){
    cor = r ;
}
ostream& operator<<(ostream& os,const Region& r){
    os << "(" << r.cor[0] << "," << r.cor[1] << "," << r.cor[2] << ","<< r.cor[3] << ")" ;
    return os ;
}

ostream& operator<<( ostream& os, const Block& b){
    os << b.block_name << " : " << b.through_block_net_num << ", "
    << b.through_block_edge_net_num << ", " << b.in_out_region << ", " << b.block_port_region << ", " << b.is_feedthroughable ;
    return os ;
}   

ostream& operator<<( ostream& os, const Net& b){
    os << b.ID << " : " << b.TX << ", " << b.RX << ", " << b.track << ", " << b.must_through << ", " << b.hmft_must_through << ", " << b.TX_coordinate
    <<", "<< b.RX_coordinate ;
    //<< b.RX << ", " << b.track << ", " << b.must_through << ", " << b.hmft_must_through << ", " << b.TX_coordinate
    //<< b.RX_coordinate ;
    return os ;
}   

float& Region::operator[] (const int& idx){
    return cor[idx] ;
}
float& Coordinate::operator[] (const int& idx){
    return cor[idx] ;
}
Coordinate::Coordinate(float x, float y){
    cor[0] = x ;
    cor[1] = y ;
}

ostream& operator<<(ostream& os,const Coordinate& r){
    os << "(" << r.cor[0] << "," << r.cor[1] << ")" ;
    return os ;
}
    