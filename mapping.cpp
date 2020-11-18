#include<bits/stdc++.h>
using namespace std;

/*global variable*/
enum WAY{UP= 1, DOWN, LEFT, RIGHT};
typedef pair<int, int> Pos;
typedef queue<Pos> Queue;
typedef stack<Pos> Stack;
int row, col, Battery, Step= 0;

/*class*/
class Point{
    private:
        Pos up, down, left, right;
    public:
        int val, invalid= 0;
        Pos pos, pre;
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
        void around_point(Point ptr, int way, Queue &queue, int dir){
            switch(way){
                case(UP):{
                    if(ptr.pos.first!= 0){
                        if(floor[ptr.get_up().first][ptr.get_up().second].val== 0){
                                queue.push(ptr.get_up());
                                if(dir){
                                    if(floor[ptr.get_up().first][ptr.get_up().second+1].val== 0){
                                        queue.push(make_pair(ptr.get_up().first, ptr.get_up().second+1));
                                        around_point(ptr, RIGHT, queue, dir);
                                    }
                                }
                                else{
                                    if(floor[ptr.get_up().first][ptr.get_up().second-1].val== 0){
                                        queue.push(make_pair(ptr.get_up().first, ptr.get_up().second-1));
                                        around_point(ptr, LEFT, queue, dir);
                                    }
                                }
                        }
                        else if(queue.empty()){
                            if(dir)
                                around_point(ptr, RIGHT, queue, dir);
                            else
                                around_point(ptr, LEFT, queue, dir);
                        }
                    }
                    else if(queue.empty()){
                        if(dir)
                            around_point(ptr, RIGHT, queue, dir);
                        else
                            around_point(ptr, LEFT, queue, dir);
                    }
                    break;
                }
                case(DOWN):{
                    if(ptr.pos.first!= row-1){
                        if(floor[ptr.get_down().first][ptr.get_down().second].val== 0){
                            queue.push(ptr.get_down());
                            if(dir){
                                if(floor[ptr.get_down().first][ptr.get_down().second-1].val== 0){
                                    queue.push(make_pair(ptr.get_down().first, ptr.get_down().second-1));
                                    around_point(ptr, LEFT, queue, dir);
                                }
                            }
                            else{
                                if(floor[ptr.get_down().first][ptr.get_down().second+1].val== 0){
                                    queue.push(make_pair(ptr.get_down().first, ptr.get_down().second+1));
                                    around_point(ptr, RIGHT, queue, dir);
                                }
                            }
                        }
                        else if(queue.empty()){
                            if(dir)
                                around_point(ptr, LEFT, queue, dir);
                            else
                                around_point(ptr, RIGHT, queue, dir);
                        }
                    }
                    else if(queue.empty()){
                        if(dir)
                            around_point(ptr, LEFT, queue, dir);
                        else
                            around_point(ptr, RIGHT, queue, dir);
                    }
                    break;
                }
                case(LEFT):{
                    if(ptr.pos.second!= 0){
                        if(floor[ptr.get_left().first][ptr.get_left().second].val== 0){
                                queue.push(ptr.get_left());
                                if(dir){
                                    if(floor[ptr.get_left().first-1][ptr.get_left().second].val== 0){
                                        queue.push(make_pair(ptr.get_left().first-1, ptr.get_left().second));
                                        around_point(ptr, UP, queue, dir);
                                    }
                                }
                                else{
                                    if(ptr.pos.first!= row-1){
                                        if(floor[ptr.get_left().first+1][ptr.get_left().second].val== 0){
                                            queue.push(make_pair(ptr.get_left().first+1, ptr.get_left().second));
                                        }
                                    }
                                }
                        }
                        else if(queue.empty()&&dir){
                            if(dir)
                                around_point(ptr, UP, queue, dir);
                        }
                    }
                    else if(queue.empty()&& dir){
                            around_point(ptr, UP, queue, dir);
                    }
                    break;
                }
                case(RIGHT):{
                    if(ptr.pos.second!= col-1){
                        if(floor[ptr.get_right().first][ptr.get_right().second].val== 0){
                                queue.push(ptr.get_right());
                                if(dir){
                                    if(ptr.pos.first!= row-1){
                                        if(floor[ptr.get_right().first+1][ptr.get_right().second].val== 0){
                                        queue.push(make_pair(ptr.get_right().first+1, ptr.get_right().second));
                                        }
                                    }
                                }
                                else{
                                    if(floor[ptr.get_right().first-1][ptr.get_right().second].val== 0){
                                        queue.push(make_pair(ptr.get_right().first-1, ptr.get_right().second));
                                        around_point(ptr, UP, queue, dir);
                                    }
                                }
                        }
                        else if(queue.empty()&&!dir){
                            around_point(ptr, UP, queue, dir);
                        }
                    }
                    else if(queue.empty()&&!dir){
                        around_point(ptr, UP, queue, dir);
                    }
                    break;
                }
                default: break;
            }
        }
        void optimize_queue(Point ptr){
            Queue dirqueue[4], queue[4];
            int dir= 1;
            for(int i= 0; i<4; i++){
                around_point(ptr, i+1, dirqueue[i], dir);
                around_point(ptr, i+1, queue[i], !dir);
                if(i==0)
                    readyQueue= dirqueue[i];
                else{
                    if(dirqueue[i].size()>readyQueue.size())
                        readyQueue= dirqueue[i];
                    if(queue[i].size()>readyQueue.size())
                        readyQueue= queue[i];
                }
            }
        }
        void print_queue(){
            Queue copy= readyQueue;
            while(!copy.empty()){
                cout<<"("<<copy.front().first<<", "<<copy.front().second<<")";
                copy.pop();
            }
            cout<<endl;
        }
        void update_floor(){
            while(!readyQueue.empty()){
                Pos tmp= readyQueue.front();
                readyQueue.pop();
                floor[tmp.first][tmp.second].val= 2;
                Step++;
                cout<<"Step= "<<Step<<" , move to ("<<tmp.first<<", "<<tmp.second<<")"<<endl;
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
        int simple_path(Pos simple1, Pos simple2){
            int countstep= 0;
            floor[simple1.first][simple1.second].pre= simple1;
            // Pos simple1Pre= simple1;
            while(simple1!= simple2){
                vector<int> priDir= priority_queue(simple1, simple2);
                // for(auto i: priDir)
                //     cout<<i<<" ";
                // cout<<endl;
                int i= 0;
                while(walk(priDir[i], simple1, countstep)&&i<4){
                    i++;
                }
            }
            // cout<<"coutstep= "<<countstep<<endl;
            return countstep;
        }
        vector<int> priority_queue(Pos simple1, Pos simple2){
            vector<int> priDir;
            if(simple1.first>simple2.first){//up
                if(simple1.second<simple2.second)//right
                    priDir= {RIGHT, UP, LEFT, DOWN};
                else if(simple1.second>simple2.second)//left
                    priDir= {LEFT, UP, RIGHT, DOWN};
                else
                    priDir= {UP, RIGHT, LEFT, DOWN};
            }
            else if(simple1.first<simple2.first){//down
                if(simple1.second<simple2.second)//right
                    priDir= {RIGHT, DOWN, LEFT, UP};
                else if(simple1.second>simple2.second)//left
                    priDir= {LEFT, DOWN, RIGHT, UP};
                else
                    priDir= {DOWN, RIGHT, LEFT, UP};
            }
            else{//equal
                if(simple1.second<simple2.second)//right
                    priDir= {RIGHT, DOWN, UP, LEFT};
                else if(simple1.second>simple2.second)//left
                    priDir= {LEFT, DOWN, UP, RIGHT};
            }
            return priDir;
        }
        int walk(int i, Pos &simple1, int &countstep){
            int wall= 1;
            Pos tmp;
            switch(i){
                case UP:{
                    if(simple1.first!= 0){
                        tmp= floor[simple1.first][simple1.second].get_up();
                        if(floor[tmp.first][tmp.second].val!= 1&& !floor[tmp.first][tmp.second].invalid){
                            if(tmp!= floor[simple1.first][simple1.second].pre){
                                wall= 0;
                                countstep++;
                                floor[tmp.first][tmp.second].pre= simple1;
                                simple1= tmp;
                            }
                            else{
                                simple1= tmp;
                                countstep--;
                                tmp= floor[simple1.first][simple1.second].get_left();
                                floor[tmp.first][tmp.second].invalid= 1;
                            }
                        }
                    }
                    break;
                }
                case DOWN:{
                    if(simple1.first!= row-1){
                        tmp= floor[simple1.first][simple1.second].get_down();
                        if(floor[tmp.first][tmp.second].val!= 1&& !floor[tmp.first][tmp.second].invalid){
                            if(tmp!= floor[simple1.first][simple1.second].pre){
                                wall= 0;
                                countstep++;
                                floor[tmp.first][tmp.second].pre= simple1;
                                simple1= tmp;
                            }
                            else{
                                simple1= tmp;
                                countstep--;
                                tmp= floor[simple1.first][simple1.second].get_left();
                                floor[tmp.first][tmp.second].invalid= 1;
                            }
                        }
                    }
                    break;
                }
                case LEFT:{
                    if(simple1.first!= 0){
                        tmp= floor[simple1.first][simple1.second].get_left();
                        if(floor[tmp.first][tmp.second].val!= 1&& !floor[tmp.first][tmp.second].invalid){
                            if(tmp!= floor[simple1.first][simple1.second].pre){
                                wall= 0;
                                countstep++;
                                floor[tmp.first][tmp.second].pre= simple1;
                                simple1= tmp;
                            }
                            else{
                                simple1= tmp;
                                countstep--;
                                tmp= floor[simple1.first][simple1.second].get_left();
                                floor[tmp.first][tmp.second].invalid= 1;
                            }
                        }
                    }
                    break;
                }
                case RIGHT:{
                    if(simple1.first!= col-1){
                        tmp= floor[simple1.first][simple1.second].get_right();
                        if(floor[tmp.first][tmp.second].val!= 1&& !floor[tmp.first][tmp.second].invalid){
                            if(tmp!= floor[simple1.first][simple1.second].pre){
                                wall= 0;
                                countstep++;
                                floor[tmp.first][tmp.second].pre= simple1;
                                simple1= tmp;
                            }
                            else{
                                simple1= tmp;
                                countstep--;
                                tmp= floor[simple1.first][simple1.second].get_left();
                                floor[tmp.first][tmp.second].invalid= 1;
                            }
                        }
                    }
                    break;
                }
                default: break;
            }
            return wall;
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

    //trace the floor
    fr.waitingStack.push(R.pos);
    while(!fr.waitingStack.empty()){
        //find the simple path
        Pos tmp= fr.waitingStack.top();
        // cout<<"Step= "<<Step<<" , move to ("<<tmp.first<<", "<<tmp.second<<")"<<endl;
        fr.waitingStack.pop();
        fr.optimize_queue(fr.floor[tmp.first][tmp.second]);
        cout<<"Queue: ";
        fr.print_queue();
        if(fr.readyQueue.empty()&&!fr.waitingStack.empty()){
            Pos simple1= tmp;
            while(fr.readyQueue.empty()){
                tmp= fr.waitingStack.top();
                fr.waitingStack.pop();
                fr.optimize_queue(fr.floor[tmp.first][tmp.second]);
            }
            Step+=fr.simple_path(simple1, tmp);
        }
        fr.update_floor();
        cout<<"Stack: ";
        fr.print_waitingStack();
    }
    fr.print_floor();
}