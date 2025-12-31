#include "SlicingTree.hpp" 


int min_cost_index(vector<pair<float,float>>& p){
    float a = -1 ;
    float b = 0 ;
    int idx = -1 ;
    for(int i=0; i<p.size(); i++){
        b = p[i].first * p[i].second * max(p[i].first,p[i].second)/min(p[i].first,p[i].second);
        if(a>b || a<0){
            a = b ;
            idx = i ;
        }
    }
    return idx ;
}

vector<int> min_ratio_index(vector<pair<float,float>>& p){
    float mid_aspect_ratio = (MinAspectRatio+MaxAspectRatio)/2 ;
    float r1 = p[0].first/p[0].second, r2 = numeric_limits<float>::max() ;  ;
    vector<int> idxs = {0, -1} ;

    float temp_ratio ;
    for(int i=1; i<p.size(); i++){
        temp_ratio = abs(p[i].first/p[i].second-mid_aspect_ratio) ;
        if(temp_ratio<r1) {
            r2 = r1 ;
            r1 = temp_ratio ;
            idxs[1] = idxs[0] ;
            idxs[0] = i ;
        }else if (temp_ratio<r2){
            r2 = temp_ratio ;
            idxs[1] = i ;
        }
    }
    return idxs;
}

int min_height_index(vector<pair<float,float>> p){
    float h = p[0].first ;
    float a = p[0].first*p[0].second ;
    int idx = 0 ;
    for(int i=1; i<p.size(); i++){
        if((p[i].first<h) || (p[i].first==h && p[i].first*p[i].second<a)){
            h = p[i].first ; 
            idx = i ;
            a = p[i].first*p[i].second ;
        }
    }
    return idx ;
}
int min_width_index(vector<pair<float,float>> p){
    float w = p[0].second ;
    float a = p[0].first*p[0].second ;
    int idx = 0 ;
    for(int i=1; i<p.size(); i++){
        if((p[i].second<w) || (p[i].second==w && p[i].first*p[i].second<a)){
            w = p[i].second ; 
            idx = i ;
            a = p[i].first*p[i].second ;
        }
    }
    return idx ;
}
pair<float, float> vertical_combine(const pair<float, float>& a,const pair<float, float>& b){
    return pair<float, float>( max(a.first,b.first), a.second+b.second) ;
}
pair<float, float> horizontal_combine(const pair<float, float>& a,const pair<float, float>& b){
    return pair<float, float>( a.first+b.first, max(a.second,b.second)) ;
}

SlicingTree::SlicingTree(const vector<Block>& blocks){
    this->blocks = blocks ;

    initial() ;
    this->sub_count = vector<int>(blocks.size()*2-1,0) ;

    sub_count[0] = 1 ;
    for(int i=1; i<sequence.size(); i++) sub_count[i] = sequence[i]>=0 ? sub_count[i-1]+1 : sub_count[i-1] ;
    caculate_cost() ;
}
ostream& operator<<(ostream& os, SlicingTree st){
    for(auto& it : st.sequence){
        if(it==-1) os << "V " ;
        else if(it==-2) os << "H " ;
        else if(it==-3) os << "R " ;
        else os << it << " " ;
    }
    return os ;
}

bool SlicingTree::M1(int pos){
    if(sequence[pos]<0) return false;
    int temp = pos ;

    while(++pos<sequence.size())
        if(sequence[pos]>=0) break ; 
    
    int t = sequence[temp] ;
    if(pos<sequence.size()){
        sequence[temp] = sequence[pos] ;
        sequence[pos] = t ;
    }
    return true ;
}

bool SlicingTree::M2(int pos){
    if(sequence[pos]>=0) return false;
    else if(sequence[pos]==-1) sequence[pos]=-2 ;
    else sequence[pos] = -1 ;
    return true ;
}

bool SlicingTree::M3(int pos){
    int temp = pos ;
    if(sequence[pos]<0){
        while(++pos<sequence.size())
            if(sequence[pos]>=0) break ; 
    }else{
        while(++pos<sequence.size())
            if(sequence[pos]<0) break ; 
    }
    int t = sequence[temp] ;
    
    if(pos<sequence.size()){
        if(sequence[temp]>=0 && temp + 1 - sub_count[temp] + 1 >= sub_count[temp] - 1) return false;
        if(sequence[temp]>=0) for(int i=temp; i<pos; i++) sub_count[i] -= 1 ;
        else for(int i=temp; i<pos; i++) sub_count[i] += 1 ;

        sequence[temp] = sequence[pos] ;
        sequence[pos] = t ;
    }
    return true ;
    
}   

float SlicingTree::caculate_cost(int strategy){
    pair<float, float> temp = !strategy ? caculate_cost_pair() : caculate_fit_aspect_ratio_pair() ;
    return  temp.first * temp.second * max(temp.first,temp.second)/min(temp.first,temp.second);
}

pair<float, float> SlicingTree::caculate_fit_aspect_ratio_pair(){
    vector<vector<pair<float, float>>> stack ;
    vector<pair<float, float>> temp ;
    vector<int> idxs ;
    //Nx2x2
    int idx1, idx2 ; 

    for(int i=0; i<sequence.size(); i++){
        if(sequence[i]>=0){
            stack.push_back(vector<pair<float, float>> {pair<float, float>(blocks[sequence[i]].h, blocks[sequence[i]].w),
                                                    pair<float, float>(blocks[sequence[i]].w, blocks[sequence[i]].h)}) ;
            //cout << blocks[sequence[i]].h << " " << blocks[sequence[i]].w << " , " << blocks[sequence[i]].w << " " << blocks[sequence[i]].h <<"\n";
        }else{
            idx1 = stack.size()-1 ;
            idx2 = stack.size()-2 ;
            if(sequence[i]==-1)
                temp = vector<pair<float, float>>{
                vertical_combine(stack[idx1][0], stack[idx2][0]),
                vertical_combine(stack[idx1][0], stack[idx2][1]),
                vertical_combine(stack[idx1][1], stack[idx2][0]),
                vertical_combine(stack[idx1][1], stack[idx2][1])} ;
            else 
                temp = vector<pair<float, float>>{
                horizontal_combine(stack[idx1][0], stack[idx2][0]),
                horizontal_combine(stack[idx1][0], stack[idx2][1]),
                horizontal_combine(stack[idx1][1], stack[idx2][0]),
                horizontal_combine(stack[idx1][1], stack[idx2][1])} ;

            stack.pop_back() ;
            stack.pop_back() ;
            idxs = min_ratio_index(temp) ;
            stack.push_back(vector<pair<float, float>>{temp[idxs[0]], temp[idxs[1]]}) ;
        }
    }
    idxs = min_ratio_index(stack[0]) ;

    pair<float, float> fit_ratio_pair = stack[0][idxs[0]] ;
    
    aspect_ratio = fit_ratio_pair.first/fit_ratio_pair.second ;
    return fit_ratio_pair ;
}

pair<float, float> SlicingTree::caculate_cost_pair(){
    vector<vector<pair<float, float>>> stack ;
    vector<pair<float, float>> temp ;
    //Nx2x2
    int idx1, idx2 ; 

    for(int i=0; i<sequence.size(); i++){
        if(sequence[i]>=0){
            stack.push_back(vector<pair<float, float>> {pair<float, float>(blocks[sequence[i]].h, blocks[sequence[i]].w),
                                                    pair<float, float>(blocks[sequence[i]].w, blocks[sequence[i]].h)}) ;
            //cout << blocks[sequence[i]].h << " " << blocks[sequence[i]].w << " , " << blocks[sequence[i]].w << " " << blocks[sequence[i]].h <<"\n";
        }else{
            idx1 = stack.size()-1 ;
            idx2 = stack.size()-2 ;
            if(sequence[i]==-1)
                temp = vector<pair<float, float>>{
                vertical_combine(stack[idx1][0], stack[idx2][0]),
                vertical_combine(stack[idx1][0], stack[idx2][1]),
                vertical_combine(stack[idx1][1], stack[idx2][0]),
                vertical_combine(stack[idx1][1], stack[idx2][1])} ;
            else 
                temp = vector<pair<float, float>>{
                horizontal_combine(stack[idx1][0], stack[idx2][0]),
                horizontal_combine(stack[idx1][0], stack[idx2][1]),
                horizontal_combine(stack[idx1][1], stack[idx2][0]),
                horizontal_combine(stack[idx1][1], stack[idx2][1])} ;

            stack.pop_back() ;
            stack.pop_back() ;
            stack.push_back(vector<pair<float, float>>{temp[min_height_index(temp)], temp[min_width_index(temp)]}) ;
        }
    }
    pair<float, float> min_cost_pair = stack[0][min_cost_index(stack[0])] ;
    aspect_ratio = min_cost_pair.first/min_cost_pair.second;
    return min_cost_pair ;
}
vector<float> SlicingTree::caculate_ideal_result(){
    vector<float> p = {0,0,0} ; //h, w, area
    for(int i=0; i<blocks.size(); i++){
        p[0] = blocks[i].h > p[0] ? blocks[i].h : p[0] ; 
        p[1] = blocks[i].w > p[1] ? blocks[i].w : p[1] ; 
        p[2] += blocks[i].h* blocks[i].w ;
    }
    return p ;
}

int SlicingTree::random_operand_index(){
    int k = rand() % sequence.size() ;
    while(sequence[k]<0) k = rand() % sequence.size() ;
    return k ;
}
int SlicingTree::random_operator_index(){
    int k = rand() % sequence.size() ;
    while(sequence[k]>=0) k = rand() % sequence.size() ;
    return k ;
}

void SlicingTree::place(){
    vector<vector<pair<float, float>>> stack ;
    vector<pair<float, float>> temp ;
    vector<vector<vector<int>>> temp_sequence ;
    vector<vector<int>> pop_sequence1, pop_sequence2 ;
    int selected_idx1 = 0, selected_idx2 = 0 ;
    //Nx2x2
    int idx1, idx2 ; 

    for(int i=0; i<sequence.size(); i++){
        //temp_sequence.push_back(sequence[i]) ;

        if(sequence[i]>=0){
            stack.push_back(vector<pair<float, float>> {pair<float, float>(blocks[sequence[i]].h, blocks[sequence[i]].w),
                                                    pair<float, float>(blocks[sequence[i]].w, blocks[sequence[i]].h)}) ;
            temp_sequence.push_back(vector<vector<int>>{{0},{1}}) ;
            //cout << stack << " S\n" ;
            //cout << temp_sequence << " C\n" ;

        }else {
            idx1 = stack.size()-1 ;
            idx2 = stack.size()-2 ;

            if(sequence[i]==-1){
                temp = vector<pair<float, float>>{
                vertical_combine(stack[idx1][0], stack[idx2][0]), //KK
                vertical_combine(stack[idx1][0], stack[idx2][1]), //KR
                vertical_combine(stack[idx1][1], stack[idx2][0]), //RK
                vertical_combine(stack[idx1][1], stack[idx2][1])} ; //RR
            }else{
                temp = vector<pair<float, float>>{
                horizontal_combine(stack[idx1][0], stack[idx2][0]), //KK
                horizontal_combine(stack[idx1][0], stack[idx2][1]), //KR
                horizontal_combine(stack[idx1][1], stack[idx2][0]), //RK
                horizontal_combine(stack[idx1][1], stack[idx2][1])} ; //RR
            }
            selected_idx1 = min_height_index(temp) ;
            selected_idx2 = min_width_index(temp) ;

            stack.pop_back() ;
            stack.pop_back() ;
            stack.push_back(vector<pair<float, float>>{temp[selected_idx1], temp[selected_idx2]}) ;

            pop_sequence1 = temp_sequence.back() ;
            pop_sequence2 = temp_sequence[temp_sequence.size()-2] ;

            temp_sequence.pop_back() ;
            temp_sequence.pop_back() ;
            temp_sequence.push_back(vector<vector<int>>{}) ;
            
            //cout << pop_sequence1 << " | " << selected_idx1 << " P1\n" ;
            //cout << pop_sequence2 << " | " << selected_idx2 << " P2\n" ;
            //cout << temp << " T\n\n" ;
            //cout << selected_idx1 << " " << selected_idx2 << "\n" ;
            if(selected_idx1==0) temp_sequence.back().push_back(combine_vector(pop_sequence2[0], pop_sequence1[0])) ;
            else if(selected_idx1==1) temp_sequence.back().push_back(combine_vector(pop_sequence2[1], pop_sequence1[0])) ;
            else if(selected_idx1==2) temp_sequence.back().push_back(combine_vector(pop_sequence2[0], pop_sequence1[1])) ;
            else temp_sequence.back().push_back(combine_vector(pop_sequence2[1], pop_sequence1[1])) ;
            
            if(selected_idx2==0) temp_sequence.back().push_back(combine_vector(pop_sequence2[0], pop_sequence1[0])) ;
            else if(selected_idx2==1) temp_sequence.back().push_back(combine_vector(pop_sequence2[1], pop_sequence1[0])) ;
            else if(selected_idx2==2) temp_sequence.back().push_back(combine_vector(pop_sequence2[0], pop_sequence1[1])) ;
            else temp_sequence.back().push_back(combine_vector(pop_sequence2[1], pop_sequence1[1])) ;
            //cout << stack << " S\n" ;
            //cout << temp_sequence << " H\n" ;
            //cout << stack.back()[0].first << " " << stack.back()[0].second  << " , " << stack.back()[1].first  << " " << stack.back()[1].second  <<"\n";
        }

        //vector<int> k =  combine_vector(temp_sequence.back()[0], temp_sequence.back()[1]) ;
        //cout << k ;
    }
    //minCostIdx()
    //cout << minCostIdx(stack[0])  <<"\n";
    //cout << stack << "\n" ;
    vector<int> rotate_sequence = temp_sequence.back()[min_cost_index(stack[0])] ;
    //cout << this->caculate_cost_pair() ;
    //cout << *this << "\n" ;
    //cout << rotate_sequence << "\n" ;
    //cout << blocks << "\n" ;
    //sequence
    vector<pair<float, float>> position ;
    vector<vector<pair<float, float>>> cordinate ; //h w
    vector<vector<int>> order ;

    pair<float, float> temp_position ;
    vector<pair<float, float>> temp_cordinate ;
    vector<int> temp_order ;
    int temp_xy ;
    int d = 0;
    for(int i=0; i<sequence.size();i++){
        if(sequence[i]>=0){
            if(rotate_sequence[d]==0){
                position.push_back(pair<int, int>{blocks[sequence[i]].h,blocks[sequence[i]].w}) ;
            }else{
                position.push_back(pair<int, int>{blocks[sequence[i]].w,blocks[sequence[i]].h}) ;
                temp_xy = blocks[sequence[i]].h ;
                blocks[sequence[i]].h = blocks[sequence[i]].w ;
                blocks[sequence[i]].w = temp_xy ;
            }

            cordinate.push_back(vector<pair<float,float>>{ pair<float,float>(0,0) }) ;    
            order.push_back(vector<int>{sequence[i]}) ;
            d ++ ;

        }else{
            idx1 = position.size()-1 ;
            idx2 = position.size()-2 ;

            if(sequence[i]==-1){
                temp_position = vertical_combine(position[idx1], position[idx2]) ;
                for(int j=0; j<cordinate[idx1].size(); j++) cordinate[idx1][j].second += position[idx2].second ;
            }else{
                temp_position = horizontal_combine(position[idx1], position[idx2]) ;
                for(int j=0; j<cordinate[idx1].size(); j++) cordinate[idx1][j].first += position[idx2].first ;
            }

            temp_cordinate = combine_vector(cordinate[idx2], cordinate[idx1]) ;
            temp_order = combine_vector(order[idx2], order[idx1]) ;

            order.pop_back() ;
            order.pop_back() ;
            position.pop_back() ;
            position.pop_back() ;
            cordinate.pop_back() ;
            cordinate.pop_back() ;

            cordinate.push_back(temp_cordinate) ;
            position.push_back(temp_position) ;
            order.push_back(temp_order) ;

        }
        //cout << order << " O\n" ;
        //cout << position << " P\n" ;
        //cout << cordinate << " C\n" ;
        //cout << cordinate << " B\n" ;
    }
    
    int dd = 0 ;
    for(auto& it:sequence){
        if(it>=0){
            blocks[it].x = cordinate.back()[dd].second ;
            blocks[it].y = cordinate.back()[dd].first ;
            dd ++ ;
        }
    }
    //cout << combine_vector(temp_sequence.back()[0], temp_sequence.back()[1]) ;
}


bool side_compare(pair<int, float> a, pair<int, float> b) {
    return a.second < b.second ; // 升序排列
}
pair<float,float> side_combine(pair<float, float>& a, pair<float, float>& b){
    
    return pair<float,float>(max(max(a.first,a.second),max(b.first,b.second)), min(a.first,a.second)+min(b.first,b.second)) ;
}
void SlicingTree::initial(){
    vector<vector<int>> initial_sequence ;
    vector<pair<int, float>> sorted_side ; //sort by longest side and mapping by index (index, side)
    vector<pair<float, float>> side ; //(h, w)

    vector<vector<int>> temp_sequence ;
    vector<pair<float, float>> temp_side ;
    int dd = 0 ;
    for(auto& it : blocks){
        side.push_back(pair<float,float>(it.h, it.w)) ;
        sorted_side.push_back(pair<int,float>(dd, max(it.w, it.h))) ;
        initial_sequence.push_back(vector<int>{dd++}) ;
    }
    sort(sorted_side.begin(), sorted_side.end(), side_compare);

    int combine_state = -1 ;
    while(initial_sequence.size()!=1){
        for(int i=0; i+1<sorted_side.size(); i+=2){
            temp_sequence.push_back(combine_vector(initial_sequence[sorted_side[i].first], initial_sequence[sorted_side[i+1].first])) ;
            temp_sequence.back().push_back(combine_state) ; //!!!!!!!!!!!!!
            temp_side.push_back(side_combine(side[i], side[i+1])) ;
        }
        if(sorted_side.size()%2){
            temp_sequence.push_back(initial_sequence.back()) ;
            temp_side.push_back(side.back()) ;
        }
        initial_sequence = vector<vector<int>>(temp_sequence) ;
        temp_sequence.clear() ;
        side = vector<pair<float, float>>(temp_side) ;
        temp_side.clear() ;
        sorted_side.clear() ;
        dd = 0 ;
        for(auto& it : side) sorted_side.push_back(pair<int,float>(dd++, max(it.first, it.second))) ;
        combine_state = combine_state==-1 ? -2 : -1 ;
        //cout << initial_sequence << " S\n" << side << " I\n" << sorted_side << " SS\n\n" ;
    }
    this->sequence = initial_sequence.back() ;
    //cout << *this ;

}