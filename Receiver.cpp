#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    double msg,d,n;
    //read private key from private file
    ifstream privatefile;
    privatefile.open("privatefile.txt");
    privatefile >> d;
    privatefile.close();
    //pipe to receive message and n 
    mkfifo("myfifo",0666);
    int fd1=open("myfifo",O_RDONLY);
    read(fd1,&msg,sizeof(msg));
    read(fd1,&n,sizeof(n));
    close(fd1);

    printf("msg is %lf\n",msg);
    printf("d is %lf\n",d);

    //decryption
    double m=pow(msg,d);
    m=fmod(m,n);
    printf("decrypted message = %lf\n",m);
}
