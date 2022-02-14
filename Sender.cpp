#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;
int gcd(int a , int b)
{
    int temp;
    while(true)
    {
        temp=a%b;
        if(temp==0)
        return b;
        a=b;
        b=temp;
    }
}
int main()
{
    //random prime numbers
    double p = 3 , q=7 ;

    //first part of public key and private key
    double n=p*q;

    //second part of public key 
    double e=2;
    double phi=(p-1)*(q-1);
    while(e<phi)
    {
        if(gcd(e,phi)==1)break;
        else e++;
    }

    //second part of private key 
    // d = e^-1 mod phi so d*e=1+constant*phi
    int k=2;
    double d=(1+(k*phi))/e;

    //assume that private file is accessed only by receiver 
    ofstream privatefile;
    privatefile.open("privatefile.txt");
    privatefile<<d;
    privatefile.close();

    //get message
    double msg;
    printf("Enter Message to be sent");
    scanf("%lf",&msg);

    //encryption
    double c=pow(msg,e);
    c=fmod(c,n);
    printf("encrypted message = %lf \n",c);
    
    //pipe to send message and n 
    mkfifo("myfifo",0666);
    int fd1=open("myfifo",O_WRONLY);

    write(fd1,&c,sizeof(c));
    write(fd1,&n,sizeof(n));
    close(fd1);

    
}
