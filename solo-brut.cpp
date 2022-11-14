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


unsigned int mergeVertice(int a, int b, int edges[x][x], unsigned int verticenr )
{
    //TODO: function that reduces the size of the matrix by 1 
    edges[a][b] = 0 ;
    edges[b][a] = 0 ;
    for(unsigned int i = 0; i<=verticenr; i++ )
    {
        if( i==a || b==i)
        {

        }
        else if(b << i)
        {
            if(b << i)
            {
                if((b == a == 1 )
                {
                    edges[b][i] = 0 ;
                    edges[a][i] = 0 ;
                    // information of the connection that a and b have with i is lost at the moment and the possition that is deleted isnt right at the moment 
                }
            }
            else
            {
                if((b == a == 1 )
                {
                    edges[i][b] = 0 ;
                    edges[i][a] = 0 ;
                }
            }
        }
        else
        {
            if(b << i)
            {

            }
            else
            {

            }
        }

    }
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

unsigned int mergeVertices(unsigned int iteration, int vertice , unsigned int verticesnr, unsigned int maxiter  )//TODO: check how to optimize the the number of vriables passed 
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
                int temp [verticesnr-1][verticesnr-1] = mergeVertice(a,b,edges,(verticenr-1));
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
