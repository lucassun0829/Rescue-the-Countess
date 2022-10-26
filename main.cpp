// B99292359FFD910ED13A7E6C7F9705B8742F0D79
//  main.cpp
//  p1
//
//  Created by Lucas Sun on 9/9/22.
//

#include <getopt.h>
#include <iostream>
#include <istream>
#include <vector>
#include <deque>
#include <algorithm>
#include <deque>

#include "xcode_redirect.hpp"

using namespace std;

class Spot{
public:
    char name = '.';
    char from = '%';
    bool checked = false;
    bool is_pipe = false;
};


class CounteesMap{
    
public:
    vector<vector<vector<Spot>>> map;
    uint32_t row;
    uint32_t total_room;
    char input_mode;
    CounteesMap(vector<vector<vector<Spot>>> init, uint32_t total_row, uint32_t room, char mode){
        map = init;
        row = total_row;
        total_room = room;
        input_mode = mode;
    };
    void get_mode(int argc, char * argv[]);
    void read_data();
    void search();
    void search_position(int x, int y);
//    void search_spot(uint32_t room, uint32_t x, uint32_t y);
    bool is_walkable(uint32_t room, uint32_t x, uint32_t y);
    void backtrace();
    void output();
    bool found = false;
    uint32_t discovered = 1;
    
    
    
    
private:
    deque<vector<uint32_t>> container;
    bool search_mode;
    bool output_mode = true;
    deque<vector<uint32_t>> path;
    uint32_t start_room;
    uint32_t start_row;
    uint32_t start_col;
    uint32_t end_room;
    uint32_t end_row=-1;
    uint32_t end_col;
};

void CounteesMap::output(){
    if(output_mode){
        cout<<"Start in room "<<start_room<<", row "<<start_row<<", column "<<start_col<<'\n';
        for(uint32_t i = 0; i<total_room; i++){
            cout<<"//castle room "<<i<<'\n';
            for(uint32_t x=0; x<row;x++){
                for(uint32_t d=0; d<row;d++){
                    cout<<map[i][x][d].name;
                }
                cout<<'\n';
            }
        }
    }
    else if(!output_mode){
        cout<<"Path taken:\n";
        while(!path.empty()){
            vector<uint32_t> current_spot;
            current_spot = path.back();
//            char name = map[current_spot[0]][current_spot[1]][current_spot[2]].name;
            cout<<"("<<current_spot[0]<<","<<current_spot[1]<<","<<current_spot[2]<<","<<map[current_spot[0]][current_spot[1]][current_spot[2]].name<<")\n";
            path.pop_back();
            
        }
    }
}

void CounteesMap::backtrace(){
//    Spot cur_spot = map[end_room][end_row][end_col];
    while(map[end_room][end_row][end_col].from!='*'){
        if(map[end_room][end_row][end_col].from == 's'){
            end_row -=1;
//            cur_spot =map[end_room][end_row][end_col];
            map[end_room][end_row][end_col].name = 's';
        }
        else if(map[end_room][end_row][end_col].from == 'e'){
            end_col -=1;
//            cur_spot =map[end_room][end_row][end_col];
            map[end_room][end_row][end_col].name = 'e';
        }
        else if(map[end_room][end_row][end_col].from == 'n'){
            end_row +=1;
//            cur_spot =map[end_room][end_row][end_col];
            map[end_room][end_row][end_col].name = 'n';
        }
        else if(map[end_room][end_row][end_col].from == 'w'){
            end_col +=1;
//            cur_spot =map[end_room][end_row][end_col];
            map[end_room][end_row][end_col].name = 'w';
        }
        else if(static_cast<uint32_t>(map[end_room][end_row][end_col].from - '0') < total_room){
            end_room = static_cast<uint32_t>(map[end_room][end_row][end_col].from - '0');
//            cur_spot =map[end_room][end_row][end_col];
            map[end_room][end_row][end_col].name = 'p';
        }
        path.push_back({end_room, end_row, end_col});

    }

}
//bool CounteesMap::is_walkable(uint32_t room, uint32_t x, uint32_t y){
//    if(x >= row || y >= row){
//        return false;
//    }
//    else if(map[room][x][y].name=='#'){
//        return false;
//    }
//    else if(map[room][x][y].name=='!'){
//        return false;
//    }
//    else if(room > total_room){
//        return false;
//    }
//    else if(map[room][x][y].checked){
//        return false;
//    }
//
//    return true;
//}
//void CounteesMap::search_spot(uint32_t room, uint32_t x, uint32_t y){
//    //N
//    if(is_walkable(room, x-1, y)){
//        map[room][x-1][y].from = 's';
//        map[room][x-1][y].checked = true;
//        if(map[room][x-1][y].name=='C'){
//            end_room = room;
//            end_row = x-1;
//            end_col = y;
//            found = true;
//            return;
//        }
//        discovered++;
//        vector<uint32_t> vect{room,x-1,y};
//        container.push_back(vect);
//    }
//
//    if(is_walkable(room, x,y+1)){
//        map[room][x][y+1].from = 'w';
//        map[room][x][y+1].checked = true;
//        if(map[room][x][y+1].name=='C'){
//            end_room = room;
//            end_row = x;
//            end_col = y+1;
//            found = true;
//            return;
//        }
//        discovered++;
//        vector<uint32_t> vect{room,x,y+1};
//        container.push_back(vect);
//
//    }
//    if(is_walkable(room, x+1,y)){
//        map[room][x+1][y].from = 'n';
//        map[room][x+1][y].checked = true;
//        if(map[room][x+1][y].name=='C'){
//            end_room = room;
//            end_row = x+1;
//            end_col = y;
//            found = true;
//            return;
//        }
//        discovered++;
//        vector<uint32_t> vect{room,x+1,y};
//        container.push_back(vect);
//    }
//    if(is_walkable(room, x,y-1)){
//        map[room][x][y-1].from = 'e';
//        map[room][x][y-1].checked = true;
//        if(map[room][x][y-1].name=='C'){
//            end_room = room;
//            end_row = x;
//            end_col = y-1;
//            found = true;
//            return;
//        }
//        discovered++;
//        vector<uint32_t> vect{room,x,y-1};
//        container.push_back(vect);
//
//    }
//}

void CounteesMap::search(){
    map[start_room][start_row][start_col].from = '*';
    map[start_room][start_row][start_col].checked = true;
    container.push_back({start_room,start_row,start_col});

    while(!container.empty()){
        vector<uint32_t> current_spot;
        
        if(search_mode){
            current_spot = container.back();
            container.pop_back();
        }
        else{
            current_spot = container.front();
            container.pop_front();
        }
//        Spot cur_spot =map[current_spot[0]][current_spot[1]][current_spot[2]];
        
        if(map[current_spot[0]][current_spot[1]][current_spot[2]].is_pipe){
            uint32_t cur_room =static_cast<uint32_t>(map[current_spot[0]][current_spot[1]][current_spot[2]].name-'0');
            //if pipe number is less than total room (meaning it is a valid pipe) and if pipe number does not equals to the current room and the position of the pipe-connect room is not checked
            if(cur_room<total_room  && cur_room!= current_spot[0] && !map[cur_room][current_spot[1]][current_spot[2]].checked){
                discovered++;
                container.push_back({cur_room,current_spot[1],current_spot[2]});
                char prev_room = static_cast<char>('0'+current_spot[0]);
                map[cur_room][current_spot[1]][current_spot[2]].from = prev_room;
                map[cur_room][current_spot[1]][current_spot[2]].checked = true;
                if(map[cur_room][current_spot[1]][current_spot[2]].name=='C'){
                    found=true;
                    end_room = cur_room;
                    end_row =current_spot[1];
                    end_col = current_spot[2];
                    break;
                }
            }
        }
//
//        if(static_cast<int>(cur_spot.name-'0')<10 && cur_spot.name-'0'>=0 && cur_spot.name-'0' != current_spot[0]){
//            if(static_cast<int>(cur_spot.name-'0')>=total_room ||  !is_walkable(cur_spot.name-'0', current_spot[1], current_spot[2])){
//                continue;
//            }
//            char prev_room = static_cast<char>('0'+current_spot[0]);
//            uint32_t cur_room =cur_spot.name-'0';
//            map[cur_room][current_spot[1]][current_spot[2]].from = prev_room;
//            map[cur_room][current_spot[1]][current_spot[2]].checked = true;
//            vector<uint32_t> vect{cur_room,current_spot[1],current_spot[2]};
//            container.push_back(vect);
//
//        }
        else{
//            search_spot(current_spot[0], current_spot[1],current_spot[2]);
//            uint32_t room = current_spot[0];
//            uint32_t x = current_spot[1];
//            uint32_t y = current_spot[2];
            if(current_spot[1]-1 < row && !map[current_spot[0]][current_spot[1]-1][current_spot[2]].checked){
                map[current_spot[0]][current_spot[1]-1][current_spot[2]].from = 'n';
                map[current_spot[0]][current_spot[1]-1][current_spot[2]].checked = true;
                if(map[current_spot[0]][current_spot[1]-1][current_spot[2]].name=='C'){
                    end_room = current_spot[0];
                    end_row = current_spot[1]-1;
                    end_col = current_spot[2];
                    found = true;
                    break;
                }
                discovered++;
//                vector<uint32_t> vect{room,x-1,y};
                container.push_back({current_spot[0],current_spot[1]-1,current_spot[2]});
            }
            if(current_spot[2]+1 < row && !map[current_spot[0]][current_spot[1]][current_spot[2]+1].checked){
                map[current_spot[0]][current_spot[1]][current_spot[2]+1].from = 'e';
                map[current_spot[0]][current_spot[1]][current_spot[2]+1].checked = true;
                if(map[current_spot[0]][current_spot[1]][current_spot[2]+1].name=='C'){
                    end_room = current_spot[0];
                    end_row = current_spot[1];
                    end_col = current_spot[2]+1;
                    found = true;
                    break;
                }
                discovered++;
                container.push_back({current_spot[0],current_spot[1],current_spot[2]+1});

            }
            if(current_spot[1]+1 < row && !map[current_spot[0]][current_spot[1]+1][current_spot[2]].checked){
                map[current_spot[0]][current_spot[1]+1][current_spot[2]].from = 's';
                map[current_spot[0]][current_spot[1]+1][current_spot[2]].checked = true;
                if(map[current_spot[0]][current_spot[1]+1][current_spot[2]].name=='C'){
                    end_room = current_spot[0];
                    end_row = current_spot[1]+1;
                    end_col = current_spot[2];
                    found = true;
                    break;
                }
                discovered++;
                container.push_back({current_spot[0],current_spot[1]+1,current_spot[2]});
            }
            if(current_spot[2]-1 < row && !map[current_spot[0]][current_spot[1]][current_spot[2]-1].checked){
                map[current_spot[0]][current_spot[1]][current_spot[2]-1].from = 'w';
                map[current_spot[0]][current_spot[1]][current_spot[2]-1].checked = true;
                if(map[current_spot[0]][current_spot[1]][current_spot[2]-1].name=='C'){
                    end_room = current_spot[0];
                    end_row = current_spot[1];
                    end_col = current_spot[2]-1;
                    found = true;
                    break;
                }
                discovered++;
                container.push_back({current_spot[0],current_spot[1],current_spot[2]-1});

            }
//            if(is_walkable(room, x-1, y)){
//                map[room][x-1][y].from = 's';
//                map[room][x-1][y].checked = true;
//                if(map[room][x-1][y].name=='C'){
//                    end_room = room;
//                    end_row = x-1;
//                    end_col = y;
//                    found = true;
//                    break;
//                }
//                discovered++;
//                vector<uint32_t> vect{room,x-1,y};
//                container.push_back(vect);
//            }
//
//            if(is_walkable(room, x,y+1)){
//                map[room][x][y+1].from = 'w';
//                map[room][x][y+1].checked = true;
//                if(map[room][x][y+1].name=='C'){
//                    end_room = room;
//                    end_row = x;
//                    end_col = y+1;
//                    found = true;
//                    break;
//                }
//                discovered++;
//                vector<uint32_t> vect{room,x,y+1};
//                container.push_back(vect);
//
//            }
//            if(is_walkable(room, x+1,y)){
//                map[room][x+1][y].from = 'n';
//                map[room][x+1][y].checked = true;
//                if(map[room][x+1][y].name=='C'){
//                    end_room = room;
//                    end_row = x+1;
//                    end_col = y;
//                    found = true;
//                    break;
//                }
//                discovered++;
//                vector<uint32_t> vect{room,x+1,y};
//                container.push_back(vect);
//            }
//            if(is_walkable(room, x,y-1)){
//                map[room][x][y-1].from = 'e';
//                map[room][x][y-1].checked = true;
//                if(map[room][x][y-1].name=='C'){
//                    end_room = room;
//                    end_row = x;
//                    end_col = y-1;
//                    found = true;
//                    break;
//                }
//                discovered++;
//                vector<uint32_t> vect{room,x,y-1};
//                container.push_back(vect);
//
//            }
        }
        if(found)
            break;
    }
}


void CounteesMap::get_mode(int argc, char * argv[]) {
    opterr = false;
    int option_index = 0, option =0;
    
    struct option long_options[] = {

        {"stack", no_argument, nullptr, 's'},
        {"queue", no_argument, nullptr, 'q'},
        {"output", required_argument, nullptr, 'o'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    uint8_t options = 0;
    while ((option = getopt_long(argc, argv, "hsqo:", long_options, &option_index)) != -1) {
        switch (option) {
            case 's':
//                printf("Stack");
                search_mode = true;
                options++;
                break;
            case'h':
                printf("This is a help message");
                exit(0);

            case 'q':
//                printf("queue");
                search_mode = false;
                options++;
                break;
            case 'o':
                if(*optarg=='L')
                    output_mode = false;
                break;
            default:
                cerr<<"Unknown command line option";
                exit(1);
        }
        if(options>1){
            cerr << "Stack or queue can only be specified once";
            exit(1);
        }
        if(options==0){
            cerr<<"Stack or queue must be specified";
            exit(1);
        }
    }

//    if (!search_mode) {
//        printf("illegal input search mode");
//        exit(1);
//    }
//    char output;
//    if(output_mode){
//        output= 'M';
//    }
//    else
//        output= 'L';
//    printf("input mode is %c and output mode is %c\n", search_mode, output);
}

void CounteesMap::read_data(){
    char c;
    string junk;
//    getline(cin, junk);
//    getline(cin, junk);

    
    if(input_mode == 'L'){
        vector<vector<vector<Spot>>> temp_map(total_room,vector<vector<Spot>>(row,vector<Spot>(row, Spot{})));
        map = temp_map;
        char junk;
        uint32_t temp_room;
        uint32_t temp_row;
        uint32_t temp_col;
        char temp_name;
        while(cin>>c){
            if(c !='('){
                cin.ignore(1000, '\n');
                continue;
            }
            
            cin>>temp_room;
            //temp_room = junk-'0';
            cin>>junk;
            cin>>temp_row;
            cin>>junk;
            cin>>temp_col;
            cin>>junk;
            cin>>temp_name;
            cin.ignore(10, '\n');
            if(temp_room>total_room){
                cerr<<"Invalid room number";
                exit(1);
            }
            if(temp_row>row){
                cerr<<"Invalid row number";
                exit(1);
            }
            if(temp_col>row){
                cerr<<"Invalid column number";
                exit(1);
            }
            if(temp_name=='S'){
                start_col = temp_col;
                start_row = temp_row;
                start_room = temp_room;
                
            }
            if(temp_name=='#' || temp_name=='!'){
                map[temp_room][temp_row][temp_col].checked=true;
            }
            if(temp_name!='S' && temp_name!='C' && temp_name!='#' && temp_name!='!' && temp_name!='.'&& !isdigit(temp_name)){
                cerr<<"Invalid Input";
                exit(1);
            }
            map[temp_room][temp_row][temp_col].name = temp_name;
            if(isdigit(temp_name)){
                map[temp_room][temp_row][temp_col].is_pipe=true;
            }
                
        }
    }
    else{
        while(cin>>c){
            if(c=='/'){
                getline(cin, junk);
            }
            else
                break;
        }

        uint32_t room = 0;
        uint32_t cur_row = 0;
        uint32_t cur_pos = 0;
        Spot spot;
        spot.name=c;
        if(c=='S'){
            start_row = cur_row;
            start_col = cur_pos;
            start_room = room;
        }
        if(c!='S' && c!='C' && c!='#' && c!='!' && c!='.'&& !isdigit(c)){
            cerr<<"Invalid Input";
            exit(1);
        }
        if(c=='#' || c=='!'){
            spot.checked=true;
        }
        if(isdigit(c)){
            spot.is_pipe=true;
        }
        map[room][cur_row].push_back(spot);
        cur_pos++;
        if(cur_pos ==row){
            cur_pos = 0;
            cur_row++;
        }
        while(cin>>c){

            if(c == '/'){
//                cin.ignore(1000, '\n');
                getline(cin, junk);
                room++;
                cur_row = 0;
                continue;
            }
            
            Spot spot;
            spot.name=c;
            if(c=='S'){
                start_row = cur_row;
                start_col = cur_pos;
                start_room = room;
            }
            if(c!='S' && c!='C' && c!='#' && c!='!' && c!='.'&& !isdigit(c)){
                cerr<<"Invalid Input";
                exit(1);
            }
            if(c=='#' || c=='!'){
                spot.checked=true;
            }
            if(isdigit(c)){
                spot.is_pipe=true;
            }
            map[room][cur_row].push_back(spot);
            cur_pos++;
            if(cur_pos ==row){
                cur_pos = 0;
                cur_row++;
            }
        }
        
    }
//    for(int i = 0; i<total_room; i++){
//        for(int x=0; x<row;x++){
//            for(int d=0; d<row;d++){
//                printf("%c",map[i][x][d].name);
//            }
//            printf("\n");
//        }
//        printf("New Room %d\n", i);;
//    }
}


int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    char input_mode;
    uint32_t total_room;
    uint32_t row;
    cin>>input_mode;
    cin>>total_room;
    cin>>row;
    vector<vector<vector<Spot>>> map(total_room,vector<vector<Spot>>(row,vector<Spot>()));
    CounteesMap room(map, row, total_room, input_mode);
    room.get_mode(argc, argv);
    room.read_data();
    room.search();
    if(!room.found){
        cout<< "No solution, "<< room.discovered <<" tiles discovered.";
        return 0;
    }
    room.backtrace();
    room.output();
    return 0;
}
