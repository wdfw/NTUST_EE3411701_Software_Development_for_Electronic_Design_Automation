#include "Parser.hpp" 

vector<string> Json_Scanner(const string& file_text){
    vector<string> tokens ;
    size_t anchor = 0 ;
    for(size_t pos=0; pos<file_text.size(); pos++){
        switch (file_text[pos]){
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
        case ',':
        case ':':
            tokens.push_back(file_text.substr(pos, 1)) ;
        case ' ':
        case '\n':
        case '\t':
            break ;
        case '\"':{
            pos++;
            anchor = pos ;
            while(file_text[pos]!='\"' && pos<file_text.size()) pos++;
            //cout << file_text.substr(anchor, pos-anchor)<<" " ;
            string temp = file_text.substr(anchor, pos-anchor) ;
            
            if(temp.find("is_feedthroughable")==0){
                tokens.push_back("is_feedthroughable") ;
                tokens.push_back(temp.substr(temp.find_first_of(':')+1)) ;
            }
            else tokens.push_back(temp) ;
            
            
        }    
        break ;
        default:
            if (isalnum(file_text[pos])){
                anchor = pos ;
                while( file_text[pos]=='.' || file_text[pos]=='_' || isalnum(file_text[pos]) && pos<file_text.size()) pos++ ;
                tokens.push_back(file_text.substr(anchor, pos-anchor)) ;
                pos--;
            }
            break ;
        }   
    }
    return tokens ;
}


typedef enum CFG_state {
    BLOCK_NAME,
    BLOCK_NAME_VALUE,
    THROUGH_BLOCK_NET_NUM,
    THROUGH_BLOCK_NET_NUM_VALUE,

    THROUGH_BLOCK_EDGE_NET_NUM,
    THROUGH_BLOCK_EDGE_NET_NUM_VALUE_BEGIN,
    THROUGH_BLOCK_EDGE_NET_NUM_VALUE_END,

    BLOCK_PORT_REGION,
    BLOCK_PORT_REGION_VALUE_BEGIN,
    BLOCK_PORT_REGION_VALUE_END,

    FEEDTHROUGHABLE,
    FEEDTHROUGHABLE_VALUE
}CFG_state ;

bool match_ID(const string& token){
    for(int i=0; i<token.size();i++)
        if(!isalnum(token[i]) && token[i]!='_' ) return false ;
    return true ;
}
bool match_number(const string& token){
    for(int i=0; i<token.size();i++)
        if(!isdigit(token[i]) && token[i]!='.') return false ;
    return true ;
}
bool match_bool(const string& token){
    if(token=="True" || token=="False" ) return true ;
    return false ;
}

Blocks CFG_Parser(const string& file_name){
    
    ifstream fp(file_name) ;
    CFG_state state = BLOCK_NAME ;
    Blocks result ;
    Block keep ;
    int edge_net_num_count = 0 ;
    int block_port_count = 0 ;
    string line ;
    while(getline(fp,line)){
        vector<string>tokens = Json_Scanner(line) ;
        for(auto& token : tokens){
            switch (state){
                case BLOCK_NAME :
                    if(token=="block_name") state = BLOCK_NAME_VALUE ;
                    break;
                case BLOCK_NAME_VALUE :
                    if(match_ID(token)){
                        keep.block_name = token ;
                        state = THROUGH_BLOCK_NET_NUM ;
                    }
                    break;
                case THROUGH_BLOCK_NET_NUM :
                    if(token=="through_block_net_num") state = THROUGH_BLOCK_NET_NUM_VALUE ;
                    break;
                case THROUGH_BLOCK_NET_NUM_VALUE :
                    if(match_number(token)){
                        keep.through_block_net_num = stoi(token) ;
                        state = THROUGH_BLOCK_EDGE_NET_NUM ;
                    }
                    break;
                case THROUGH_BLOCK_EDGE_NET_NUM :
                    if(token=="through_block_edge_net_num") state = THROUGH_BLOCK_EDGE_NET_NUM_VALUE_BEGIN ;
                    break;
                case THROUGH_BLOCK_EDGE_NET_NUM_VALUE_BEGIN :
                    if(token=="[") state = THROUGH_BLOCK_EDGE_NET_NUM_VALUE_END ;
                    break;
                case THROUGH_BLOCK_EDGE_NET_NUM_VALUE_END :
                    if(token=="]") state = BLOCK_PORT_REGION ;
                    else if(match_number(token)){
                        if(edge_net_num_count<4){
                            keep.in_out_region[edge_net_num_count] = stof(token) ;
                            edge_net_num_count ++ ;
                        }else{
                            keep.through_block_edge_net_num = stoi(token) ;
                            edge_net_num_count = 0 ;
                        }
                    }
                    break;
                case BLOCK_PORT_REGION :
                    if(token=="block_port_region") state = BLOCK_PORT_REGION_VALUE_BEGIN ;
                    break;
                case BLOCK_PORT_REGION_VALUE_BEGIN :
                    if(token=="[") state = BLOCK_PORT_REGION_VALUE_END ;
                    break;
                case BLOCK_PORT_REGION_VALUE_END :
                    if(token=="]") state = FEEDTHROUGHABLE ;
                    else if(match_number(token)){
                        keep.block_port_region[block_port_count] = stof(token) ;
                        block_port_count = block_port_count<3 ? block_port_count+1: 0;
                    }
                    break;
                case FEEDTHROUGHABLE :
                    if(token=="is_feedthroughable") state = FEEDTHROUGHABLE_VALUE ;
                    break;
                case FEEDTHROUGHABLE_VALUE :
                    if(match_bool(token)){
                        keep.is_feedthroughable=(token=="True") ;
                        result.insert(pair<string,Block>(keep.block_name, keep)) ;

                        state = BLOCK_NAME ;
                        //cout << keep<<"\n";
                        keep = Block() ;

                    }
                    break;
                default:
                    break;
            }
        }
    }
    // cout << result.size() << "\n" ;
    fp.close() ;
    
    return result ;
}

typedef enum CM_state {
    CM_ID, //0
    CM_ID_VALUE, //1
    
    CM_TX, //2
    CM_TX_VALUE, //3
    
    CM_RX, //4
    CM_RX_VALUE_BEGIN, //5
    CM_RX_VALUE_END, //6


    CM_TRACK, //7
    CM_TRACK_VALUE, //8
    
    CM_MUST_THROUGH, //9
    CM_MUST_THROUGH_VALUE_BEGIN, //10
        CM_MUST_THROUGH_ID, //11
        CM_MUST_THROUGH_REGION, //12
    CM_MUST_THROUGH_VALUE_END, //13

    CM_HMFT_MUST_THROUGH, //14
    CM_HMFT_MUST_THROUGH_VALUE_BEGIN, //15
        CM_HMFT_MUST_THROUGH_ID, //16
        CM_HMFT_MUST_THROUGH_REGION, //17
    CM_HMFT_MUST_THROUGH_VALUE_END, //18

    CM_TX_COORD, //19
    CM_TX_COORD_VALUE_BEGIN, //20
    CM_TX_COORD_VALUE_END, //21

    CM_RX_COORD, //22
    CM_RX_COORD_BEGIN, //23
        CM_RX_COORD_VALUE_BEGIN, //24
        CM_RX_COORD_VALUE_END, //25
    CM_RX_COORD_END  //26
}CM_state ;

Nets CM_Parser(const string& file_name){
    
    ifstream fp(file_name) ;
    CM_state state = CM_ID;
    Nets result ;
    Net keep ;
    int hmft_must_through_count = 0 ;
    int must_through_count = 0 ;
    int tx_count = 0 ;
    int rx_count = 0 ;

    string line ;
    
    while(getline(fp,line)){
        
        vector<string>tokens = Json_Scanner(line) ;
        for(auto& token : tokens){
            switch (state){
            case CM_ID:
                if(token=="ID") state=CM_ID_VALUE ;
                break;
            case CM_ID_VALUE:
                if(match_ID(token)){
                    keep.ID = token ;
                    state = CM_TX ;
                }
                break;  
            case CM_TX:
                if(token=="TX") state=CM_TX_VALUE ;
                break;
            case CM_TX_VALUE:
                if(match_ID(token)){
                    keep.TX = token ;
                    state = CM_RX ;
                }
                break;  
            case CM_RX:
                if(token=="RX") state=CM_RX_VALUE_BEGIN ;
                break;
            case CM_RX_VALUE_BEGIN:
                if(token=="[") {
                    keep.RX.clear() ;
                    state = CM_RX_VALUE_END ;
                }
                break;  
            case CM_RX_VALUE_END:
                if(token=="]") state = CM_TRACK ;
                else if(match_ID(token)) keep.RX.push_back(token) ; 
                break;  
            case CM_TRACK :
                if(token=="NUM") state = CM_TRACK_VALUE ;
                break ; 
            case CM_TRACK_VALUE :
                if(match_number(token)){
                    keep.track = stof(token) ;
                    state = CM_MUST_THROUGH ;
                }
                break ; 
            case CM_MUST_THROUGH :
                if(token=="MUST_THROUGH"){
                    keep.must_through.clear() ;
                    must_through_count = 0 ;
                    state = CM_MUST_THROUGH_VALUE_BEGIN ;
                }
                break ;
            case CM_MUST_THROUGH_VALUE_BEGIN :
                if(token=="{") state = CM_MUST_THROUGH_VALUE_END ;
                break ; 
            case CM_MUST_THROUGH_VALUE_END :
                if(token=="}") state = CM_HMFT_MUST_THROUGH ;
                else if(token=="["){
                    keep.must_through.push_back(pair<string,vector<Region>>{"",{}}) ;
                    must_through_count = 0 ;
                    state = CM_MUST_THROUGH_ID ;
                }
                break ; 
            case CM_MUST_THROUGH_ID :
                if(token=="]") state=CM_MUST_THROUGH_VALUE_END ;
                else if(match_ID(token)){
                    keep.must_through.back().first = token ;
                    state = CM_MUST_THROUGH_REGION ;
                }
                break ;
            case CM_MUST_THROUGH_REGION :
                if(token=="]") state=CM_MUST_THROUGH_VALUE_END ;
                else if(match_number(token)){
                    if(!must_through_count) keep.must_through.back().second.push_back(Region()) ;
                    keep.must_through.back().second.back()[must_through_count] = stoi(token) ;
                    must_through_count = must_through_count<3?must_through_count+1:0 ;
                }
                break ;
            case CM_HMFT_MUST_THROUGH :
                if(token=="HMFT_MUST_THROUGH"){
                    keep.hmft_must_through.clear() ;
                    hmft_must_through_count = 0 ;
                    state = CM_HMFT_MUST_THROUGH_VALUE_BEGIN ;
                }
                break ;
            case CM_HMFT_MUST_THROUGH_VALUE_BEGIN :
                if(token=="{") state = CM_HMFT_MUST_THROUGH_VALUE_END ;
                break ; 
            case CM_HMFT_MUST_THROUGH_VALUE_END :
                if(token=="}") state = CM_TX_COORD ;
                else if(token=="[") {
                    keep.hmft_must_through.push_back(pair<string,vector<Region>>{"",{}}) ;
                    hmft_must_through_count = 0 ;
                    state = CM_HMFT_MUST_THROUGH_ID ;
                }
                break ; 
            case CM_HMFT_MUST_THROUGH_ID :
                if(token=="]") state=CM_HMFT_MUST_THROUGH_VALUE_END ;
                else if(match_ID(token)){
                    keep.hmft_must_through.back().first = token ;
                    state = CM_HMFT_MUST_THROUGH_REGION ;
                }
                break ;
            case CM_HMFT_MUST_THROUGH_REGION :
                if(token=="]") state=CM_HMFT_MUST_THROUGH_VALUE_END ;
                else if(match_number(token)){
                    if(!hmft_must_through_count) keep.hmft_must_through.back().second.push_back(Region()) ;
                    keep.hmft_must_through.back().second.back()[hmft_must_through_count] = stoi(token) ;
                    hmft_must_through_count = hmft_must_through_count<3?hmft_must_through_count+1:0 ;
                }
                break ;
            case CM_TX_COORD :
                if(token=="TX_COORD") state = CM_TX_COORD_VALUE_BEGIN ;
                break ;
            case CM_TX_COORD_VALUE_BEGIN :                
                if(token=="[") {
                    tx_count = 0 ;
                    state = CM_TX_COORD_VALUE_END ;
                }
                break ;
            case CM_TX_COORD_VALUE_END :                
                if(token=="]") state = CM_RX_COORD ;
                else if(match_number(token)){
                    keep.TX_coordinate[tx_count] = stof(token) ;
                    tx_count = tx_count<1 ? tx_count+1 : 0 ;
                }
                break ;
            case CM_RX_COORD :
                if(token=="RX_COORD"){
                    rx_count = 0 ;
                    keep.RX_coordinate.clear() ;
                    state = CM_RX_COORD_BEGIN ;
                }
                break ;
            case CM_RX_COORD_BEGIN :
                if(token=="[") state=CM_RX_COORD_VALUE_BEGIN ;
                break ;
            case CM_RX_COORD_VALUE_BEGIN :
                if(token=="[") state=CM_RX_COORD_VALUE_END ;
                else if(token=="]"){
                    state=CM_ID ;
                    result.insert(pair<string,Net>(keep.ID, keep)) ;
                    keep = Net() ;
                }
                break ;
            case CM_RX_COORD_VALUE_END :
                if(token=="]"){
                    state=CM_RX_COORD_VALUE_BEGIN ;
                }else if(match_number(token)){
                    if(!rx_count) keep.RX_coordinate.push_back(Coordinate()) ;
                    keep.RX_coordinate.back()[rx_count] = stof(token) ;
                    rx_count = rx_count<1 ? rx_count+1 : 0 ;
                }
            default:
                break;
            }
        }
    }
    //  cout << result.size() <<"\n" ;
    fp.close() ;
    //for(auto& it : result) cout << it <<"\n" ;
    return result ;
}


vector<string> DEF_Scanner(const string& file_text){
    vector<string> tokens ;
    size_t anchor = 0 ;
    for(size_t pos=0; pos<file_text.size(); pos++){
        switch (file_text[pos]){
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
        case ',':
        case ':':
        case '-':
        case '+':
        case ';':
            tokens.push_back(file_text.substr(pos, 1)) ;
        case ' ':
        case '\n':
        case '\t':
            break ;
        case '\"':{
            pos++;
            anchor = pos ;
            while(file_text[pos]!='\"' && pos<file_text.size()) pos++;
            //cout << file_text.substr(anchor, pos-anchor)<<" " ;
            string temp = file_text.substr(anchor, pos-anchor) ;
            tokens.push_back(temp) ;
        }    
        break ;
        default:
            if (isalnum(file_text[pos])){
                anchor = pos ;
                while( file_text[pos]=='.' || file_text[pos]=='_' || isalnum(file_text[pos]) && pos<file_text.size()) pos++ ;
                tokens.push_back(file_text.substr(anchor, pos-anchor)) ;
                pos-- ;
            }
            break ;
        }   
    }
    return tokens ;
}

typedef enum TOP_state {
    TOP_DESIGN, //0
        TOP_DESIGN_VALUE, //1

    TOP_MICRONS, //2
        TOP_MICRONS_VALUE, //3

    TOP_DIEAREA, //4
        TOP_DIEAREA_VALUE, //5

    TOP_COMPONENTS, //6
    TOP_COMPONENTS_NUMBER, //7
    TOP_COMPONENTS_BEGIN, //8
        TOP_COMPONENTS_NAME, //9
        TOP_COMPONENTS_FILE, //10
        TOP_COMPONENTS_VALUE, //11
        TOP_COMPONENTS_ORIENT, //12


    TOP_REGIONS, //13
    TOP_REGIONS_NUMBER, //14
    TOP_REGIONS_BEGIN, //15
        TOP_REGIONS_NAME, //16
        TOP_REGIONS_VALUE, //17
    TOP_REGIONS_END, //18


}TOP_state ;

typedef enum DEF_state{
    DEF_DESIGN, //0
        DEF_DESIGN_VALUE, //1

    DEF_MICRONS, //2
        DEF_MICRONS_VALUE, //3

    DEF_DIEAREA, //4
        DEF_DIEAREA_VALUE, //5
}DEF_state ;

vector<Coordinate> DEF_Parser(const string& file_name){
    ifstream fp(file_name) ;
    std::stringstream buffer;
    
    buffer << fp.rdbuf();
    fp.close() ;
    vector<string> tokens = DEF_Scanner( buffer.str() ) ;

    vector<Coordinate> cordinates ;
    DEF_state state = DEF_DESIGN ;
    float micron = 0 ;
    int cor_count = 0 ;
    
    for(auto& token : tokens){
        switch (state){
            
            case DEF_DESIGN :
                if(token=="DESIGN") state = DEF_DESIGN_VALUE ;
                break;
            case DEF_DESIGN_VALUE :
                if(match_ID(token)){
                    //dblock.first = token ;
                    state = DEF_MICRONS ;
                }
                break;        
            case DEF_MICRONS :
                if(token=="MICRONS") state = DEF_MICRONS_VALUE ;
                break;
            case DEF_MICRONS_VALUE :
                if(match_number(token)){
                    micron = stof(token) ;
                    state = DEF_DIEAREA ;
                }
                break;   
            case DEF_DIEAREA :
                if(token=="DIEAREA") state = DEF_DIEAREA_VALUE ;
                break;
            case DEF_DIEAREA_VALUE :
                if(match_number(token)){
                    if(cor_count==0){
                        cordinates.push_back(Coordinate()) ;
                        
                        cordinates.back()[0] = stof(token)/micron ;
                        cor_count ++ ;
                    }else{
                        cordinates.back()[1] = stof(token)/micron ;
                        cor_count = 0 ;
                    }
                }
            default:
                break;
        }    
    }
    return cordinates ;
}
DEF_Block Top_DEF_Parser(const string& dir_name){
    ifstream fp(dir_name + "/chip_top.def") ;
    std::stringstream buffer;
    
    buffer << fp.rdbuf();
    fp.close() ;

    vector<string> top_tokens = DEF_Scanner( buffer.str() ) ;
    
    DEF_Block result ;
    TOP_state state = TOP_DESIGN ;
    pair<string, vector<Coordinate>> components_keep ;
    pair<string, Region> regions_keep ;
    Coordinate keep ;
    float micron = 0 ;
    int count = 0 ;
    int component_count = 0 ;
    int region_count = 0 ;
    for(auto& token : top_tokens){
        switch (state){
            case TOP_DESIGN :
                if(token=="DESIGN") state = TOP_DESIGN_VALUE ;
                break;
            case TOP_DESIGN_VALUE :
                if(match_ID(token)){
                    result.name = token ;
                    state = TOP_MICRONS ;
                }
                break;    
            case TOP_MICRONS :
                if(token=="MICRONS") state = TOP_MICRONS_VALUE ;
                break;       
            case TOP_MICRONS_VALUE :
                if(match_number(token)){
                    micron = stof(token) ;
                    state = TOP_DIEAREA ;
                }
                break;       
            case TOP_DIEAREA :
                if(token=="DIEAREA") state = TOP_DIEAREA_VALUE ;
                break;    
            case TOP_DIEAREA_VALUE :
                if(match_number(token)){
                    result.diearea[count++] = stof(token)/micron ;
                }else if(token=="COMPONENTS"){
                    state = TOP_COMPONENTS_NUMBER ;
                    count = 0 ;
                }
                break;     
            case TOP_COMPONENTS_NUMBER :
                if(match_number(token)){
                    component_count = stoi(token) ;
                    state = TOP_COMPONENTS_BEGIN;
                }
                break ;
            case TOP_COMPONENTS_BEGIN :
                if(token=="-") state = TOP_COMPONENTS_NAME ;
                else if(token=="END") state = TOP_REGIONS ;
                break;   
            case TOP_COMPONENTS_NAME :
                if(match_ID(token)){
                    components_keep.first = token ;
                    state = TOP_COMPONENTS_FILE ;
                }
                break ;
            case TOP_COMPONENTS_FILE :
                if(match_ID(token)){
                    components_keep.second = DEF_Parser(dir_name +"/" + token + ".def") ;
                    result.components.push_back(components_keep) ;
                    state = TOP_COMPONENTS_VALUE ;
                }
                break ;
            case TOP_COMPONENTS_VALUE :
                if(match_number(token)){
                    keep[count++] = stof(token)/micron ;
                    if(count==2){
                        result.bases.push_back(keep) ;
                        state = TOP_COMPONENTS_ORIENT ;
                        count = 0 ;
                    }
                }
                break ;
            case TOP_COMPONENTS_ORIENT:
                if(match_ID(token)){
                    result.orients.push_back(token) ;
                    state = TOP_COMPONENTS_BEGIN ;
                }
            case TOP_REGIONS :
                if(token=="REGIONS") state = TOP_REGIONS_NUMBER ;
                break ;
            case TOP_REGIONS_NUMBER:
                if(match_number(token)){
                    region_count = stoi(token) ;
                    state = TOP_REGIONS_BEGIN ;
                }
                break ;
            case TOP_REGIONS_BEGIN :
                if(token=="-") state = TOP_REGIONS_NAME ;
                else if(token=="END") state = TOP_REGIONS_END ;
                break ;
            case TOP_REGIONS_NAME :
                if(match_ID(token)){
                    regions_keep.first = token ;
                    state = TOP_REGIONS_VALUE ;
                }
                break ;
            case TOP_REGIONS_VALUE :
                if(match_number(token)){
                    regions_keep.second[count++] = stof(token)/micron ;
                    if(count==4){
                        count = 0 ;
                        result.regions.push_back(regions_keep) ;
                        state = TOP_REGIONS_BEGIN ;
                        
                    }
                }
                break ;
            default:
                break;
        }
    }
    /*
    
    cout <<"Design" << result.name << "\n" ;
    cout << "--------------COmponents\n-------------";
    for(int i=0; i<result.components.size(); i++){
        cout << result.components[i] << "\n" << result.bases[i] << " " << result.orients[i] << "\n" ; 
    }
    cout << "--------------Regions\n-------------";
    for(int i=0; i<result.regions.size(); i++){
        cout << result.regions[i] << "\n"  ; 
    }*/
    // cout << result.components.size() << " " << result.regions.size() <<"\n" ;
    return result ;
}
