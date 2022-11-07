#include <vector>

unsigned int verticesnr;
int edges [vertices][vertices];
unsigned int vertices [verticesnr];

/*
unsigned int min(unsigned int a, unsigned int b)
{
    if(a<b){
        return a; 
    }
    else{
        return b;
    }
}
*/

unsigned int mergeVertice(int a, int b, int edges[x][x])
{
    
    return 0;
}

unsigned int rededges(int edges [a][a])
{
    red=0;
    for(i=0; i <=a; i++)
    {
        for(j=0; j <=a; j++)
        {
            if(edges [i][j] == -1)
            {
                red++;        
            } 
        }
    }
    return red;
}

unsigned int mergeVertices(unsigned int iteration, int vertice unsigned int verticesnr  )
// iteration must be initialized with 1
{
   unsigned mincolorvec [(verticesnr-1)*(verticesnr)/2];
   i=0;
   
   for(a=iteration; a <= n-1; a++)
   {
        for(b=a+1; a <= n ; b++)
            {
                i++;
                int temp [verticesnr][verticesnr] = mergeVertice(a,b,edges);
                mincolorvec[i]=rededges(temp) + mergeVertices(iteration+1, temp, verticesnr-1);
            }
   }
    

    return 0; // return min(mincolorvec) 
}

