#include <stdio.h>
#include<stdlib.h>
#include <algorithm>
#include <stdint.h>
#include <iostream> 
#include <inttypes.h>
#include<string.h>
#include<vector>

using namespace std;

struct Act
{
	long long s;//sweetness
	int t;//how to get to this point
	int x;
	int y;
	int z;
	int fromx;
	int fromy;
	int fromz;

};


long long MaxPathSum(vector<vector<long long> > &grid, int n, int m, int k, long long c, vector<Act>&Path)
{       
    vector<vector<vector <Act> > >maxsum(n, vector<vector<Act> >(m, vector<Act>(k+1)));

    maxsum[0][0][0].s = grid[0][0];
    for(int i = 1; i < n; i++)
    {
        maxsum[i][0][0].s = maxsum[i - 1][0][0].s + grid[i][0];
        maxsum[i][0][0].t = 0;
        maxsum[i][0][0].x = i;
        maxsum[i][0][0].y = 0;
        maxsum[i][0][0].z = 0;
        maxsum[i][0][0].fromx = i - 1;
        maxsum[i][0][0].fromy = 0;
        maxsum[i][0][0].fromz = 0;
    }
    for(int i = 1; i < m; i++)
    {
        maxsum[0][i][0].s = maxsum[0][i - 1][0].s + grid[0][i];
        maxsum[0][i][0].t = 0;
        maxsum[0][i][0].x = 0;
        maxsum[0][i][0].y = i;
        maxsum[0][i][0].z = 0;
        maxsum[0][i][0].fromx = 0;
        maxsum[0][i][0].fromy = i - 1;
        maxsum[0][i][0].fromz = 0;
    }


    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            if(maxsum[i - 1][j][0].s < maxsum[i][j - 1][0].s)
            {
            	maxsum[i][j][0].s = maxsum[i][j - 1][0].s + grid[i][j];
            	maxsum[i][j][0].t = 0;
		        maxsum[i][j][0].x = i;
		        maxsum[i][j][0].y = j;
		        maxsum[i][j][0].z = 0;
		        maxsum[i][j][0].fromx = i;
        		maxsum[i][j][0].fromy = j - 1;
        		maxsum[i][j][0].fromz = 0;
            }
            else
            {
                maxsum[i][j][0].s = maxsum[i - 1][j][0].s + grid[i][j];
                maxsum[i][j][0].t = 0;
		        maxsum[i][j][0].x = i;
		        maxsum[i][j][0].y = j;
		        maxsum[i][j][0].z = 0;
		        maxsum[i][j][0].fromx = i - 1;
        		maxsum[i][j][0].fromy = j;
        		maxsum[i][j][0].fromz = 0;
		    }
        }
    }

    vector<Act>Maxsumoflayer(k+1);
    Maxsumoflayer[0] = maxsum[0][0][0];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
        	if(maxsum[i][j][0].s > Maxsumoflayer[0].s)
        	{
        		Maxsumoflayer[0] = maxsum[i][j][0];
        	}
        }
    }

    if( k == 0)
    {	
	    int i = n - 1;
	    int j = m - 1;

	    while(i > 0 || j > 0)
	    {
	    	Act LastAct = maxsum[i][j][0];
	    	Path.push_back(LastAct);
	        i = LastAct.fromx;
	        j = LastAct.fromy;
	    }
	    return maxsum[n-1][m-1][0].s;
    }


    int jumptimes = 0;
//join jump
    for(int l = 1; l < k+1; l++)//create sweetness with every jump times
    {
    	maxsum[0][0][l].s = Maxsumoflayer[l-1].s + grid[0][0]-l*c;
    	maxsum[0][0][l].t = 1;
    	maxsum[0][0][l].x = 0;
    	maxsum[0][0][l].y = 0;
    	maxsum[0][0][l].z = l;
    	maxsum[0][0][l].fromx = Maxsumoflayer[l-1].x;
    	maxsum[0][0][l].fromy = Maxsumoflayer[l-1].y;
    	maxsum[0][0][l].fromz = Maxsumoflayer[l-1].z;
    	for(int i = 1; i < n; i++)
	    {
	    	if(maxsum[i - 1][0][l].s >= Maxsumoflayer[l-1].s)
	    	{
	    		maxsum[i][0][l].s = maxsum[i - 1][0][l].s + grid[i][0] - l*c;
	    		maxsum[i][0][l].t = 0;
		        maxsum[i][0][l].x = i;
		        maxsum[i][0][l].y = 0;
		        maxsum[i][0][l].z = l;
		        maxsum[i][0][l].fromx = i - 1;
        		maxsum[i][0][l].fromy = 0;
        		maxsum[i][0][l].fromz = l;
	    	}
	    	else
	    	{
	    		maxsum[i][0][l].s = Maxsumoflayer[l-1].s + grid[i][0] - l*c;
	    		maxsum[i][0][l].t = 1;
		        maxsum[i][0][l].x = i;
		        maxsum[i][0][l].y = 0;
		        maxsum[i][0][l].z = l;
		        maxsum[i][0][l].fromx = Maxsumoflayer[l-1].x;
        		maxsum[i][0][l].fromy = Maxsumoflayer[l-1].y;
        		maxsum[i][0][l].fromz = Maxsumoflayer[l-1].z;
	    	}
	    }
	    for(int i = 1; i < m; i++)
	    {
	    	if(maxsum[0][i - 1][l].s >= Maxsumoflayer[l-1].s)
	    	{
	    		maxsum[0][i][l].s = maxsum[0][i - 1][l].s + grid[0][i] - l*c;
	    		maxsum[0][i][l].t = 0;
		        maxsum[0][i][l].x = 0;
		        maxsum[0][i][l].y = i;
		        maxsum[0][i][l].z = l;
		        maxsum[0][i][l].fromx = 0;
        		maxsum[0][i][l].fromy = i - 1;
        		maxsum[0][i][l].fromz = l;
	    	}
	    	else
	    	{
	    		maxsum[0][i][l].s = Maxsumoflayer[l-1].s + grid[0][i] - l*c;
	    		maxsum[0][i][l].t = 1;
		        maxsum[0][i][l].x = 0;
		        maxsum[0][i][l].y = i;
		        maxsum[0][i][l].z = l;
		        maxsum[0][i][l].fromx = Maxsumoflayer[l-1].x;
        		maxsum[0][i][l].fromy = Maxsumoflayer[l-1].y;
        		maxsum[0][i][l].fromz = Maxsumoflayer[l-1].z;
	    	}
	    }
    	for(int i = 1; i < n; i++)
	    {
	        for(int j = 1; j < m; j++)
	        {

	            if(maxsum[i - 1][j][l].s < maxsum[i][j - 1][l].s && Maxsumoflayer[l-1].s < maxsum[i][j - 1][l].s)
	            {
	            	maxsum[i][j][l].s = maxsum[i][j - 1][l].s + grid[i][j] - l*c;
	            	maxsum[i][j][l].t = 0;
			        maxsum[i][j][l].x = i;
			        maxsum[i][j][l].y = j;
			        maxsum[i][j][l].z = l;
			        maxsum[i][j][l].fromx = i;
	        		maxsum[i][j][l].fromy = j - 1;
	        		maxsum[i][j][l].fromz = l;
	            }
	            else if(maxsum[i - 1][j][l].s > maxsum[i][j - 1][l].s && maxsum[i - 1][j][l].s > Maxsumoflayer[l-1].s)
	            {
	                maxsum[i][j][l].s = maxsum[i - 1][j][l].s + grid[i][j] - l*c;
	                maxsum[i][j][l].t = 0;
			        maxsum[i][j][l].x = i;
			        maxsum[i][j][l].y = j;
			        maxsum[i][j][l].z = l;
			        maxsum[i][j][l].fromx = i - 1;
	        		maxsum[i][j][l].fromy = j;
	        		maxsum[i][j][l].fromz = l;

	            }
	            else if (Maxsumoflayer[l-1].s >= maxsum[i][j - 1][l].s && Maxsumoflayer[l-1].s >= maxsum[i - 1][j][l].s)
	            {
	            	maxsum[i][j][l].s = Maxsumoflayer[l-1].s + grid[i][j] - l*c;
	            	maxsum[i][j][l].t = 1;
			        maxsum[i][j][l].x = i;
			        maxsum[i][j][l].y = j;
			        maxsum[i][j][l].z = l;
			        maxsum[i][j][l].fromx = Maxsumoflayer[l-1].x;
	        		maxsum[i][j][l].fromy = Maxsumoflayer[l-1].y;
	        		maxsum[i][j][l].fromz = Maxsumoflayer[l-1].z;
	            }
	        }
	    }

	    Maxsumoflayer[l] = maxsum[0][0][l];
	    for(int i = 0; i < n; i++)
	    {
	        for(int j = 0; j < m; j++)
	        {
	        	if(maxsum[i][j][l].s > Maxsumoflayer[l].s)
	        	{
	        		Maxsumoflayer[l] = maxsum[i][j][l];
	        	}
	        }
	    }
	    if(maxsum[n-1][m-1][l].s <= maxsum[n-1][m-1][l-1].s)
	    {
	    	jumptimes = l - 1;
	    	break;
	    }
	    else
	    {
	    	jumptimes = l;
	    }

    }
    long long Max = maxsum[n - 1][m - 1][jumptimes].s;
    // int jumptimes = 0;
    // for(int l = 0; l < k+1; ++l)
    // {
    // 	if(maxsum[n - 1][m - 1][l].s > Max)
    // 	{
    // 		Max = maxsum[n - 1][m - 1][l].s;
    // 		jumptimes = l;
    // 	}
    // }

    int i = n - 1;
    int j = m - 1;
    int h = jumptimes;

    while(i > 0 || j > 0 || h > 0)
    {
    	Act LastAct = maxsum[i][j][h];
    	Path.push_back(LastAct);
        i = LastAct.fromx;
        j = LastAct.fromy;
        h = LastAct.fromz;
    }
    return Max;
}



int main()
{
    int n, m, k;
    long long c;
	scanf("%d %d %d %lld", &n, &m, &k, &c);

	vector<Act> Path;
    vector<vector <long long> >grid(n);


	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
        	long long temp;
        	cin >> temp;
        	grid[i].push_back(temp);
        }
    }
    
    long long d = MaxPathSum(grid, n, m, k, c, Path);
    printf("%lld\n", d);
    printf("%lu\n", Path.size());
	for(int i = Path.size()-1; i > -1; i--)
	{
		if(Path[i].t == 0)
		{
			printf("%s %d %d\n", "Move", Path[i].x, Path[i].y);
		}
		if(Path[i].t == 1)
		{
			printf("%s %d %d\n", "Jump", Path[i].x, Path[i].y);
		}
	}

    return 0;
}


