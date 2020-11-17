#include<bits/stdc++.h>
using namespace std;

/*global variable*/
typedef pair<int, int> pos;
int row, col, Battery, dir= 1;
queue<int> q;
stack<int> s;
pos R;

/*class*/
class Floor{
    private:
        int **floor;
    public:
        Floor(int **array): floor(array){}
        void print_floor(){
            for(int j= 0; j< row; j++){
                for(int i= 0; i< col; i++)
                    cout<<floor[j][i];
                cout<<endl;
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

;}