#include "NewCircuitStructure.hpp"

//---------------------------NewCoordinate------------------------------------------------
NewCoordinate::NewCoordinate(Coordinate cordinate){
    this->cordinate[0] = cordinate[0] ;
    this->cordinate[1] = cordinate[1] ;
}
NewCoordinate::NewCoordinate(vector<float> cordinate){
    this->cordinate = cordinate ;
}
NewCoordinate::NewCoordinate(float x, float y){
    this->cordinate[0] = x;
    this->cordinate[1] = y ;
}
NewCoordinate NewCoordinate::operator+(NewCoordinate cordinate2){
    return NewCoordinate(this->cordinate[0]+cordinate2[0], this->cordinate[1]+cordinate2[1]) ;
}
NewCoordinate NewCoordinate::operator-(NewCoordinate cordinate2){
    return NewCoordinate(this->cordinate[0]-cordinate2[0], this->cordinate[1]-cordinate2[1]) ;
}
NewCoordinate NewCoordinate::operator*(NewCoordinate cordinate2){
    return NewCoordinate(this->cordinate[0]*cordinate2[0], this->cordinate[1]*cordinate2[1]) ;
}

float& NewCoordinate::operator[] (int idx){
    return this->cordinate[idx] ;
}
NewCoordinate NewCoordinate::operator+(float n){
    return NewCoordinate(this->cordinate[0]+n,this->cordinate[1]+n) ;
}
NewCoordinate NewCoordinate::operator-(float n){
    return NewCoordinate(this->cordinate[0]-n,this->cordinate[1]-n) ;
}
NewCoordinate NewCoordinate::operator*(float n){
    return NewCoordinate(this->cordinate[0]*n,this->cordinate[1]*n) ;
}
NewCoordinate NewCoordinate::operator/(float n){
    return NewCoordinate(this->cordinate[0]/n,this->cordinate[1]/n) ;
}

bool NewCoordinate::operator!(void){
    return this->cordinate[0]!=-1 && this->cordinate[1]!=-1 ;
}

ostream& operator<<(ostream& os, NewCoordinate newCordinate){
    os << "(" << newCordinate[0] << "," << newCordinate[1] << ")" ;
    return os ;
}
//---------------------------NewCoordinate--------------------------------------------

//---------------------------NewRegion------------------------------------------------
NewRegion::NewRegion(NewCoordinate cordinateLB, NewCoordinate cordinateUR){
    region[0] = cordinateLB[0] ;
    region[1] = cordinateLB[1] ;
    region[2] = cordinateUR[0] ;
    region[3] = cordinateUR[1] ;
}
NewRegion::NewRegion(Region region){
    this->region = region.cor ;
}
NewRegion::NewRegion(vector<float> region){
    this->region = region ;
}
NewRegion::NewRegion(float xl, float yb, float xr, float yt){
    region[0] = xl ;
    region[1] = yb ;
    region[2] = xr ;
    region[3] = yt ;
}

NewRegion NewRegion::operator+(NewRegion region2){
    return NewRegion(this->region[0]+region2[0], this->region[1]+region2[1],this->region[2]+region2[2], this->region[3]+region2[3]) ;
}
NewRegion NewRegion::operator-(NewRegion region2){
    return NewRegion(this->region[0]-region2[0], this->region[1]-region2[1],this->region[2]-region2[2], this->region[3]-region2[3]) ;
}
NewRegion NewRegion::operator*(NewRegion region2){
    return NewRegion(this->region[0]*region2[0], this->region[1]*region2[1],this->region[2]*region2[2], this->region[3]*region2[3]) ;
}
NewRegion NewRegion::operator/(NewRegion region2){
    return NewRegion(this->region[0]/region2[0], this->region[1]/region2[1],this->region[2]/region2[2], this->region[3]/region2[3]) ;
}

NewRegion NewRegion::operator+(float n){
    return NewRegion(this->region[0]+n, this->region[1]+n,this->region[2]+n, this->region[3]+n) ;
}
NewRegion NewRegion::operator-(float n){
    return NewRegion(this->region[0]-n, this->region[1]-n,this->region[2]-n, this->region[3]-n) ;
}
NewRegion NewRegion::operator*(float n){
    return NewRegion(this->region[0]*n, this->region[1]*n,this->region[2]*n, this->region[3]*n) ;
}
NewRegion NewRegion::operator/(float n){
    return NewRegion(this->region[0]/n, this->region[1]/n,this->region[2]/n, this->region[3]/n) ;
}

NewRegion NewRegion::operator+(NewCoordinate cordinate2){
    return NewRegion(this->region[0]+cordinate2[0], this->region[1]+cordinate2[1],
                     this->region[2]+cordinate2[0], this->region[3]+cordinate2[1]) ;
}
NewRegion NewRegion::operator-(NewCoordinate cordinate2){
    return NewRegion(this->region[0]-cordinate2[0], this->region[1]-cordinate2[1],
                     this->region[2]-cordinate2[0], this->region[3]-cordinate2[1]) ;
}
NewRegion NewRegion::operator*(NewCoordinate cordinate2){
    return NewRegion(this->region[0]*cordinate2[0], this->region[1]*cordinate2[1],
                     this->region[2]*cordinate2[0], this->region[3]*cordinate2[1]) ;
}
NewRegion NewRegion::operator/(NewCoordinate cordinate2){
    return NewRegion(this->region[0]/cordinate2[0], this->region[1]/cordinate2[1],
                     this->region[2]/cordinate2[0], this->region[3]/cordinate2[1]) ;
}

bool NewRegion::operator!(void){
    return this->region[0]!=-1 && this->region[1]!=-1 && this->region[2]!=-1 && this->region[3]!=-1 ;
}

float& NewRegion::operator[] (int idx){
    return this->region[idx] ;
}

ostream& operator<<(ostream& os,NewRegion newRegion){
    os << "(" << newRegion[0] << "," << newRegion[1] << "," << newRegion[2] << "," << newRegion[3] << ")" ;
    return os ;
}
//---------------------------NewRegion------------------------------------------------
//---------------------------NewNet------------------------------------------------
NewNet::NewNet(string ID, string TX, vector<string> RX, int num, map<string, vector<NewRegion>> mustThrough,
               map<string, vector<NewRegion>> hmftMustThrough, NewCoordinate TXCoordinate, 
               vector<NewCoordinate> RXCoordinate){
                this->ID = ID ;
                this->TX = TX ;
                this->RX = RX ;
                this->num = num ;
                this->mustThrough = mustThrough ;
                this->hmftMustThrough = hmftMustThrough ;
                this->TXCoordinate = TXCoordinate ;
                this->RXCoordinate = RXCoordinate ;
}
NewNet::NewNet(Net net){
    this->ID = net.ID ;
    this->TX = net.TX ;
    this->RX = net.RX ;
    this->num = net.track ;

    this->mustThrough.clear() ;
    this->hmftMustThrough.clear() ;
    vector<NewRegion> keep ;
    for(auto& it : net.must_through){
        keep.resize(it.second.size()) ;
        for(int i=0; i<it.second.size();i++){
            keep[i] = NewRegion(it.second[i]) ;
        }
        this->mustThrough.insert(pair<string, vector<NewRegion>>(it.first, keep)) ;
    }
    
    for(auto& it : net.hmft_must_through){
        keep.resize(it.second.size()) ;
        for(int i=0; i<it.second.size();i++){
            keep[i] = NewRegion(it.second[i]) ;
        }
        this->hmftMustThrough.insert(pair<string, vector<NewRegion>>(it.first, keep)) ;
    }

    
    this->TXCoordinate = NewCoordinate(net.TX_coordinate) ;
    this->RXCoordinate.resize(net.RX_coordinate.size()) ;
    for(int i=0; i<net.RX_coordinate.size(); i++)
       this->RXCoordinate[i] = NewCoordinate(net.RX_coordinate[i]) ;
}

ostream& operator<<( ostream& os, const NewNet& newNet){
    os << "ID: " << newNet.ID << "\n" ;
    os << "Num: " << newNet.num << "\n" ;
    os << "TX: " << newNet.TX << "\n" ;
    os << "RX: " << newNet.RX << "\n" ;
    os << "TX Coordinate: " << newNet.TXCoordinate << "\n" ;
    os << "RX Coordinate: " << newNet.RXCoordinate << "\n" ;
    os << "Must Through: " << newNet.mustThrough << "\n" ;
    os << "HMFT Must Through: " << newNet.hmftMustThrough << "\n" ;
    os << "Path: " << newNet.path << "\n" ;
    return os ;
}
NetTable CreateNetTable(Nets& nets){
    NetTable table ;
    for(auto& it : nets) table.insert(pair<string, NewNet>(it.first, NewNet(it.second))) ;
    return table ;
}

//---------------------------NewNet------------------------------------------------
//---------------------------NewBlock------------------------------------------------

NewBlock::NewBlock( string ID, NewCoordinates dieRegion, NewCoordinate position,
                    int throughBlockNetNum, int throughEdgeNetNum,
                    bool feedthroughable,bool isRegion, NewRegion inOutRegion, NewRegion portRegion){
    this->ID = ID ;
    this->dieRegion = dieRegion ;
    this->position = position ;

    this->blockRegion = dieRegion ;
    this->blockRegion += position ;
    this->throughBlockNetNum = throughBlockNetNum ;
    this->throughEdgeNetNum = throughEdgeNetNum ;
    this->isRegion = isRegion ;
    this->feedthroughable = feedthroughable ;
    this->inOutRegion = inOutRegion ;
    this->portRegion = portRegion ;
}

void _swap(Coordinate& c){
    float d = c[1] ;
    c[1] = c[0] ;
    c[0] = d ;
}

void _rotateCordinates(vector<Coordinate>& coordiantes, string orient){
    char k ;
    if(orient=="FN") k='A' ;
    else if(orient=="FS") k='B' ;
    else if(orient=="FW") k='C' ;
    else if(orient=="FE") k='D' ;
    else k= orient[0] ;
    for(int i=0; i<coordiantes.size();i++){
        switch (k){
            case 'N':
                break;
            case 'S':{
                coordiantes[i][0] = -coordiantes[i][0] ;
                coordiantes[i][1] = -coordiantes[i][1] ;
            }
            break;
            case 'W':{
                coordiantes[i][1] = -coordiantes[i][1] ;
                _swap(coordiantes[i]) ;
            }
            break;
            case 'E':{
                coordiantes[i][0] = -coordiantes[i][0] ;
                _swap(coordiantes[i]) ;
            }
            break;
            case 'A':{
                coordiantes[i][0] = -coordiantes[i][0] ;
            }
            break;
            case 'B':{
                coordiantes[i][1] = -coordiantes[i][1] ;
            }
            break;
            case 'C':{
                coordiantes[i][1] = -coordiantes[i][1] ;
                coordiantes[i][1] = -coordiantes[i][1] ;
                _swap(coordiantes[i]) ;
            }
            break;
            case 'D':{
                coordiantes[i][0] = -coordiantes[i][0] ;
                coordiantes[i][1] = -coordiantes[i][1] ;
                _swap(coordiantes[i]) ;
            }
            break;
        }
    }
    
    Coordinate offsetCordinate(coordiantes[0][0],coordiantes[0][1]) ;
    for(int i=0; i<coordiantes.size();i++){
        offsetCordinate[0] = min(offsetCordinate[0],coordiantes[i][0]) ;
        offsetCordinate[1] = min(offsetCordinate[1],coordiantes[i][1]) ;
    }
    
    for(int i=0; i<coordiantes.size();i++){
        coordiantes[i][0] -= offsetCordinate[0] ;
        coordiantes[i][1] -= offsetCordinate[1] ;
    }
    if(coordiantes.size()==2){
        float c00 = coordiantes[0][0], c01 = coordiantes[0][1], c10 = coordiantes[1][0], c11 = coordiantes[1][1] ;
        coordiantes[1][1] = max(c01, c11) ;
        coordiantes[1][0] = max(c00, c10) ;
        coordiantes[0][0] = 0 ;
        coordiantes[0][1] = 0 ;
    }
}
BlockTable CreateBlockTable(Blocks& blocks, DEF_Block& defBlock){
    BlockTable table ;

    vector<pair<string,vector<Coordinate>>>& components = defBlock.components ;
    vector<pair<string,Region>>& regions = defBlock.regions ;

    for(int i=0; i<components.size(); i=i+1){
        NewBlock tempBlock ; 

        string ID = components[i].first ;
        vector<Coordinate> dieRegion = components[i].second ;
        Coordinate position = defBlock.bases[i] ;
        Block& block = blocks[ID] ;

        tempBlock.ID = ID ;
        tempBlock.dieRegion.resize(dieRegion.size()) ;

        _rotateCordinates(dieRegion,defBlock.orients[i]) ;

        for(int j=0; j<dieRegion.size(); j++){
            tempBlock.dieRegion[j] = NewCoordinate(dieRegion[j]) ;
        }

        tempBlock.position = NewCoordinate(position) ;

        tempBlock.blockRegion = tempBlock.dieRegion ;
        tempBlock.blockRegion += tempBlock.position ;

        tempBlock.throughBlockNetNum = block.through_block_net_num ;
        tempBlock.throughEdgeNetNum = block.through_block_edge_net_num ;
        tempBlock.feedthroughable = block.is_feedthroughable ;
        tempBlock.isRegion = false ;
        tempBlock.inOutRegion = NewRegion(block.in_out_region) ;
        tempBlock.portRegion = NewRegion(block.block_port_region) ;

        table.insert(pair<string, NewBlock>(tempBlock.ID,tempBlock)) ;
    }

    for(int i=0; i<regions.size(); i=i+1){
        NewBlock tempBlock ; 

        string ID = regions[i].first ;
        Region dieRegion = regions[i].second ;
        tempBlock.ID = ID ;
        tempBlock.blockRegion = {NewCoordinate(dieRegion[0],dieRegion[1]), NewCoordinate(dieRegion[2],dieRegion[3])} ;
        tempBlock.position = {NewCoordinate(dieRegion[0],dieRegion[1])} ;

        tempBlock.dieRegion.resize(2) ;
        tempBlock.dieRegion[0] = tempBlock.blockRegion[0] - tempBlock.position ;
        tempBlock.dieRegion[1] = tempBlock.blockRegion[1] - tempBlock.position ;
        tempBlock.isRegion = true ;


        table.insert(pair<string, NewBlock>(tempBlock.ID,tempBlock)) ;
        
    }
    return table ;
}

ostream& operator<<(ostream& os, NewBlock newBlock){
    os << "ID: " << newBlock.ID << "\n" ;
    os << "Block Region: " << newBlock.blockRegion << "\n" ;
    os << "Die Region: " << newBlock.dieRegion << "\n" ;
    os << "Position: " << newBlock.position << "\n" ;
    os << "Through Block Net Num: " << newBlock.throughBlockNetNum << "\n" ;
    os << "Through Edge Net Num: " << newBlock.throughEdgeNetNum << "\n" ;
    os << "Is Feedthroughable: " << ShowBool(newBlock.feedthroughable) << "\n" ;
    os << "Is Region: " << ShowBool(newBlock.isRegion) << "\n" ;
    os << "I/O Region: " << newBlock.inOutRegion << "\n" ;
    os << "Port Region: " << newBlock.portRegion << "\n" ;
    os << "Grid Code: " << newBlock.gridCode ;
    return os ;
}

//---------------------------NewBlock------------------------------------------------
//---------------------------NewMaze------------------------------------------------
//int edgeHeight(NewBlock& )
bool _isEdge(NewCoordinate& cordinate,NewCoordinates& edges){
    NewCoordinate diff(0,0) ;
    int N = edges.size() ;
    NewCoordinate c1, c2 ;
    for(int i=0; i<N; i++){
        c1 = NewCoordinate(max(edges[i][0],edges[(i+1)%N][0]),max(edges[i][1],edges[(i+1)%N][1])) ;
        c2 = NewCoordinate(min(edges[i][0],edges[(i+1)%N][0]),min(edges[i][1],edges[(i+1)%N][1])) ;
        if(cordinate[0]>c1[0] || cordinate[1]>c1[1] || cordinate[0]<c2[0] || cordinate[1]<c2[1]) continue ;

        diff[0] = c1[0] - c2[0];
        diff[1] = c1[1] - c2[1];


        if(diff[0]==0) return true ;
        else if (int(cordinate[1]) == int(diff[1]/diff[0] * (cordinate[0] - c2[0]) + c2[1])) return true ;
        
    }
    return false ;
}
void NewMaze::bruteForcePolygon(NewBlock& black, int value){
    NewCoordinates& coordinates = black.blockRegion ;
    bool feedthroughable = black.feedthroughable ;

    NewRegion edge(coordinates[0][0],coordinates[0][1],coordinates[0][0],coordinates[0][1]) ;
    for(int i=1; i<coordinates.size();i++){
        edge[0] = min(edge[0], coordinates[i][0]) ;
        edge[1] = min(edge[1], coordinates[i][1]) ;
        edge[2] = max(edge[2], coordinates[i][0]) ;
        edge[3] = max(edge[3], coordinates[i][1]) ;
    }

    for(int i=0; i<coordinates.size();i++){
        NewCoordinate rightUp = NewCoordinate(max(coordinates[i][0], coordinates[(i+1)%coordinates.size()][0]),
                                              max(coordinates[i][1], coordinates[(i+1)%coordinates.size()][1])) ;
        NewCoordinate leftBottom = NewCoordinate(min(coordinates[i][0], coordinates[(i+1)%coordinates.size()][0]),
                                                 min(coordinates[i][1], coordinates[(i+1)%coordinates.size()][1])) ;                                            
        NewCoordinate diff = rightUp - leftBottom ;
        int j ;
        if(diff[0]>diff[1]){
            for(int i=leftBottom[0]; i<=rightUp[0]; i++){
                j = diff[1] * ((i-leftBottom[0])/diff[0]) + leftBottom[1] ;
                this->grid[j][i] = 10 ;
            }      
        }else{
            for(int i=leftBottom[1]; i<=rightUp[1]; i++){
                j = diff[0] * ((i-leftBottom[1])/diff[1]) + leftBottom[0] ;
                this->grid[i][j] = 10 ;
            }     
        }

        bool isClosed ;
        for(int i=int(edge[1]); i<=int(edge[3]); i++){
            isClosed = false ;
            for(int j=int(edge[0]); j<=int(edge[2]); j++){
                if(grid[i][j]==10 && j-1>=0 && grid[i][j-1]!=10) isClosed = !isClosed ;
                if(isClosed)
                    if(feedthroughable) grid[i][j] = 2 ;
                    else grid[i][j] = value ;
            }
        }

        for(int i=0; i<coordinates.size();i++){
            NewCoordinate rightUp = NewCoordinate(max(coordinates[i][0], coordinates[(i+1)%coordinates.size()][0]),
                                                max(coordinates[i][1], coordinates[(i+1)%coordinates.size()][1])) ;
            NewCoordinate leftBottom = NewCoordinate(min(coordinates[i][0], coordinates[(i+1)%coordinates.size()][0]),
                                                    min(coordinates[i][1], coordinates[(i+1)%coordinates.size()][1])) ;                                            
            NewCoordinate diff = rightUp - leftBottom ;
            int j ;
            if(diff[0]!=0){
                for(int i=leftBottom[0]; i<=rightUp[0]; i++){
                    j = diff[1] * ((i-leftBottom[0])/diff[0]) + leftBottom[1] ;
                    if(feedthroughable) this->grid[j][i] = 2 ;
                    else this->grid[j][i] = value ;
                }
            }else{
                j = leftBottom[0] ;
                for(int i=leftBottom[1]; i<=rightUp[1]; i++){
                    if(feedthroughable) this->grid[i][j] = 2 ;
                    else this->grid[i][j] = value ;  
                }
            }
        }
    }
}
int _ManhattanDistance(NewCoordinate& A, NewCoordinate& B){
    return abs(A[0]-B[0])+abs(A[1]-B[1]) ;
}
bool operator<(pair<int,pair<int,NewCoordinate>>A, pair<int,pair<int,NewCoordinate>>B){
    return A.first<B.first ;
}
void _assignColor(Color& color, int r, int g, int b, int a=0){
    color.r = r ;
    color.g = g ;
    color.b = b ;
    color.a = a ;
}
void image(vector<vector<int>>maze, string fileName="mazeCost.bmp", NewCoordinate start=NewCoordinate(), NewCoordinate target=NewCoordinate()){
    Surface surf(maze[0].size(),maze.size());
    int maxVal = 0, minVal= 9999999 ;
    int w=maze[0].size(), h=maze.size();
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){ 
            maxVal = max(maxVal, maze[i][j]) ;
            minVal = min(minVal, maze[i][j]) ;
        }
    }
    int diff = maxVal-minVal ;
    Color color ;
    
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            int f = float(maze[i][j]-minVal)/float(diff)*255.0 ;
            _assignColor(color,f,f,f) ; //可過區塊
            surf.RectFill(j, i, 1, 1, color);
        }
    }
   
    if(!start){
        _assignColor(color,255,0,0) ; //可過區塊
        surf.RectFill(int(start[0]), int(start[1]), 1, 1, color);
    }
    if(!target){
        _assignColor(color,0,255,0) ; //可過區塊
        surf.RectFill(int(target[0]), int(target[1]), 1, 1, color);
    }
    surf.Save(fileName.c_str());
}





bool operator<(NewCoordinate A, NewCoordinate B){
    return A[0]*1000+A[1]<B[0]*1000+B[1] ;
}
void NewMaze::drawAll(NetTable& nets,BlockTable& blocks,string fileName){

    vector<int> prev ;
    vector<NewCoordinate> path ;
    for(auto&it : nets){
        
       for(int i=0; i<it.second.path.size(); i++){
            for(auto& passed : it.second.path[i]){
                prev.push_back( grid[int(passed[1])][int(passed[0])] ) ;
                path.push_back( passed ) ;
                grid[int(passed[1])][int(passed[0])] = 20 ;
            } 
        }
        
        if(!it.second.TXCoordinate){
            NewCoordinate offsetTX = it.second.TXCoordinate + blocks[it.second.TX].position ;
            grid[int(offsetTX[1])][int(offsetTX[0])] = 21 ;
        } 
        for(int rxCount=0; rxCount<it.second.RXCoordinate.size(); rxCount++){
            NewCoordinate offsetRX = it.second.RXCoordinate[rxCount] + blocks[it.second.RX[rxCount]].position ;
            grid[int(offsetRX[1])][int(offsetRX[0])] = 22 ;
        }
    }
    
    mazeImage(fileName) ;

    for(int i=prev.size()-1; i>=0;i--) 
        grid[int(path[i][1])][int(path[i][0])] = prev[i] ;
}
void NewMaze::drawLine(vector<vector<NewCoordinate>>& segement, string fileName, NewCoordinate tx, vector<NewCoordinate> rxs){
    vector<int> prev ;
    vector<NewCoordinate> path ;
   
    for(int i=0; i<segement.size(); i++){
        for(auto& passed : segement[i]){
            prev.push_back( grid[int(passed[1])][int(passed[0])] ) ;
            path.push_back( passed ) ;
            grid[int(passed[1])][int(passed[0])] = 20 ;
        } 
        
    }
    if(!tx) grid[int(tx[1])][int(tx[0])] = 21 ;
    if(rxs.size()){
        for(auto& rx : rxs){
            grid[int(rx[1])][int(rx[0])] = 22 ;
        } 
    }
    mazeImage(fileName) ;

    for(int i=prev.size()-1; i>=0;i--) 
        grid[int(path[i][1])][int(path[i][0])] = prev[i] ;
}

bool operator<(const pair<NewMaze::Cost,NewCoordinate>& c1,const pair<NewMaze::Cost,NewCoordinate>& c2){
    return c1.first.startLength > c2.first.startLength ;
}


void _sink(vector<pair<NewMaze::Cost,NewCoordinate>>& openList, map<NewCoordinate, int>& mapping, NewCoordinate cordinate){
    int currentIdx = mapping[cordinate] ;
    int tempIdx ;
    int a ;
    pair<NewMaze::Cost,NewCoordinate> b = openList[0];
    while(currentIdx*2<openList.size()){
        tempIdx = currentIdx*2 ;
        if(tempIdx+1<openList.size() && openList[tempIdx].first.total > openList[tempIdx+1].first.total) tempIdx++ ;
        if(openList[currentIdx].first.total > openList[tempIdx].first.total){
            
            a = mapping[openList[tempIdx].second] ;
            mapping[openList[tempIdx].second] = mapping[openList[currentIdx].second] ;
            mapping[openList[currentIdx].second] = a ; 

            b = openList[tempIdx] ;
            openList[tempIdx] = openList[currentIdx] ;
            openList[currentIdx] = b ;
            currentIdx = tempIdx ;
        }else{
            break ;
        }
    }
}
void _goup(vector<pair<NewMaze::Cost,NewCoordinate>>& openList, map<NewCoordinate, int>& mapping, NewCoordinate cordinate){
    int currentIdx = mapping[cordinate] ;
    int tempIdx ;
    int a ;
    pair<NewMaze::Cost,NewCoordinate> b = openList[0];

    while(currentIdx!=1 && openList[currentIdx/2].first.total > openList[currentIdx].first.total){
        a = mapping[openList[currentIdx/2].second] ;
        mapping[openList[currentIdx/2].second] = mapping[openList[currentIdx].second] ;
        mapping[openList[currentIdx].second] = a ;

        b = openList[currentIdx/2] ;
        openList[currentIdx/2] = openList[currentIdx] ;
        openList[currentIdx] = b ;
        currentIdx /= 2 ;
    }
}

void _push(vector<pair<NewMaze::Cost,NewCoordinate>>& openList, map<NewCoordinate, int>& mapping, pair<NewMaze::Cost,NewCoordinate> newElement){
    mapping.insert(pair<NewCoordinate,int>{newElement.second, openList.size()}) ;
    openList.push_back(newElement) ;
    _goup(openList,mapping, newElement.second) ;
}

void _pop(vector<pair<NewMaze::Cost,NewCoordinate>>& openList, map<NewCoordinate, int>& mapping){
    pair<NewMaze::Cost,NewCoordinate> temp = openList[1];
    int t = mapping[openList[1].second] ;
    mapping[openList[1].second] = mapping[openList.back().second] ;
    mapping[openList.back().second] = t ;
    openList[1] = openList.back() ;
    openList.back() = temp ;

    _sink(openList,mapping, openList[1].second) ;
}
void _setStartLength(vector<pair<NewMaze::Cost,NewCoordinate>>& openList, map<NewCoordinate, int>& mapping, NewCoordinate cordinate,NewCoordinate newParent, int value){
    openList[mapping[cordinate]].first.setStartLength(value) ;
    openList[mapping[cordinate]].first.parent = newParent ;
    
    _goup(openList, mapping, cordinate) ;
}

vector<NewCoordinate> _getStrightLine(vector<NewCoordinate>& path){
    NewCoordinate diff = path[1]-path[0] ;
    int dx = diff[0];
    int dy = diff[1] ;
    vector<NewCoordinate> lines = {path[0]} ;
    for(int i=1; i<path.size(); i++){
        if(path[i][0]-path[i-1][0]!=dx || path[i][1]-path[i-1][1]!=dy){
            diff = path[i]-path[i-1] ;
            dx = diff[0]; 
            dy = diff[1] ;
            lines.push_back(path[i-1]) ;
        }
    }
    if(lines.back()[0]!=path.back()[0] || lines.back()[1]!=path.back()[1]) lines.push_back(path.back()) ;

    return lines ;
}

bool operator<(NewRegion a, NewRegion b){
    return a[0]>b[0] || (a[0]==b[0] && a[1]>b[1]);
}
void NewMaze::outputNets(NetTable& nets,string fileName){
    vector<int> prev ;

    vector<NewCoordinate> lines ;
    ofstream fp(fileName) ;
    NewNet net ;
    set<NewRegion> uniqueLines ;
    for(auto&it : nets){
        uniqueLines.clear() ;
        net = it.second ;
        lines.clear() ;
        fp << "[" << net.ID <<"]\n" ;

        for(int rxCount=0; rxCount<net.RX.size();rxCount++){
            if(!net.path[rxCount].size()) continue;
            lines = _getStrightLine(net.path[rxCount]) ;
            for(int i=0; i<lines.size()-1; i++) uniqueLines.insert(NewRegion(lines[i],lines[i+1])) ;
            
        }
        for(auto it2 : uniqueLines){
            fp << "(" + to_string(int(it2[0])) + "," +to_string(int(it2[1])) + "),(" +  to_string(int(it2[2])) + "," +to_string(int(it2[3])) + ")\n" ;
        }

    }
    fp.close() ;
}

inline int trackCostFuntion(int tracksNum, int validTracksNum){
    
    if(tracksNum>validTracksNum) return 999999999 ;    
    return tracksNum/(validTracksNum-tracksNum+1) ;
}
void NewMaze::ASartRouterH(NetTable& nets, BlockTable& blocks, int tracksNum, int isMute) {
    
    vector<bool> througableMask(blocks.size()+31,false) ;

    vector<queue<pair<NewCoordinate,int>>> openList ;
    map<NewCoordinate,int> colsedList ; 
    vector<vector<Cost>> costGrid ;
    vector<vector<int>> trackGrid ; //left track

    NewCoordinate txCoordinate, rxCordinate, currentCordinate, keep ;
    vector<NewCoordinate> parent ;

    int anchor = 0 ;
    int successCount = 0 ;
    int totalCount = 0 ;
    int recordCount = 0 ;
    int cy, cx, tx, ty, parentIdx, gValue, totalValue ;
    bool throughable = false ;
    int netTracksNum ;
    bool pink = false ;
    trackGrid = vector<vector<int>>(this->h, vector<int>(this->w,tracksNum)) ;

    for(auto& it : nets){

        NewNet& net = it.second ;
        
        txCoordinate = net.TXCoordinate + blocks[net.TX].position ; 


        txCoordinate[0] = int(txCoordinate[0]);
        txCoordinate[1] = int(txCoordinate[1]);

        througableMask[blocks[it.second.TX].gridCode] = true ;
        netTracksNum = net.num ;

        for(int rxCount=0; rxCount<net.RXCoordinate.size(); rxCount++){
            
            cout << "\rRouting..." ;
		    fflush(stdout);
            totalCount ++ ;
            througableMask[blocks[it.second.RX[rxCount]].gridCode] = true ;
            

            costGrid = vector<vector<Cost>>(this->h, vector<Cost>(this->w,Cost(0,-1))) ;
            

            net.path.push_back(vector<NewCoordinate>{}) ;
            rxCordinate = net.RXCoordinate[rxCount] + blocks[net.RX[rxCount]].position ;
            rxCordinate[0] = int(rxCordinate[0]) ;
            rxCordinate[1] = int(rxCordinate[1]) ;
            openList = vector<queue<pair<NewCoordinate,int>>>(w*h+tracksNum,queue<pair<NewCoordinate,int>>()) ;
            colsedList.clear() ;
            parent.clear();
            costGrid[int(txCoordinate[1])][int(txCoordinate[0])].setEndLength(_ManhattanDistance(txCoordinate,rxCordinate)) ;
            costGrid[int(txCoordinate[1])][int(txCoordinate[0])].setStartLength(0) ;
            costGrid[int(txCoordinate[1])][int(txCoordinate[0])].setTrackCost(0) ;
            

            openList[_ManhattanDistance(txCoordinate,rxCordinate)].push(pair<NewCoordinate, int>{NewCoordinate(txCoordinate[0],txCoordinate[1]), 0}) ;
            anchor = _ManhattanDistance(txCoordinate,rxCordinate) ;
            throughable = true ;

            while(true){
                

                do{
                    if(anchor >= openList.size()){
                        throughable = false ;
                        break ;
                    }
                    currentCordinate = openList[anchor].front().first ;
                    parentIdx = openList[anchor].front().second ;
                    openList[anchor].pop() ;
                   
                    while (anchor<openList.size() && openList[anchor].size()==0) anchor ++ ;
                    if(anchor >= openList.size()) break ; 
                }while(colsedList.find(currentCordinate)!=colsedList.end()) ;
                if(!throughable) break ;

                cx=int(currentCordinate[0]); cy = int(currentCordinate[1]); 
                gValue = costGrid[cy][cx].startLength ;
                colsedList.insert(pair<NewCoordinate,int>{NewCoordinate(cx,cy),parentIdx}) ;
                parent.push_back(NewCoordinate(cx,cy)) ;
                if(currentCordinate[0] == rxCordinate[0] && currentCordinate[1] == rxCordinate[1]) break ;
            
                for(int k=0; k<4; k++){

                    tx = cx ; ty = cy;
                    switch (k){
                    case 0:
                        tx = cx + 1 ;
                        break;
                    case 2:
                        tx = cx - 1 ;
                        break;
                    case 1:
                        ty = cy + 1 ;
                        break;
                    case 3:
                        ty = cy - 1 ;
                        break;
                    }
                    
                    keep[0] = tx ; keep[1] = ty ;
                    if(tx<0 || ty<0 || tx>=w || ty>=h) continue;

                    if(colsedList.find(keep)!=colsedList.end() || (grid[ty][tx]>=30 && !througableMask[grid[ty][tx]])){

                    }else if(costGrid[ty][tx].total==-1){

                        costGrid[ty][tx].setEndLength(_ManhattanDistance(keep,rxCordinate)) ;
                        costGrid[ty][tx].setStartLength(gValue+1) ;

                        if(!(tx==rxCordinate[0] && ty==rxCordinate[1]) || !(tx==txCoordinate[0] && ty==txCoordinate[1])) costGrid[ty][tx].setTrackCost(trackCostFuntion(netTracksNum,trackGrid[ty][tx])) ;
                        if(costGrid[ty][tx].total>=999999999) continue;

                        openList[costGrid[ty][tx].total].push(pair<NewCoordinate, int> {NewCoordinate(tx,ty), parent.size()-1}) ;

                        anchor = min(anchor, costGrid[ty][tx].total) ;
                    }else{
                        if(costGrid[ty][tx].startLength>gValue+1){
                            costGrid[ty][tx].setStartLength(gValue+1) ;
                            if(costGrid[ty][tx].total>=999999999) continue;
                            openList[costGrid[ty][tx].total].push(pair<NewCoordinate, int> {NewCoordinate(tx,ty), parent.size()-1}) ;
                            anchor = min(anchor,costGrid[ty][tx].total) ;
                        }

                    
                    }

                }

            }
            if(throughable){
                int node = parent.size()-1;
                NewCoordinate path ; 
                net.path.back().push_back(parent[node]) ;

                while(true){
                    node = colsedList[parent[node]] ;
                    net.path.back().push_back(parent[node]) ;
                    trackGrid[int(parent[node][1])][int(parent[node][0])] -= netTracksNum ;

                    // cout << parent[node] << " " << trackGrid[int(parent[node][1])][int(parent[node][0])] << " " << costGrid[int(parent[node][1])][int(parent[node][0])].total  << "\n";

                    if(node==0){
                        trackGrid[int(parent[node][1])][int(parent[node][0])] += netTracksNum ;
                        break ;
                    }
                }
                successCount++ ;
                if(!isMute) cout << "\rComplete ID: " <<  net.ID << " - " << rxCount << " | Total Completed: "<< successCount << " Nets\n" ;
                
            }else{
                if(isMute<=1) cout << "\rNon-throughable ID: " << net.ID << " - " << rxCount  <<" | Total Completed: "<< successCount << " Nets\n" ;
            }
            througableMask[blocks[it.second.RX[rxCount]].gridCode] = false ;

        }
        througableMask[blocks[it.second.TX].gridCode] = false ;

    }
    cout << "\r------------------------------------------------------------------------------\n" ; 
    cout << "Routable Rate: " << float(successCount)/float(totalCount)*100 << "%\n" ;
    cout << "\r------------------------------------------------------------------------------\n" ; 

    drawAll(nets,blocks, "./routingResult.bmp");
}


NewMaze::NewMaze(BlockTable& blockTable, int height, int width){
    this->h = height ;
    this->w = width ;
    grid = vector<vector<int>>(height, vector<int>(width,0)) ;

    //trackGrid = vector<vector<int>>(height, vector<int>(width,0)) ;
    int validGrdiCode = 30 ;
    for(auto& it : blockTable){
        it.second.gridCode = validGrdiCode ;
        NewBlock block = it.second  ;
        if(!block.isRegion){
            NewCoordinates blockRegion = block.blockRegion ;
            if(blockRegion.size()==2){                
                for(int i=blockRegion[0][1]; i<blockRegion[1][1]; i++){
                    for(int j=blockRegion[0][0]; j<blockRegion[1][0]; j++){
                        if(block.feedthroughable) grid[i][j] = 2 ;
                        else grid[i][j] = validGrdiCode ;
                    }
                }
                
                if(!block.inOutRegion){
                    NewRegion inOutRegion = block.inOutRegion ;
                    for(int i=inOutRegion[1]; i<inOutRegion[3]; i++){
                        for(int j=inOutRegion[0]; j<inOutRegion[2]; j++){
                            grid[i][j]= 2 ;
                        }
                    }
                }
                            
                if(!block.portRegion){
                    NewRegion portRegion = block.portRegion ;
                    for(int i=portRegion[1]; i<portRegion[3]; i++){
                        for(int j=portRegion[0]; j<portRegion[2]; j++){
                            grid[i][j]= 3 ;
                        }
                    }
                }
            }else{
                bruteForcePolygon(block,validGrdiCode) ; 
            }
            
        }
        validGrdiCode ++ ;
        
    }

}

void NewMaze::mazeImage(string fileName){
    Surface surf(this->w,this->h);
    Color color ;

    for(int i=0; i<this->h; i++){
        for(int j=0; j<this->w; j++){
            
            switch (grid[i][j]){
            case 0:
                _assignColor(color,255,255,255) ; //可過區塊
                break;
            // case 1:
            //     _assignColor(color,0,0,0) ; //不可過元件
            //     break;       
            case 2:
                _assignColor(color,255,0,0) ; //可過元件
                break;        
            case 3:
                _assignColor(color,0,255,0) ; //接口
                break;      
            case 10:
                _assignColor(color,128,128,128) ; //導線
                break;   
            case 20:
                _assignColor(color,0,0,255) ; //導線
                break;    
            case 21:
                _assignColor(color,0,255,255) ; //導線 起點
                break;      
            case 22:
                _assignColor(color,255,255,0) ; //導線 終點
                break;        
            default: //>30
                _assignColor(color,0,0,0) ; //不可過元件
                break;
            }
            surf.RectFill(j, i, 1, 1, color);
        }
    }
   
    surf.Save(fileName.c_str());
}

NewMaze::Cost::Cost(int startLength, int endLength, int trackCost, NewCoordinate parent){
    this->total = startLength + endLength ;
    this->startLength = startLength ;
    this->endLength = endLength ;
    this->trackCost = trackCost ;
    this->parent = parent ;
}
void NewMaze::Cost::setStartLength(int newValue){
    this->startLength = newValue ;
    this->total = this->startLength + this->endLength + this->trackCost;
}
void NewMaze::Cost::setEndLength(int newValue){
    this->endLength = newValue ;
    this->total = this->startLength + this->endLength + this->trackCost;
}
void NewMaze::Cost::setTrackCost(int newValue){
    this->trackCost = newValue ;
    this->total = this->startLength + this->endLength + this->trackCost;
}
bool  NewMaze::Cost::operator>(const Cost& c2){
    return this->startLength > c2.startLength ;
}

ostream& operator<<(ostream& os, NewMaze::Cost cost){
    os <<"(" << cost.startLength << " " << cost.endLength << " | " << cost.total << " )" ;
    return os ;
}

//---------------------------NewMaze------------------------------------------------
//----------------------------mase---------------------------------------------------
void operator+=(NewCoordinates& cordinates, NewCoordinate position){
    for(auto& it : cordinates) it = it+position ;
} 

