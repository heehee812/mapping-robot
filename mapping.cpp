#include<bits/stdc++.h>
using namespace std;

/*global variable*/
int row, col, Battery;

/*main function*/
int main(int argc, char *argv[]){

    //load in the test case
    string filename= argv[1];
    fstream ifile(filename, ios::in);

    //get the floor size
    ifile>> row>> col>> Battery;
    cout<< row<< ", "<< col<< ", "<< Battery<< endl;
;}