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
    //TODO: function that reduces the size of the matrix by 1 

    return edges;
}

//TODO: need a function that reduces the size of the matrix by 1 


unsigned int rededges(int edges [a][a])
{
    unsigned int red = 0;
    unsigned int redmax = 0;
    for(int i = 0; i <= a; i++)
    {
        for(int j = 0; j <=a; j++)
        {
            if(edges [i][j] == -1)
            {
                red++;        
            }
            if(edges [j][i]== -1)
            {
                red++;
            }
         
        }
        redmax = max(redmax,red);
        red=0;
    }
    return redmax;
}

unsigned int mergeVertices(unsigned int iteration, int vertice unsigned int verticesnr, unsigned int maxiter  )//TODO: check how to optimize the the number of vriables passed 
// iteration must be initialized with 1
{
    unsigned int maxred = inf;
    unsigned int j = (verticesnr-1)*(verticesnr)/2
    unsigned int mincolorvec [j];
    int i=0;
   

    //abbruchbedingung der Rekursion
    if(itteration == maxiter) 
    {
        return 0;
    }


   for(int a=iteration; a <= n-1; a++)
   {
        for(int b=a+1; a <= n ; b++)
            {
                // reduce matrix and calculate the max twin width by recursion
                int temp [verticesnr][verticesnr] = mergeVertice(a,b,edges);
                mincolorvec[i] =max(rededges(temp), mergeVertices(iteration+1, temp, verticesnr-1); //TODO: welche matrix muss übergeben werden 
                i++;
            }
   }
   for(int k = 0; k << j ; k++)
   {
        maxred = min(mincolorvec[k],maxred);
   }

    return maxred; 
}
