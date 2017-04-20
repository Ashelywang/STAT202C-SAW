//
//  main.cpp
//  hw1
//
//  Created by anshu wang on 4/12/17.
//  Copyright © 2017 anshu wang. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <random>
#include <set>
#include <fstream>

#include <cstdlib>
#include <ctime>

using namespace std;
class Result{
public:
    double p;
    int length;
    int lastx;
    int lasty;
    int Matrix[121];
    int n;
    int xlist[122];
    int ylist[122];
    
    Result(double p1, int l1,int last_x,int last_y){
        p = p1;
        length = l1;
        lastx = last_x;
        lasty = last_y;
    }
    
    Result(double p1, int l1,int last_x,int last_y,int * xl,int * yl){
        p = p1;
        length = l1;
        lastx = last_x;
        lasty = last_y;
        for(int i =0;i<l1;i++){
            xlist[i] = xl[i];
            ylist[i] = yl[i];
        }
    }
    
    Result(double p1, int l1,int last_x,int last_y, int* M, int n0){
        p = p1;
        length = l1;
        lastx = last_x;
        lasty = last_y;
        for(int i = 0;i<121;i++){
            Matrix[i] = M[i];
        }
        n = n0;
    }
    
};
class Hist{
public:
    double Matrix[122];
    int num[122];
    Hist(){
        for(int i =0;i<122;i++){
            Matrix[i] = 0;
            num[i] = 0;
        }
    }
    void add(int length, double weight){
        Matrix[length] =  Matrix[length]+ weight;
        num[length]++;
    }
};
bool check_matrix_full(int* Matrix,int n){
    int sum = 0;
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            sum += Matrix[i*n+j];
        }
    }
    if(sum>0){
        return false;
    }
    return true;
}
bool is_feasible(int* Matrix,int stepx, int stepy, int n){
    if(stepx<0 || stepy<0||stepx >=n || stepy >=n){
        return false;
    }
    else if (Matrix[stepx*n+stepy]==0){
        return false;
    }
    else{
        return true;
    }
}
Result generate_SAW(int n){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    int xlist[121]; int ylist[121];
    
    
    int Matrix[n*n];
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            Matrix[i*n+j] = 1;
        }
    }
    Matrix[0]  = 0;
    int length = 0;
    int tmp_x =0; xlist[0] = 0;
    int tmp_y = 0; ylist[0] = 0;
    double p =1.0;
    int next[2][4] = {0,0,1,-1,1,-1,0,0};
    int tmp_cn =0;
    int myset[5];
    int mysetsize = 0;
    while(!check_matrix_full(Matrix, n)){
        tmp_cn = 0;
        mysetsize = 0;
        for(int i =0;i<4;i++){
            myset[i] = -1;
        }
        for(int i =0;i<4;i++){
            if(is_feasible(Matrix, tmp_x+next[0][i], tmp_y+next[1][i], n)){
                tmp_cn+=1;
                myset[mysetsize] = i;
                mysetsize +=1;
            }
        }
        if(tmp_cn==0){
            break;
        }
        else{
            p = p /double(tmp_cn);
        }
        std::uniform_int_distribution<int> distribution(0,tmp_cn-1);
        int rand_i =distribution(gen);
        int newx = next[0][myset[rand_i]]+tmp_x;
        int newy = next[1][myset[rand_i]]+tmp_y;
        Matrix[newx*n + newy] = 0;
        tmp_x = newx;
        tmp_y = newy;
        length ++;
        xlist[length] = tmp_x;
        ylist[length] = tmp_y;
    }
    if(Matrix[n*n-1]==0){
        Result r(p,length,10,10,xlist,ylist);
        return r;
    }
    else{
        Result r(p,length,0,0,xlist,ylist);
        return r;
    }
    
    
}
Result generate_SAW2(int n){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    int xlist[121]; int ylist[121];
    
    int Matrix[n*n];
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            Matrix[i*n+j] = 1;
        }
    }
    Matrix[0]  = 0;
    int length = 0;
    int tmp_x =0; xlist[0] = 0;
    int tmp_y = 0; ylist[0] = 0;
    double p =1.0;
    int next[2][4] = {0,0,1,-1,1,-1,0,0};
    int tmp_cn =0;
    int myset[5];
    int mysetsize = 0;
    while(!check_matrix_full(Matrix, n)){
        tmp_cn = 0;
        mysetsize = 0;
        for(int i =0;i<4;i++){
            myset[i] = -1;
        }
        for(int i =0;i<4;i++){
            if(is_feasible(Matrix, tmp_x+next[0][i], tmp_y+next[1][i], n)){
                tmp_cn+=1;
                myset[mysetsize] = i;
                mysetsize +=1;
            }
        }
        if(tmp_cn==0){
            break;
        }
        else{
            std::uniform_real_distribution<> dis(0,1);
            double xx = dis(gen);
            if(xx<0.05){
                break;
            }
            else{
                p = p /double(tmp_cn) * 0.95;
            }
        }
        std::uniform_int_distribution<int> distribution(0,tmp_cn-1);
        int rand_i =distribution(gen);
        int newx = next[0][myset[rand_i]]+tmp_x;
        int newy = next[1][myset[rand_i]]+tmp_y;
        Matrix[newx*n + newy] = 0;
        tmp_x = newx;
        tmp_y = newy;
        length ++;
        xlist[length] =tmp_x;
        ylist[length] = tmp_y;
    }
    if(Matrix[n*n-1]==0){
        Result r(p,length,10,10,xlist,ylist);
        return r;
    }
    else{
        Result r(p,length,0,0,xlist,ylist);
        return r;
    }
    
}

Result generate_based_on_Matrix(Result r){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    int tmp_cn =0;
    int myset[5];
    int mysetsize = 0;
    int next[2][4] = {0,0,1,-1,1,-1,0,0};
    int tmpx = r.lastx;
    int tmpy = r.lasty;
    int Matrix[121];
    for(int i =0;i<121;i++){
        Matrix[i] = r.Matrix[i];
    }
    double p = r.p;
    int length = r.length;
    while(!check_matrix_full(Matrix, r.n)){
        tmp_cn = 0;
        mysetsize = 0;
        for(int i =0;i<4;i++){
            myset[i] = -1;
        }
        for(int i =0;i<4;i++){
            if(is_feasible(Matrix, tmpx+next[0][i], tmpy+next[1][i], r.n)){
                tmp_cn+=1;
                myset[mysetsize] = i;
                mysetsize +=1;
            }
        }
        if(tmp_cn==0){
            break;
        }
        else{
            p = p /double(tmp_cn);
        }
        std::uniform_int_distribution<int> distribution(0,tmp_cn-1);
        int rand_i =distribution(gen);
        int newx = next[0][myset[rand_i]]+tmpx;
        int newy = next[1][myset[rand_i]]+tmpy;
        Matrix[newx*r.n + newy] = 0;
        tmpx = newx;
        tmpy = newy;
        length++;
    }
    Result r2(p,length,tmpx,tmpy);
    return r2;
}
Result generate_SAW3(int n){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    
    
    int Matrix[n*n];
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            Matrix[i*n+j] = 1;
        }
    }
    Matrix[0]  = 0;
    int length = 0;
    int tmp_x =0;
    int tmp_y = 0;
    double p =1.0;
    int next[2][4] = {0,0,1,-1,1,-1,0,0};
    int tmp_cn =0;
    int myset[5];
    int mysetsize = 0;
    while(!check_matrix_full(Matrix, n)){
        tmp_cn = 0;
        mysetsize = 0;
        for(int i =0;i<4;i++){
            myset[i] = -1;
        }
        for(int i =0;i<4;i++){
            if(is_feasible(Matrix, tmp_x+next[0][i], tmp_y+next[1][i], n)){
                tmp_cn+=1;
                myset[mysetsize] = i;
                mysetsize +=1;
            }
        }
        if(tmp_cn==0){
            break;
        }
        else{
            p = p /double(tmp_cn);
        }
        std::uniform_int_distribution<int> distribution(0,tmp_cn-1);
        int rand_i =distribution(gen);
        int newx = next[0][myset[rand_i]]+tmp_x;
        int newy = next[1][myset[rand_i]]+tmp_y;
        Matrix[newx*n + newy] = 0;
        tmp_x = newx;
        tmp_y = newy;
        length ++;
        if(length >= 50){
            Result r(p,length,tmp_x,tmp_y, Matrix,n);
            return r;
        }
    }
    Result r(p,length,tmp_x,tmp_y);
    return r;
    
}

void problem11(){
    int n = 10000000;
    //double* pvec= new double[10010];
    double p = 0;
    //pvec[0] = 0;
    Hist hist1;
    int maxlength = 0;
    int xlist[122];
    int ylist[122];
    for(int i=1;i<n;i++){
        if(i%1000000==0){
            cout<<i<<"/10000000 Completed!"<<endl;
            cout<<p<<endl;
        }
        Result r = generate_SAW(11);
        p = (p*double(i-1) + 1.0/r.p)/double(i);
        hist1.add(r.length,1.0/r.p);
        if(i%1000 ==0){
           // pvec[i/1000] =p;
        }
        if(r.length> maxlength){
            maxlength = r.length;
            for(int j = 0;j<r.length;j++){
                xlist[j] = r.xlist[j];
                ylist[j] = r.ylist[j];
            }
        }
    }
    /*cout<<"complete computation method 1"<<endl;
    ofstream myfile;
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/p_method1.txt");
    if (myfile.is_open())
    {
        cout<<"opened file1 "<<endl;
        for(int count = 0; count <10000; count ++){
            myfile << pvec[count] << " " ;
        }
        myfile.close();
    }
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/hist1.txt");
    if (myfile.is_open())
    {
        cout<<"opened file hist! "<<endl;
        for(int count = 0; count <122; count ++){
            myfile << hist1.Matrix[count] << " " ;
        }
        myfile.close();
    }*/
    cout<<"For method 1, The longest length is "<<maxlength<<endl;
    for(int j = 0;j<maxlength;j++){
        cout <<xlist[j]<<' ';
    }
    cout<<endl;
    for(int j = 0;j<maxlength;j++){
        cout <<ylist[j]<<' ';
    }
    //delete[] pvec;
}

void problem2(){
    int n = 10000000;
    double* pvec= new double[10010];
    double p =0;
    pvec[0] = 0;
    int xlist[122];
    int ylist[122];
    Hist hist1;
    int maxlength = 0;
    for(int i=1;i<n;i++){
        if(i%1000000==0){
            cout<<i<<"/10000000 Completed!"<<endl;
            cout<<p<<endl;
        }
        Result r = generate_SAW2(11);
        p = (p*double(i-1) + 1.0/r.p)/double(i);
        hist1.add(r.length,1.0/r.p);
        if(i%1000 ==0){
            pvec[i/1000] =p;
        }
        if(r.length> maxlength){
            maxlength = r.length;
            for(int j = 0;j<r.length;j++){
                xlist[j] = r.xlist[j];
                ylist[j] = r.ylist[j];
            }

        }
    }
    
    cout<<"complete computation method 2"<<endl;
    ofstream myfile;
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/p_method21.txt");
    if (myfile.is_open())
    {
        cout<<"opened file1 "<<endl;
        for(int count = 0; count < n/1000; count ++){
            myfile << pvec[count] << " " ;
        }
        myfile.close();
    }
  
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/hist2.txt");
    if (myfile.is_open())
    {
        cout<<"opened file hist! "<<endl;
        for(int count = 0; count <122; count ++){
            myfile << hist1.Matrix[count] << " " ;
        }
        myfile.close();
    }
    cout<<"For method 2, The longest length is "<<maxlength<<endl;
    

    for(int j = 0;j<maxlength;j++){
        cout <<xlist[j]<<' ';
    }
    cout<<endl;
    for(int j = 0;j<maxlength;j++){
        cout <<ylist[j]<<' ';
    }

    delete[] pvec;

}

void problem3(){
    int n = 10000000;
    double* pvec= new double[100100];
    double p =0;
    pvec[0] = 0;
    int i =1;
    Hist hist1;
    int maxlength;
    while(i<n){
        if(i%100000==0){
            cout<<i<<"/10000000 Completed!"<<endl;
            cout << p<<endl;
        }
        Result r = generate_SAW3(11);
        if(r.length>=50){
            for(int j = 0;j<5;j++){
                Result r2 = generate_based_on_Matrix(r);
                p = (p*double(i-1) + 1.0/r2.p/5)/double(i);
                //cout<<r2.length<<endl;
                hist1.add(r2.length,1.0/r2.p);
                i++;
                if(i%1000 ==0){
                    pvec[i/1000] =p;
                }
                if(r2.length >maxlength){
                    maxlength = r2.length;
                }
            }
        }
        else{
            p = (p*double(i-1) + 1.0/r.p)/double(i);
            hist1.add(r.length,1.0/r.p);
            //cout<<r.length<<endl;
            i++;
            if( i%1000 ==0){
                pvec[i/1000] =p;
            }
            
        }
    }
    cout<<"complete computation method 3"<<endl;
    ofstream myfile;
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/p_method31.txt");
    if (myfile.is_open())
    {
        cout<<"opened file6 "<<endl;
        for(int count = 0; count <n/1000; count ++){
            myfile << pvec[count] << " " ;
        }
        myfile.close();
    }
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/hist3.txt");
    if (myfile.is_open())
    {
        cout<<"opened file hist! "<<endl;
        for(int count = 0; count <122; count ++){
            myfile << hist1.Matrix[count] << " " ;
        }
        myfile.close();
    }
    cout<<"For method 3, The longest length is "<<maxlength<<endl;
    

    delete[] pvec;
    

}

void problem41(){
    int n = 10000000;
    double* pvec= new double[10010];
    double p = 0;
    pvec[0] = 0;
    Hist hist1;
    double k;
    for(int i=1;i<n;i++){
        if(i%100000==0){
            cout<<i<<"/10000000 Completed!"<<endl;
            cout<<p<<endl;
        }
        Result r = generate_SAW(11);
        k = 1;
        while(r.lastx!=10){
            r = generate_SAW(11);
            k = k+1;
        }
        
        p = (p*double(i-1) + 1.0/r.p/k)/double(i);
        hist1.add(r.length,1.0/r.p/k);
        
        if(i%1000 ==0){
            pvec[i/1000] =p;
        }
    }
    cout<<"complete computation method 4"<<endl;
    ofstream myfile;
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/p_method4.txt");
    if (myfile.is_open())
    {
        cout<<"opened file1 "<<endl;
        for(int count = 0; count <10000; count ++){
            myfile << pvec[count] << " " ;
        }
        myfile.close();
    }
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/hist4.txt");
    if (myfile.is_open())
    {
        cout<<"opened file hist! "<<endl;
        for(int count = 0; count <122; count ++){
            myfile << hist1.Matrix[count] << " " ;
        }
        myfile.close();
    }
    
    delete[] pvec;
    
}


void problem42(){
    int n = 10000000;
    double* pvec= new double[10010];
    double p = 0;
    pvec[0] = 0;
    Hist hist1;
    for(int i=1;i<n;i++){
        if(i%100000==0){
            cout<<i<<"/10000000 Completed!"<<endl;
            cout<<p<<endl;
        }
        Result r = generate_SAW(11);
        if(r.lastx!=10){
            p = (p*double(i-1) + 0)/double(i);
        }
        else{
            p = (p*double(i-1) + 1.0/r.p)/double(i);
            hist1.add(r.length,1.0/r.p);
        }
        
        if(i%1000 ==0){
            pvec[i/1000] =p;
        }
    }
    cout<<"complete computation method 4"<<endl;
    ofstream myfile;
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/p_method4.txt");
    if (myfile.is_open())
    {
        cout<<"opened file1 "<<endl;
        for(int count = 0; count <10000; count ++){
            myfile << pvec[count] << " " ;
        }
        myfile.close();
    }
    myfile.open("/Users/anshuwang/Documents/Course Files/STAT 202C/hw1/hw1/hw1/hist4.txt");
    if (myfile.is_open())
    {
        cout<<"opened file hist! "<<endl;
        for(int count = 0; count <122; count ++){
            myfile << hist1.Matrix[count] << " " ;
        }
        myfile.close();
    }

    delete[] pvec;
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    //problem3();
    problem11();
    //problem2();
    //problem41();
    return 0;
}
