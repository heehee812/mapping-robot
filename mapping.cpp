#include<bits/stdc++.h>
using namespace std;

/*global variable*/
typedef pair<int, int> Pos;
typedef queue<Pos> Queue;
typedef stack<Pos> Stack;
int row, col, Battery, dir= 1;
Pos R;

/*class*/
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
        void around_point(Pos ptr){
            // //decide what direction should go
            // if(ptr.first!= row-1){
            //     cout<<"ptr.first!= bottom"<<endl;
            //     if(floor[ptr.first+1][ptr.second]== 0){
            //         cout<<ptr.first+1<<","<<ptr.second<<endl;
            //         readyQueue.push(make_pair(ptr.first+1, ptr.second));
            //         if(dir){
            //             if(floor[ptr.first+1][ptr.second-1]== 0){
            //                 cout<<ptr.first+1<<","<<ptr.second-1<<endl;
            //                 readyQueue.push(make_pair(ptr.first-1, ptr.second-1));
            //             }
            //         }
            //         else{
            //             if(floor[ptr.first+1][ptr.second+1]== 0){
            //                 cout<<ptr.first+1<<","<<ptr.second+1<<endl;
            //                 readyQueue.push(make_pair(ptr.first-1, ptr.second+1));
            //             }
            //         }
            //     }
            // }
            // if(dir){
            //     cout<<"dir=1"<<endl;
            //     if(floor[ptr.first][ptr.second-1]== 0){
            //         cout<<ptr.first<<","<<ptr.second-1<<endl;
            //         readyQueue.push(make_pair(ptr.first, ptr.second-1));
            //         if(floor[ptr.first-1][ptr.second-1]== 0){
            //             cout<<ptr.first-1<<","<<ptr.second-1<<endl;
            //             readyQueue.push(make_pair(ptr.first-1, ptr.second-1));
            //         }
            //     }
            //     if(floor[ptr.first-1][ptr.second]== 0){
            //         cout<<ptr.first-1<<","<<ptr.second<<endl;
            //         readyQueue.push(make_pair(ptr.first-1, ptr.second));
            //         if(floor[ptr.first-1][ptr.second+1]== 0){
            //             cout<<ptr.first-1<<","<<ptr.second+1<<endl;
            //             readyQueue.push(make_pair(ptr.first-1, ptr.second+1));
            //         }
            //     }
            //     if(floor[ptr.first][ptr.second+1]== 0){
            //         cout<<ptr.first<<","<<ptr.second+1<<endl;
            //         readyQueue.push(make_pair(ptr.first, ptr.second+1));
            //         if(ptr.first!= 0)
            //             if(floor[ptr.first+1][ptr.second+1]== 0){
            //                 cout<<ptr.first+1<<","<<ptr.second+1<<endl;
            //                 readyQueue.push(make_pair(ptr.first+1, ptr.second+1));
            //             }
            //     }
            // }
            // else{
            //     if(floor[ptr.first][ptr.second+1]== 0){
            //         cout<<ptr.first<<","<<ptr.second-1<<endl;
            //         readyQueue.push(make_pair(ptr.first, ptr.second+1));
            //         if(floor[ptr.first-1][ptr.second]== 0){
            //             cout<<ptr.first-1<<","<<ptr.second<<endl;
            //             readyQueue.push(make_pair(ptr.first-1, ptr.second+1));
            //         }
            //     }
            //     if(floor[ptr.first-1][ptr.second]== 0){
            //         cout<<ptr.first-1<<","<<ptr.second<<endl;
            //         readyQueue.push(make_pair(ptr.first-1, ptr.second));
            //         if(floor[ptr.first-1][ptr.second-1]== 0){
            //             cout<<ptr.first-1<<","<<ptr.second-1<<endl;
            //             readyQueue.push(make_pair(ptr.first-1, ptr.second-1));
            //         }
            //     }
            //     if(floor[ptr.first][ptr.second-1]== 0){
            //         cout<<ptr.first<<","<<ptr.second-1<<endl;
            //         readyQueue.push(make_pair(ptr.first, ptr.second-1));
            //         if(ptr.first!= 0)
            //             if(floor[ptr.first+1][ptr.second-1]== 0){
            //                 cout<<ptr.first+1<<","<<ptr.second-1<<endl;
            //                 readyQueue.push(make_pair(ptr.first+1, ptr.second-1));
            //             }
            //     }
            // }
        }
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
                R= make_pair(j, i);
        }
    }
    Floor fr(floor);
    fr.around_point(make_pair(3, 4));
    // fr.print_readyQueue();
;}