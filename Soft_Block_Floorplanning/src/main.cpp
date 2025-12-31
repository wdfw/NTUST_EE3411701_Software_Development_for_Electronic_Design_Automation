#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <limits>
#include <ctime>
#include "Block.hpp"
#include "SlicingTree.hpp"
using namespace std; 

int NumOfBlocks ;
vector<Block> Blocks ;
float MinAspectRatio ;
float MaxAspectRatio ;


class progress_bar {
    private :
        clock_t start_time ;
        clock_t end_time ;
        string show_str = "" ;
        bool bar_close = false ;

        string to_string_padding(int v){
            if(v<10) return "0" + to_string(v) ;
            return to_string(v) ;
        }
        string clock2time(clock_t c){
            double t = c/CLOCKS_PER_SEC ;
            int min = int(t) / 60 ;
            int sec = t - min*60 ;
            return to_string_padding(min) + ":" + to_string_padding(sec) ;  
        }

    public :
        int total = 0;
        int current = 0; 
        progress_bar(int total){
            this->total = total ;
            this->start_time = clock() ;
        }
        void update(int chunk){
            if(current>=total){
                if(!bar_close) flush() ;
            }else{
                current = current+chunk>total ? total : current+chunk ;
                show() ;
            }
        }
        void flush(){
            end_time = clock() ;
            clock_t diff_time = end_time - start_time ;
            //cout << diff_time ;
            cout << "\r[" << show_str << "]" << "[Finish Time:"<< clock2time(diff_time) <<  "]\n"  ;
            bar_close = true ;
        }
        void show(){
            float percentage = float(current)/float(total) ;
            while(float(current)/float(total)*50>show_str.size()) show_str += "=" ;
            cout << "\r[" << show_str << "]" << "[" << 100.0*percentage << "%]" ;
        }
} ;
bool probibality(const float& pr){
    return float(rand()%100000)/100000 < pr ;
}
int match_int(string& str, size_t& sp){
    size_t temp = sp ;
    while(sp<str.size() && isalnum(str[sp])) sp++;
    return stoi(str.substr(temp, sp-temp)) ; 
}
float match_float(string& str, size_t& sp){
    size_t temp = sp ;
    while(sp<str.size() && (isalnum(str[sp]) || str[sp]=='.')) sp++;

    return stof(str.substr(temp, sp-temp)) ;   
}
string match_name(string& str, size_t& sp){
    size_t temp = sp ;
    while(sp<str.size() && !isspace(str[sp])) sp++;
    return str.substr(temp, sp-temp) ; 
}
void space_closure(string& str, size_t& sp){
    while(sp<str.size() && isspace(str[sp]) ) sp++;
}
typedef enum PARSER_STATE{
    NUM_BLOCKS,
    MIN_ASPECT_RATIO,
    MAX_ASPECT_RATIO,
    BLOCK_NAME,
    BLOCK_WIDTH,
    BLOCK_HEIGHT,
}STATE ;
void parser(string file){
    ifstream fp(file) ;
    size_t sp = 0 ;
    STATE state = NUM_BLOCKS; 
    string str = "";

    while(getline(fp,str)){
        sp = 0 ;
        while(1){
            space_closure(str,sp) ;
            if(sp >= str.size()) break;
            switch (state){
                case NUM_BLOCKS :
                    match_name(str, sp) ;
                    space_closure(str,sp) ;
                    NumOfBlocks = match_int(str, sp) ;
                    state = MIN_ASPECT_RATIO ;
                    break;
                case MIN_ASPECT_RATIO :
                    match_name(str, sp) ;
                    space_closure(str,sp) ;
                    MinAspectRatio = match_float(str, sp) ;
                    state = MAX_ASPECT_RATIO ;
                    break;
                case MAX_ASPECT_RATIO :
                    match_name(str, sp) ;
                    space_closure(str,sp) ;
                    MaxAspectRatio = match_float(str, sp) ;
                    state = BLOCK_NAME ;
                    break;
                case BLOCK_NAME :
                    Blocks.push_back(Block()) ;
                    Blocks.back().name = match_name(str, sp) ;
                    state = BLOCK_WIDTH ;
                    break;
                case BLOCK_WIDTH :
                    Blocks.back().w = match_int(str, sp) ;
                    state = BLOCK_HEIGHT ;
                    break;
                case BLOCK_HEIGHT :
                    Blocks.back().h = match_int(str, sp) ;
                    state = BLOCK_NAME ;
                    break;
                default:
                    cout << "State Error" ;
                    break;
            }
        }
    }
}

void output_slicingtree(string file, SlicingTree& stree, string format=""){
    ofstream fp(file) ;
    pair<int, int> temp ;
    temp = stree.caculate_cost_pair() ;
    stree.place() ;
    if(format=="genPlot"){
        fp << "Boundary " << temp.second << " " << temp.first << "\n" ;
        fp << "Macro " << NumOfBlocks << "\n" ;
        for(auto& it : stree.blocks)
            fp << it.name << " " << it.x << " " << it.y << " " << it.x+it.w << " " << it.y+it.h << "\n" ;
        
    }else{
        fp << temp.second << " " << temp.first << "\n" ;
        for(auto& it : stree.blocks)
            fp << it.name << " " << it.w << " " << it.h << " " <<it.x << " " << it.y << " " << it.x+it.w << " " << it.y+it.h << "\n" ;
        
    }
    fp.close() ;
}
int main(int argc, char* argv[]){
    
    if(argc<3){
        cout << "Inputs Error" ;
        return -1 ;
    }
    
    string input_file=string(argv[1]), output_file=string(argv[2]) ;
    string format = argc>=4 ? string(argv[3]) : "" ;
    srand(time(NULL)) ;

    //Step 1. Parse & Create Slicingtree Representation 
    parser(input_file) ;
    SlicingTree stree(Blocks) ;
    //-----------------Step 1 End-----------------
    //Step 2. Execute SA Algorithm
    //-----------------Hyperparameter---------------
    double tempature = 1000000 ; //tempature in SA
    double r = 0.98 ; //reduce rate
    double eps = 1 ; //terminated tempature
    int kn = 300 ; //for loop kn times for every tempature
    //-----------------Hyperparameter---------------
    double current_tempature = tempature ;
    float last_cost = numeric_limits<float>::max() ;
    float current_cost = numeric_limits<float>::max() ;
    float lowest_cost = numeric_limits<float>::max() ;
    float diff_cost = 0 ;
    
    SlicingTree temp_state = stree ; //keep the previout state of Slicingtree
    SlicingTree best_state = stree ; //keep the Slicingtree with lowest cos
    bool operation_state = false ; // is M1-M3 operation successful ?
    bool accept_state = false ; // is SA accept the update ?
    int operation_code = -1 ; // slect operation 1:M1, 2:M2, 3:M3
    int strategy = 0 ;
    pair<float, float> temp_area = stree.caculate_cost_pair() ;
    swap(temp_area.first,temp_area.second) ;

    vector<float> ideal_indicator = stree.caculate_ideal_result() ; //the ideal perferance (width, height and area)
    
    cout << "Original Area : " << temp_area.first*temp_area.second << " " << temp_area  <<"\n" ;
    cout << "Original Aspect Ratio : " << stree.aspect_ratio <<"\n" ;
    cout << "Original Cost : " << stree.caculate_cost() << "\n" ;
    //cout << "Ideal Indicator (Height, Width, Area) : " << "(" << ideal_indicator[0] << "," << ideal_indicator[1] << "," << ideal_indicator[2] << ")\n" ;
    while(1){
        progress_bar pbar(ceil(log(eps/current_tempature) / log(r)*kn)) ;
        //cout << pbar.total << " " << r << " " << kn << " " << NumOfBlocks<< "\n";

        while (current_tempature>=eps){
            for(int k=0; k<kn; k++){
                operation_code = rand()%3 ;
                switch (operation_code){
                    case 0:
                        operation_state = stree.M1(stree.random_operand_index()) ;
                        break;        
                    case 1:
                        operation_state = stree.M2(stree.random_operator_index()) ;
                        break;
                    case 2:
                        operation_state = stree.M3(rand()%stree.sequence.size()) ;
                        break;
                }

                if(!operation_state){ //when up date fail, retry operation
                    k -- ; 
                }else{
                    current_cost = stree.caculate_cost(strategy) ;

                    if(current_cost < lowest_cost && stree.aspect_ratio>=MinAspectRatio && stree.aspect_ratio<=MaxAspectRatio){
                        lowest_cost = current_cost ;
                        best_state.sequence = stree.sequence ;
                    }

                    diff_cost = current_cost - last_cost ;

                    if( probibality(exp(-diff_cost/tempature)) ){ //accept the step and update
                        temp_state.sequence = stree.sequence ;
                        if(operation_code==2) temp_state.sub_count = stree.sub_count ;
                        accept_state = true ;
                        last_cost = current_cost ;
                    }else{ //reject the step and recover
                        stree.sequence = temp_state.sequence ;
                        if(operation_code==2) stree.sub_count = temp_state.sub_count ;
                        accept_state = false ;
                    }
                    pbar.update(1) ;
                }
            }
            current_tempature *= r ;
        }
        //-----------------Step 2 End-----------------

        //Step 3. Translate Slicingtree to Output Format
        if(strategy==0) temp_area = best_state.caculate_cost_pair() ;
        else temp_area = best_state.caculate_fit_aspect_ratio_pair() ;

        if(best_state.aspect_ratio<MinAspectRatio || best_state.aspect_ratio>MaxAspectRatio){
            if(strategy==0){
                strategy = 1 ;
                last_cost = numeric_limits<float>::max() ;
                current_cost = numeric_limits<float>::max() ;
                lowest_cost = numeric_limits<float>::max() ;
                current_tempature = tempature ;
                diff_cost = 0 ;
                cout << "Can not fit the ratio constrains, change strategy." << "\n";

            }else{
                cout << "No Placement fit the apsec ratios!!!" << "\n";
                return 0 ;
            }
        }else{
            swap(temp_area.first,temp_area.second) ;
            cout << "Optimized  Area : " << temp_area.first*temp_area.second << " " << temp_area << "\n" ;
            cout << "Optimized  Aspect Ratio : " << best_state.aspect_ratio <<"\n" ;
            cout << "Optimized  Cost : " << lowest_cost << "\n" ;
            //cout << "Optimized  Sequence : " << best_state <<"\n"; 
            output_slicingtree(output_file, best_state,format) ;
            return 0 ;
        }
           
        //-----------------Step 3 End-----------------
    }
    return -1 ;    
}