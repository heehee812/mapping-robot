#include<bits/stdc++.h>
using namespace std;

/*global variable*/
enum WAY{UP= 1, DOWN, LEFT, RIGHT};
typedef pair<int, int> Pos;
typedef queue<Pos> Queue;
typedef stack<Pos> Stack;
int row, col, Battery, dir= 1;

/*class*/
class Point{
    private:
        Pos up, down, left, right;
    public:
        int val;
        Pos pos;
        Pos get_up(){ 
            up= make_pair(pos.first-1, pos.second);
            return up;
        }
        Pos get_down(){
            down= make_pair(pos.first+1, pos.second);
            return down;
        }
        Pos get_left(){
            left= make_pair(pos.first, pos.second-1);
            return left;
        }
        Pos get_right(){
            right= make_pair(pos.first, pos.second+1);
            return right;
        }
};
Point R;

class Floor{
    public:
        Queue readyQueue;
        Stack waitingStack;
        Point **floor;
        Floor(){
            floor= new Point*[row];
            for(int i= 0; i<row; i++){
                floor[i]= new Point[col];
                for(int j= 0; j<col; j++)
                    floor[i][j].pos= make_pair(i, j);
            }
        }
        void print_floor(){
            for(int j= 0; j< row; j++){
                for(int i= 0; i< col; i++)
                    cout<<floor[j][i].val;
                cout<<endl;
            }
        }
        void around_point(Point ptr, int way){
            switch(way){
                case(UP):{
                    if(floor[ptr.get_up().first][ptr.get_up().second].val== 0){
                            readyQueue.push(ptr.get_up());
                            if(dir){
                                if(floor[ptr.get_up().first][ptr.get_up().second+1].val== 0){
                                    readyQueue.push(make_pair(ptr.get_up().first, ptr.get_up().second+1));
                                    around_point(ptr, RIGHT);
                                }
                            }
                            else{
                                if(floor[ptr.get_up().first][ptr.get_up().second-1].val== 0){
                                    readyQueue.push(make_pair(ptr.get_up().first, ptr.get_up().second-1));
                                    around_point(ptr, LEFT);
                                }
                            }
                    }
                    else if(readyQueue.empty()){
                        if(dir)
                            around_point(ptr, RIGHT);
                        else
                            around_point(ptr, LEFT);
                    }
                    break;
                }
                case(DOWN):{
                    if(ptr.pos.first!= row-1){
                        if(floor[ptr.get_down().first][ptr.get_down().second].val== 0){
                            readyQueue.push(ptr.get_down());
                            if(dir){
                                if(floor[ptr.get_down().first][ptr.get_down().second-1].val== 0){
                                    readyQueue.push(make_pair(ptr.get_down().first, ptr.get_down().second-1));
                                    around_point(ptr, LEFT);
                                }
                            }
                            else{
                                if(floor[ptr.get_down().first][ptr.get_down().second+1].val== 0){
                                    readyQueue.push(make_pair(ptr.get_down().first, ptr.get_down().second+1));
                                    around_point(ptr, RIGHT);
                                }
                            }
                        }
                        else if(readyQueue.empty()){
                            if(dir)
                                around_point(ptr, LEFT);
                            else
                                around_point(ptr, RIGHT);
                        }
                    }
                    else{
                        if(dir)
                            around_point(ptr, LEFT);
                        else
                            around_point(ptr, RIGHT);
                    }
                    break;
                }
                case(LEFT):{
                    if(floor[ptr.get_left().first][ptr.get_left().second].val== 0){
                            readyQueue.push(ptr.get_left());
                            if(dir){
                                if(floor[ptr.get_left().first-1][ptr.get_left().second].val== 0){
                                    readyQueue.push(make_pair(ptr.get_left().first-1, ptr.get_left().second));
                                    around_point(ptr, UP);
                                }
                            }
                            else{
                                if(ptr.pos.first!= row-1){
                                    if(floor[ptr.get_left().first+1][ptr.get_left().second].val== 0){
                                        readyQueue.push(make_pair(ptr.get_left().first+1, ptr.get_left().second));
                                    }
                                }
                            }
                    }
                    else if(readyQueue.empty()&&dir){
                        if(dir)
                            around_point(ptr, UP);
                    }
                    break;
                }
                case(RIGHT):{
                    if(floor[ptr.get_right().first][ptr.get_right().second].val== 0){
                            readyQueue.push(ptr.get_right());
                            if(dir){
                                if(ptr.pos.first!= row-1){
                                    if(floor[ptr.get_right().first+1][ptr.get_right().second].val== 0){
                                    readyQueue.push(make_pair(ptr.get_right().first+1, ptr.get_right().second));
                                    }
                                }
                            }
                            else{
                                if(floor[ptr.get_right().first-1][ptr.get_right().second].val== 0){
                                    readyQueue.push(make_pair(ptr.get_right().first-1, ptr.get_right().second));
                                    around_point(ptr, UP);
                                }
                            }
                    }
                    else if(readyQueue.empty()&&!dir){
                        around_point(ptr, UP);
                    }
                    break;
                }
                default: break;
            }
        }
        void print_readyQueue(){
            Queue copy= readyQueue;
            while(!copy.empty()){
                cout<<"("<<copy.front().first<<", "<<copy.front().second<<") ";
                copy.pop();
            }
            cout<<endl;
        }
        void update_floor(){
            while(!readyQueue.empty()){
                Pos tmp= readyQueue.front();
                readyQueue.pop();
                floor[tmp.first][tmp.second].val= 2;
                waitingStack.push(tmp);
            }
        }
        void print_waitingStack(){
            Stack copy= waitingStack;
            while(!copy.empty()){
                cout<<"("<<copy.top().first<<", "<<copy.top().second<<") ";
                copy.pop();
            }
            cout<<endl;
        }
};

/*main function*/
int main(int argc, char *argv[]){

    //load in the test case
    string filename= argv[1];
    fstream ifile(filename, ios::in);

    ifile>> row>> col>> Battery;

    //initialize a floor
    Floor fr;
    for(int j= 0; j<row; j++){
        for(int i= 0; i<col&& !ifile.eof(); i++){
            char c;
            ifile>> c;
            fr.floor[j][i].val= c-'0';
            if(c== 'R')
                R.pos= make_pair(j, i);
        }
    }

    fr.waitingStack.push(R.pos);
    while(!fr.waitingStack.empty()){
        //find the simple path
        Pos tmp= fr.waitingStack.top();
        fr.waitingStack.pop();
        dir= !dir;
        fr.around_point(fr.floor[tmp.first][tmp.second], DOWN);
        cout<<"queue: ";
        fr.print_readyQueue();
        if(!fr.readyQueue.empty()){
            fr.update_floor();
            cout<<"stack: ";
            fr.print_waitingStack();
        }
    }
}