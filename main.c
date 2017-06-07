#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int a[250][4000];

int countRow,countCol;
int randomRow,randomCol;

void randomize();
void karger(int node1,int node2);
void replaceAllNodes(int nod1,int nod2);
void selfloops(int sizeMergeNode,int nodeLoop);
void removeNode2(int nod);
void showArray();
void showResult();

void randomize(){

  while(countRow>2)
 {
    int i=0;
    srand(time(NULL));
    randomRow=(rand()%(countRow-1));

    while(a[randomRow][i]!=0)
   {
       i++;
   }
   countCol=i-1;
   randomCol=(rand()%countCol+1);

   karger(a[randomRow][0],a[randomRow][randomCol]);
 }
}

void replaceAllNodes(int nod1,int nod2){

int z;
int replace=1;

for(z=0;z<countRow;z++)
{
    while(a[z][replace]!=0)
 {
    if(a[z][replace]==nod2)
    {
       a[z][replace]=nod1;
    }
       replace++;
 }
 replace=1;
}
}

void selfloops(int sizeMergeNode,int nodeLoop){

    int i,j,k,size;
    size=sizeMergeNode;

    for(i=0;i<size;i++){

       for(j=i+1;j<size;){
        if(a[nodeLoop][j]==a[nodeLoop][0]){
           for(k=j;k<size;k++)
           {
            a[nodeLoop][k]=a[nodeLoop][k+1];
           }
           a[nodeLoop][k]=0;
           size--;
        }else
        j++;
       }
    }
}

void removeNode2(int nod){

int z;
int x=0;
int start;

for(z=0;z<countRow;z++)
{
    if(a[z][0]==nod)
    {
      for(start=1;start<countRow-z;start++)
      {
          while(a[z+start][x]!=0)
        {
          a[z+start-1][x]=a[z+start][x];
           x++;
        }
          a[z+start-1][x]=0;
          x=0;
      }
      countRow--;
    }
}
}//end of function

void karger(int node1,int node2){

int i=0;
int j=0;
int v=0;
int k=0;
int count;
int start=0;

while(a[i][0]!=node1){
    i++;
}

while(a[i][v]!=0)//size of node1
   {
       v++;
   }

while(a[j][0]!=node2){
    j++;
}

 while(a[j][k]!=0)//size of node2
   {
       k++;
   }

for(count=v;count<v+k;count++){  //merging
    a[i][count]=a[j][start];
    start++;
}
a[i][count]=0;

//scan their lists and replace all occurrence of node2 as node1

  replaceAllNodes(node1,node2);

//scan node1 list and remove self loops

   selfloops(v+k,i); //v+k is merge size

//remove edge
removeNode2(node2);
showArray();
}

void showArray(){

FILE *temp;
int z;
int x=0;

temp=fopen("temp.txt","w");

   for(z=0;z<countRow;z++)
    {
          while(a[z][x]!=0)
        {
          fprintf(temp,"%ld ",a[z][x]);
           x++;
        }
          fprintf(temp,"\n");
          x=0;
    }

fclose(temp);
}

void showResult(){

int x=0;
int minCut;

          while(a[0][x]!=0)
        {
           x++;
        }

minCut=x-1;
printf("Mincut is: %d",minCut);

}

int main(void)
{

int rows=0;
int columns=0;

    FILE *in = fopen("kargerMinCut.txt", "r");

    if (in != NULL)
     {
        char line[BUFSIZ];

        while (fgets(line, sizeof line, in) != NULL)
        {
            char *start = line;
            int field;
            int n;

            while (sscanf(start, "%d%n", &field, &n) == 1)
                {
                   start += n;
                   a[rows][columns]=field;
                   columns++;
                }
                   rows++;
                   columns=0;
        }
     }

     fclose(in);
     countRow=rows;

     randomize();
     showResult();
     printf("\n");

    return 0;
}
