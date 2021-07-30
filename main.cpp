#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <unistd.h>
#include <fstream>
using namespace std;
int height = 100;
int width = 100;
const int NP =1000;
double lastx=0;
double lasty=0;
int randomizer=0;
mt19937 mt1(time(0));
int id = getpid();
int sign(double n){
    if(n>=0){
        return 1;
    }else{
        return -1;
    }
}
double line(double x){
    return 0.89*x-0.1;
}

class Per{
    public:
        vector <double> weights;
        double lr=0.01;
        Per(int n){
            //srand(time(0));
            ////srand(time(0));
            for(int j=0;j<n;j++){
                double randNum=6666;
                while(randNum<-1 || randNum>1){
                randNum =(mt1()%(999999+100000+1)-100000);
                randNum=randNum/100000;
                //cout<<randNum<<endl<<endl;
                }
                weights.push_back(randNum);
                //cout<<"Random Num"<<randNum<<endl;
            }
        }
        int guess(double input[]){
            double sum =0;
            for(int i=0;i<weights.size();i++ ){
                sum+=input[i]*weights[i];
                //cout<<sum<<endl;
            }
            int output =sign(sum);
            return output;
        }
        void train(double inputs[],int target){
            int guess1 =guess(inputs);
            int error = target -guess1;
            for(int jj=0;jj<weights.size();jj++){
                weights[jj]+=error*inputs[jj]*lr;
                //cout<<error<<endl;
            }
        }
};
class Point{
    public:
        double x;
        double y;
        double bias;
        int label;
        Point(){
            //srand(time(0));
            ////srand(time(0));
            bias=1;
            do{
            x =(mt1()%(999999+100000+1)-100000);
            x=x/100000;
            y =(mt1()%(999999+100000+1)-100000);
            y=y/100000;
            }while(x>1 ||x<-1||y>1||y<-1);
            int gen =mt1()%((1-1+1)+1)+mt1()%((1-1+1)+1);
            if(gen==0){
                x=x*-1;
                //cout<<"Som ykladny\n";
            }else if(gen==1){
                y=y*-1;
                //cout<<"Som xkladny\n";
            }else{
                
            }
            double liney = line(x);
            if(y>liney){
                label=1;
            }else{
                label=-1;
            }
        }
        Point(double x_,double y_){
            x=x_;
            y=y_;
            label=1;
            bias=1;
        }
       
};
Per p(3);
//Point ConfusedUngaBunga(0.3,0.4);
Point points[NP];
int main(){
    ofstream myf("stderr");
fprintf(stderr, "START weights:%d\n",id);

cout<<"Perceptron\n";
for(int iii=0;iii<p.weights.size();iii++){
    cerr<<p.weights[iii]<<endl;
}
int counter=0;
int learningcycles=0;
int strike=0;
do{
    strike =0;
randomizer=0;
for(Point p3:points){
    double inputs[]={p3.x,p3.y,p3.bias};
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
    if(learningcycles>NP*3){
        cout<<"Nepodarilo sa zatiahol som za brzdu\n";
        break;
    }
}
while(strike!=NP);


cout<<strike<<endl;
for(int iii=0;iii<p.weights.size();iii++){
    cerr<<p.weights[iii]<<endl;
}
cout<<"Perception end:"<<counter<<"\n";
cout<<learningcycles<<endl<<endl;
/*for(int t=0;t<10;t++){
    cout<<mt1()%((1-1+1)+1)<<endl;
}*/


//cout<<drand48()<<endl;
    return 0;
}