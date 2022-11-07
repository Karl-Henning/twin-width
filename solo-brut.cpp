#include <vector>

unsigned int verticesnr;
int edges [vertices][vertices];
unsigned int vertices [verticesnr];


unsigned int min(unsigned int a, unsigned int b)
{
    if(a<=b){
        return a; 
    }
    else{
        return b;
    }
}

unsigned int max(unsigned int a, unsigned int b)
{
    if(a>=b){
        return a; 
    }
    else{
        return b;
    }
}


unsigned int mergeVertice(int a, int b, int edges[x][x])
{

    //TODO: programm to merge a vertice 
    return edges;
}

unsigned int rededges(int edges [a][a])
{
    int red = 0;
    for(int i = 0; i <= a; i++)
    {
        for(int j = 0; j <=a; j++)
        {
            if(edges [i][j] == -1)//TODO: decide for a number that represents a red edge maybe go for a >= or <= so that a edge can be more red 
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
    if(itteration == 7) //TODO: verticesnr set maximum of itterations
    {
        return 0;
    }
   unsigned mincolorvec [(verticesnr-1)*(verticesnr)/2];
   i=0;
   
   for(a=iteration; a <= n-1; a++)
   {
        for(b=a+1; a <= n ; b++)
            {
                i++;
                int temp [verticesnr][verticesnr] = mergeVertice(a,b,edges);
                mincolorvec[i]=rededges(temp) + mergeVertices(iteration+1, temp, verticesnr-1); // TODO: the understanding how twin width is calculated needs to checked (red edges from 1 vertice no +)
            }
   }
    

    return 0; // TODO: return min(mincolorvec) (might be easy with right twin width calculation)
}
