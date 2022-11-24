#include <vector>

unsigned int verticesnr;
int edges [vertices][vertices];
unsigned int vertices [verticesnr];


unsigned int min(unsigned int a, unsigned int b)
{
    if(a <= b)
    {
        return a; 
    }
    else
    {
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


unsigned int mergeVertice(int a, int b, int edges[][], unsigned int verticesnr)
{

    // a and b should range from 0 to matrix size -1
    //TODO: function that reduces the size of the matrix by 1 
        for(unsigned int i = 0; i < verticesnr; i++)
    {
        if(i < a)
        {
            if(i < b)
            {
                if(edges[i][a]==1)
                {
                    if(edges[i][b]!=1)
                    {
                        edges[i][a]=-1
                    }
                }
                if(edges[i][a]==0)
                {
                    if(edges[i][b]!=0)
                    {
                        edges[i][a]= -1;
                    }
                }
            }
            if(i > b)
            {
                if(edges[i][a]==1)
                {
                    if(edges[b][i]!=1)
                    {
                        edges[i][a]=-1
                    }
                }
                if(edges[i][a]==0)
                {
                    if(edges[b][i]!=0)
                    {
                        edges[i][a]= -1;
                    }
                }
            }  
        }
        if(i > a)
        {
            if(i > b)
            {
                if(edges[a][i]==1)
                {
                    if(edges[b][i]!=1)
                    {
                        edges[a][i]=-1
                    }
                }
                if(edges[a][i]==0)
                {
                    if(edges[b][i]!=0)
                    {
                        edges[a][i]= -1;
                    }
                }
                /*
                if(edges[a][i]==-1)
                {
                // nothing changes
                }
                */
            }
            if(i < b)
            {
                if(edges[a][i]==1)
                {
                    if(edges[i][b]!=1)
                    {
                        edges[a][i]=-1
                    }
                }
                if(edges[a][i]==0)
                {
                    if(edges[i][b]!=0)
                    {
                        edges[a][i]= -1;
                    }
                }
            }
        }
    }

    int newedges[matrixsize-1][matrixsize-1]=0;

    for(int c = 0; c < matrixsize; c++ )
    {
        for(int d = c; d < matrixsize; d++ )
        {
            if(c == b || d== b )
            {

            }
            elseif(c > b )
            {
                if(d > b)
                {
                    edges[c][d]=newedges[c-1][d-1];
                }
                else
                {
                    edges[c][d]=newedges[c-1][d];
                }
            }
            else
            {
                if(d > b)
                {
                    edges[c][d]=newedges[c][d-1];
                }
                else
                {
                    edges[c][d]=newedges[c][d];
                }
            }
        }
    }
    return newedges;
}


unsigned int rededges(int edges [][], int verticesnr)
{
    unsigned int red = 0;
    unsigned int redmax = 0;
    for(int i = 0; i <= verticesnr; i++)
    {
        for(int j = 0; j <= verticesnr; j++)
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

unsigned int mergeVertices(int edges[][], unsigned int iteration, int vertice, unsigned int verticesnr, unsigned int maxiter  )//TODO: check how to optimize the the number of vriables passed 
// iteration must be initialized with 1
{
    unsigned int maxred = inf;
    unsigned int j = (verticesnr-1)*(verticesnr)/2
    unsigned int mincolorvec [j];
    //unsigned int matrixsize; should be initialized
    int i=0;
   

    //abbruchbedingung der Rekursion
    if(itteration == maxiter) 
    {
        return 0;
    }


   for(int a=iteration; a <= n-1; a++) // here is a mistake
   {
        for(int b=a+1; a <= n ; b++)
            {
                // reduce matrix and calculate the max twin width by recursion
                int temp [verticesnr][verticesnr] = mergeVertice(a,b,edges);
                mincolorvec[i] =max(rededges(temp), mergeVertices(iteration+1, temp, verticesnr-1)); //TODO: welche matrix muss übergeben werden 
                i++;
            }
   }
   for(int k = 0; k < j ; k++)
   {
        maxred = min(mincolorvec[k],maxred);
   }

    return maxred; 
}