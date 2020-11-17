#include<bits/stdc++.h>
using namespace std;

/*global variable*/
typedef pair<int, int> Pos;
typedef queue<Pos> Queue;
typedef stack<Pos> Stack;
int row, col, Battery, dir= 1;

/*class*/
class Point{
    private:
        Pos up, down, left, right;
    public:
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
    private:
        int **floor;
        Queue readyQueue;
        Stack waitingStack;
    public:
        Floor(int **array): floor(array){}
        void print_floor(){
            for(int j= 0; j< row; j++){
                for(int i= 0; i< col; i++)
                    cout<<floor[j][i];
                cout<<endl;
            }
        }
        void around_point(Pos ptr){}
        void print_readyQueue(){
            Queue copy= readyQueue;
            while(!copy.empty()){
                cout<<"("<<copy.front().first<<", "<<copy.front().second<<") ";
                copy.pop();
            }
        }
};

/*main function*/
int main(int argc, char *argv[]){

    //load in the test case
    string filename= argv[1];
    fstream ifile(filename, ios::in);

    ifile>> row>> col>> Battery;

    //initialize a floor
    int **floor= new int*[row];
    for(int i= 0; i<row; i++)
        floor[i]= new int[col];
    
    for(int j= 0; j<row; j++){
        for(int i= 0; i<col&& !ifile.eof(); i++){
            char c;
            ifile>> c;
            floor[j][i]= c-'0';
            if(c== 'R')
                R.pos= make_pair(j, i);
        }
    }
    Floor fr(floor);
    // fr.around_point(R);
    // fr.print_readyQueue();
    // cout<<"R= "<<R.pos.first<<", "<<R.pos.second<<endl;
    // cout<<"R.right= "<<R.get_right().first<<", "<<R.get_right().second<<endl;
;}