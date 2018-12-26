#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

void mergeSort(char **a,int length);

char ABC[50];

void merge(char **a, char **left, char **right, int len)
{
	int lenL=len/2,lenR=len-lenL;
 	int i=0,j=0,k=0;
 	while(j<lenL&&k<lenR)
 		a[i++]=strCompare(left[j],right[k],ABC)<0?left[j++]:right[k++];
 	while(j<lenL)
 		a[i++]=left[j++];
 	while(k<lenR)
 		a[i++]=right[k++];
}

void getArray(char **b, int left, int right,char **a)
{
	int lenght=right-left;
	for(int i=left,j=0;i<right;i++,j++)
		b[j]=a[i];
}

void divide(char **left, char **right, char **a, int len)
{
	int m=len/2;
	getArray(left,0,m,a);
	getArray(right,m,len,a);
}

void sentDataFrom(int *from, char **message, int len)
{
	write(from[1],message, sizeof(*message)*sizeof(char)*(len));
}

int readDataIn(int *in, char **message, int len)
{
	return read(in[0],message,sizeof(*message)*sizeof(char)*len);
}

int goToSide(char **sideArr, int *pipe, int len)
{
	close(pipe[0]);
	mergeSort(sideArr,len);
	sentDataFrom(pipe,sideArr,len);
    close(pipe[1]);
    exit(0);
}

void waitForChild(char **a, int *pipeWithChild, int len)
{
	close(pipeWithChild[1]);
    if(readDataIn(pipeWithChild, a,len))
		wait(NULL);
	close(pipeWithChild[0]);
}

void mergeSort(char **a,int length)
{
	if(length>1)
	{
		int middle=length/2;
		char *leftArray[middle], *rightArray[length-middle];

		divide(leftArray,rightArray,a,length);

		int right[2],left[2];
		pipe(right);
		pipe(left);

		pid_t pidLeft, pidRight;

		pidLeft=fork();
		if(!pidLeft)
		{
			goToSide(leftArray,left,middle);
        }
        else if(pidLeft>0)
        {
        	waitForChild(leftArray,left,middle);
	        pidRight=fork();
	        if(!pidRight)
	        {
	        	goToSide(rightArray,right,length-middle);
	        }
	        else if(pidRight>0)
	        {
	        	waitForChild(rightArray,right,length-middle);
				merge(a,leftArray,rightArray,length);
        	}
		}
	}
}

int main(int argc, char const *argv[])
{
	char **words=(char**)malloc(sizeof((char*)malloc(sizeof(char)))*255);
	for(int i=0;i<255;i++)
		words[i]=(char*)malloc(sizeof(char)*255);
	readAlphabet(argv[1],ABC);
	int len=readStrings(argv[2], words);
	mergeSort(words, len);
	writeStrings(words,len);
	return 0;
}