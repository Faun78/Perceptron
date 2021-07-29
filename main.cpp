#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <unistd.h>
#include <fstream>
using namespace std;
int height = 10;
int width = 10;
const int NP =50;
float lastx=0;
float lasty=0;
int randomizer=0;
mt19937 mt1(time(0));
int id = getpid();
int sign(float n){
    if(n>=0){
        return 1;
    }else{
        return -1;
    }
}
class Per{
    public:
        float weights[2];
        float lr=0.1;
        Per(){
            //srand(time(0));
            ////srand(time(0));
            for(int j=0;j<(sizeof(weights)/sizeof(*weights));j++){
                float randNum=6666;
                while(randNum<-1 || randNum>1){
                randNum =(mt1()%(999999+100000+1)-100000);
                //cout<<randNum<<endl;
                randNum=randNum/100000;
                //cout<<randNum<<endl<<endl;
                }
                weights[j]=randNum;
                //cout<<"Random Num"<<randNum<<endl;
            }
        }
        int guess(float input[]){
            float sum =0;
            for(int i=0;i<(sizeof(weights)/sizeof(*weights));i++ ){
                sum+=input[i]*weights[i];
                //cout<<sum<<endl;
            }
            int output =sign(sum);
            return output;
        }
        void train(float inputs[],int target){
            int guess1 =guess(inputs);
            int error = target -guess1;
            for(int jj=0;jj<(sizeof(weights)/sizeof(*weights));jj++){
                weights[jj]+=error*inputs[jj]*lr;
                //cout<<error<<endl;
            }
        }
};
class Point{
    public:
        float x;
        float y;
        int label;
        Point(){
            //srand(time(0));
            ////srand(time(0));
            x= (mt1()%(width+0+1)+0);
            y= (mt1()%(height+0+1)+0);
            if(x>y){
                label=1;
            }else{
                label=-1;
            }
        }
        void randomize(){
            //srand(time(0));
            x= (mt1()%(width+1+1)-1);
            y= (mt1()%(height+1+1)-1);
            if(x>y){
                label=1;
            }else{
                label=-1;
            }
        }
};
Per p;
Point points[NP];
int main(){
    ofstream myf("stderr");
fprintf(stderr, "START weights:%d\n",id);

cout<<"Perceptron\n";
for(int iii=0;iii<(sizeof(p.weights)/sizeof(*p.weights));iii++){
    cerr<<p.weights[iii]<<endl;
}
int counter=0;
int learningcycles=0;
int strike=0;
do{
    strike =0;
for(Point p2:points){
    if(p2.x==lastx && p2.y==lasty){
        myf<<p2.x<<" "<<lastx<<endl;
        myf<<p2.y<<" "<<lasty<<endl;
        p2.randomize();
        myf<<p2.x<<" "<<lastx<<endl;
        myf<<p2.y<<" "<<lasty<<endl;
        randomizer++;
        myf<<endl;
    }else{
        lastx=p2.x;
        lasty=p2.y;
        //cerr<<"Nie je to klon"<<endl;
    }
}
lastx=0;
lasty=0;
randomizer=0;
for(Point p3:points){
        if(p3.x==lastx && p3.y==lasty){
        p3.randomize();
        randomizer++;
    }else{
        lastx=p3.x;
        lasty=p3.y;
    }
    float inputs[]={p3.x,p3.y};
        if(p3.label!=p.guess(inputs)){
        counter++;
        strike=-1;
        myf<<endl;
        myf<<p3.x<<endl;
        myf<<p3.y<<endl;
        myf<<p3.label<<endl;
        myf<<p.guess(inputs)<<endl;
        myf<<endl;
    }
    p.train(inputs,p3.label);
    strike++;

    }
    learningcycles++;
}
while(strike!=NP);


cout<<strike<<endl;
for(int iii=0;iii<(sizeof(p.weights)/sizeof(*p.weights));iii++){
    cerr<<p.weights[iii]<<endl;
}
cout<<"Perception end:"<<counter<<"\n";
cout<<learningcycles<<endl;

//cout<<drand48()<<endl;
    return 0;
}