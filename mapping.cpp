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
        Pos pos, pre= pos;
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
        int battery= Battery;
        bool enough= 1;
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
        bool check_battery(Pos simple1, Pos simple2, int step){
            cout<<"battery: "<<battery<<endl;
            if(battery>(simple_path(simple1, simple2)+ step)){
                cout<<"gg"<<endl;
                return 1;
            }
            else
                return 0;
        }
        void update_floor(){
            while(!readyQueue.empty()){
                Pos tmp= readyQueue.front();
                enough= check_battery(tmp, R.pos, 1);
                cout<<"enough= "<<enough<<endl;
                if(enough){
                    battery--;
                    readyQueue.pop();
                    floor[tmp.first][tmp.second].val= 2;
                    Step++;
                    cout<<"Step= "<<Step<<", battery= "<<battery<<" , move to ("<<tmp.first<<", "<<tmp.second<<")"<<endl;
                    waitingStack.push(tmp);
                }
                else{
                    break;
                }
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
            cout<<"simple1: "<<simple1.first<<", "<<simple1.second<<" simple2: "<<simple2.first<<", "<<simple2.second<<endl;
            static int countstep= 0;
            static bool overlay= 0;
            static Pos over= simple1;
            static bool arrive= 0;
            Pos simplenext= simple1;
            int i= 0;
            while(simplenext!= simple2){
                cout<<"simplenext= "<<simplenext.first<<simplenext.second<<endl;
                vector<int>priDir= priority_queue(simple1, simple2);
                simple1= simplenext;
                while(simplenext==simple1&&!overlay){
                    cout<<"i: "<<i<<endl;
                    if(i<priDir.size()){
                        simplenext= get_dir(priDir[i], simple1, overlay, over, countstep);
                        i++;
                    }
                    else{
                        overlay= 1;
                        countstep--;
                    }
                }
                cout<<"simplenext= "<<simplenext.first<<simplenext.second<<endl;
                if(overlay){
                    cout<<"overlay, break"<<endl;
                    break;
                }
                int step= simple_path(simplenext, simple2);
                if(arrive)
                    break;
                if(overlay){
                    if(simple1!= over){
                        cout<<"nonp"<<endl;
                        break;
                    }
                    else{
                        overlay= 0;
                        simplenext= simple1;
                        cout<<"overlay= 0, again"<<endl;
                    }
                }
            }
            if(simplenext== simple2)
                arrive= 1;
            return countstep;
        }

        Pos get_dir(int way, Pos simplenext, bool &overlay, Pos& over, int &countstep){
            Pos tmp;
            cout<<"way= "<<way<<endl;
            switch(way){
                case(UP):{
                    if(simplenext.first>0){
                        tmp= floor[simplenext.first][simplenext.second].get_up();
                        cout<<"tmp= "<<tmp.first<<", "<<tmp.second<<", "<<floor[tmp.first][tmp.second].val<<endl;
                        if(floor[tmp.first][tmp.second].val!= 1){
                            cout<<"can go"<<endl;
                            if(floor[simplenext.first][simplenext.second].pre==tmp){
                                cout<<"overlay"<<endl;
                                overlay= 1;
                                over= tmp;
                                countstep--;
                            }
                            else
                                countstep++;
                            floor[tmp.first][tmp.second].pre= simplenext;
                            cout<<"countstep= "<<countstep<<endl;
                            return tmp;
                        }
                        else{
                            return simplenext;
                        }
                    }
                    else{
                            return simplenext;
                        }
                    break;
                }
                case(DOWN):{
                    if(simplenext.first<row-1){
                        tmp= floor[simplenext.first][simplenext.second].get_down();
                        cout<<"tmp= "<<tmp.first<<", "<<tmp.second<<", "<<floor[tmp.first][tmp.second].val<<endl;
                        if(floor[tmp.first][tmp.second].val!= 1){
                            cout<<"can go"<<endl;
                            if(floor[simplenext.first][simplenext.second].pre==tmp){
                                cout<<"overlay"<<endl;
                                overlay= 1;
                                over= tmp;
                                countstep--;
                            }
                            else
                                countstep++;
                            floor[tmp.first][tmp.second].pre= simplenext;
                            cout<<"countstep= "<<countstep<<endl;
                            return tmp;
                        }
                        else{
                            return simplenext;
                        }
                    }
                    else{
                            return simplenext;
                        }
                    break;
                }
                case(LEFT):{
                    if(simplenext.second>0){
                        tmp= floor[simplenext.first][simplenext.second].get_left();
                        cout<<"tmp= "<<tmp.first<<", "<<tmp.second<<", "<<floor[tmp.first][tmp.second].val<<endl;
                        if(floor[tmp.first][tmp.second].val!= 1){
                            cout<<"can go"<<endl;
                            if(floor[simplenext.first][simplenext.second].pre==tmp){
                                cout<<"overlay"<<endl;
                                overlay= 1;
                                over= tmp;
                                countstep--;
                            }
                            else
                                countstep++;
                            floor[tmp.first][tmp.second].pre= simplenext;
                            cout<<"countstep= "<<countstep<<endl;
                            return tmp;
                        }
                        else{
                            return simplenext;
                        }
                    }
                    else{
                            return simplenext;
                        }
                    break;
                }
                case(RIGHT):{
                    if(simplenext.second<col-1){
                        tmp= floor[simplenext.first][simplenext.second].get_right();
                        cout<<"tmp= "<<tmp.first<<", "<<tmp.second<<", "<<floor[tmp.first][tmp.second].val<<endl;
                        if(floor[tmp.first][tmp.second].val!= 1){
                            cout<<"can go"<<endl;
                            if(floor[simplenext.first][simplenext.second].pre==tmp){
                                cout<<"overlay"<<endl;
                                overlay= 1;
                                over= tmp;
                                countstep--;
                            }
                            else
                                countstep++;
                            floor[tmp.first][tmp.second].pre= simplenext;
                            cout<<"countstep= "<<countstep<<endl;
                            return tmp;
                        }
                        else{
                            return simplenext;
                        }
                    }
                    else{
                            return simplenext;
                        }
                    break;
                }
            }
            return tmp;
        }
        
        vector<int> priority_queue(Pos simple1, Pos simple2){
            vector<int> priDir;
            Pos tmp= floor[simple1.first][simple1.second].pre;
            Point s1= floor[simple1.first][simple1.second];
            if(simple1.first>simple2.first){//up
                if(simple1.second<simple2.second){//right
                    if(tmp== s1.get_up())
                        priDir= {RIGHT, LEFT, DOWN, UP};
                    else if(tmp== s1.get_down())
                        priDir= {RIGHT, UP, LEFT, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {RIGHT, UP, DOWN,};
                    else if(tmp== s1.get_right())
                        priDir= {UP, LEFT, DOWN};
                    else
                        priDir= {RIGHT, UP, LEFT, DOWN};
                }
                else if(simple1.second>simple2.second){//left
                    if(tmp== s1.get_up())
                        priDir= {LEFT, RIGHT, DOWN, UP};
                    else if(tmp== s1.get_down())
                        priDir= {LEFT, UP, RIGHT, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {UP, RIGHT, DOWN,};
                    else if(tmp== s1.get_right())
                        priDir= {LEFT, UP, DOWN};
                    else
                        priDir= {LEFT, UP, RIGHT, DOWN};
                }
                else{
                    if(tmp== s1.get_up())
                        priDir= {RIGHT, LEFT, DOWN, UP};
                    else if(tmp== s1.get_down())
                        priDir= {UP, RIGHT, LEFT, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {UP, RIGHT, DOWN,};
                    else if(tmp== s1.get_right())
                        priDir= {UP, LEFT, DOWN};
                    else
                        priDir= {UP, RIGHT, LEFT, DOWN};
                }
            }
            else if(simple1.first<simple2.first){//down
                if(simple1.second<simple2.second){//right
                    if(tmp== s1.get_up())
                        priDir= {RIGHT, DOWN, LEFT, UP};
                    else if(tmp== s1.get_down())
                        priDir= {RIGHT, LEFT, UP, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {RIGHT, DOWN, UP,};
                    else if(tmp== s1.get_right())
                        priDir= {DOWN, LEFT, UP};
                    else
                        priDir= {RIGHT, DOWN, LEFT, UP};
                }
                else if(simple1.second>simple2.second){//left
                    if(tmp== s1.get_up())
                        priDir= {LEFT, DOWN, RIGHT, UP};
                    else if(tmp== s1.get_down())
                        priDir= {LEFT, RIGHT, UP, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {DOWN, RIGHT, UP,};
                    else if(tmp== s1.get_right())
                        priDir= {LEFT, DOWN, UP};
                    else
                        priDir= {LEFT, DOWN, RIGHT, UP};
                }
                else{
                    if(tmp== s1.get_up())
                        priDir= {DOWN, RIGHT, LEFT, UP};
                    else if(tmp== s1.get_down())
                        priDir= {RIGHT, LEFT, UP, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {DOWN, RIGHT, UP,};
                    else if(tmp== s1.get_right())
                        priDir= {DOWN, LEFT, UP};
                    else
                        priDir= {DOWN, RIGHT, LEFT, UP};
                }
            }
            else{//equal
                if(simple1.second<simple2.second){//right
                    if(tmp== s1.get_up())
                        priDir= {RIGHT, DOWN, LEFT, UP};
                    else if(tmp== s1.get_down())
                        priDir= {RIGHT, UP, LEFT, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {RIGHT, DOWN, UP,};
                    else if(tmp== s1.get_right())
                        priDir= {DOWN, UP, LEFT};
                    else
                        priDir= {RIGHT, DOWN, UP, LEFT};
                }
                else if(simple1.second>simple2.second){//left
                    if(tmp== s1.get_up())
                        priDir= {LEFT, DOWN, RIGHT, UP};
                    else if(tmp== s1.get_down())
                        priDir= {LEFT, UP, RIGHT, DOWN};
                    else if(tmp== s1.get_left())
                        priDir= {DOWN, UP, RIGHT,};
                    else if(tmp== s1.get_right())
                        priDir= {LEFT, DOWN, UP};
                    else
                        priDir= {LEFT, DOWN, UP, RIGHT};
                }
            }
            return priDir;
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
    // fr.waitingStack.push(R.pos);
    // while(!fr.waitingStack.empty()){
    //     Pos tmp= fr.waitingStack.top();
    //     fr.waitingStack.pop();
    //     fr.optimize_queue(fr.floor[tmp.first][tmp.second]);
    //     cout<<"Queue: ";
    //     fr.print_queue();
    //     if(fr.readyQueue.empty()&&!fr.waitingStack.empty()){
    //         Pos simple1= tmp;
    //         while(fr.readyQueue.empty()){
    //             tmp= fr.waitingStack.top();
    //             fr.waitingStack.pop();
    //             fr.optimize_queue(fr.floor[tmp.first][tmp.second]);
    //         }
    //         int stepfromnow= fr.simple_path(simple1, tmp);
    //         int stepformorigingo= fr.simple_path(simple1, R.pos);
    //         int stepformoriginback= fr.simple_path(R.pos, tmp);
    //         if(stepfromnow+fr.simple_path(tmp, R.pos)<=fr.battery&&stepfromnow<(stepformorigingo+ stepformoriginback)){
    //             Step+=stepfromnow;
    //             fr.battery-= stepfromnow;
    //         }
    //         else{
    //             Step+=(stepformorigingo+ stepformoriginback);
    //             fr.battery= Battery- fr.simple_path(R.pos, tmp);
    //         }
    //     }
    //     while(!fr.readyQueue.empty()){
    //         fr.update_floor();
    //         if(!fr.enough){
    //             Step+=fr.simple_path(tmp, R.pos);
    //             int batterylose= fr.simple_path(R.pos, tmp);
    //             fr.battery= Battery-batterylose;
    //             Step+=fr.simple_path(R.pos, tmp);
    //             fr.enough= 1;
    //         }
    //         cout<<"Stack: ";
    //         fr.print_waitingStack();
    //     }
    // }
    // fr.print_floor();
    int kk=fr.simple_path(make_pair(6, 1), make_pair(6, 4));
    cout<<"kk: "<<kk<<endl;
}