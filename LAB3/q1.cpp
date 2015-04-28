#include<iostream>
#include<new>
#include<map>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;
int total;

int dijkstra(int **a, int src, int dst)
{
    int* d = new int[total];

    //initialisation
    for( int i =0; i<total ;i++)
    {
        if ( i == src )
        {
            d[i] = 0;
           // cout << " i : " << d[i] << endl;
        }

        else if ( a[src][i] != -1)
        {
            d[i] = a[src][i];
        }

        else
        {
            d[i] = 999999;
        }
    }

    vector<int> finalNodes;     //tree of final nodes
    vector<int>::iterator it;
    int temp = -1;
    while( finalNodes.size() < total)
    {
        //calculation
        int mini = 99999;
        bool check;
        for( int i=0; i<total; i++)
        {
            check = false;
            if ( d[i] > 0 )
            {
                for ( int i1=0; i1<finalNodes.size(); i1++)
                {
                    if ( i == finalNodes[i1]){check=true;break;}

                }

                if ( (check == false) && ( mini > d[i])){
                    mini = min(mini,d[i]);
                    temp = i;
                }

            }
        }

        finalNodes.insert(finalNodes.begin(),temp);   //final nodes for given source

        //last for loop
        bool check2 = false;
        for (int y =0 ; y < total; y++)
        {
            check2 = false;
            if ( a[temp][y] >  0 )
            {
                for ( int i1=0; i1<finalNodes.size(); i1++)
                {
                    if ( y == finalNodes[i1]){check2 = true; break;}
                }

                if ( check2 == false)    //not present in the tree
                {
                    d[y] = min( d[y], (d[temp] + a[temp][y]));
                }
            }
        }
    }

  /*  for( int i=0; i<total; i++)
    {
        cout << " I : " << i << " DISTANCE " << d[i] << " \n";
    }

    cout << "\nShortest distance b/w " << src << " --> " << dst << " = " << d[dst] << endl;*/

    return d[dst];
}

int** importData(int **a )
{
    ifstream file("network_topology.txt");
    int n,i = -1;
    file >> n;
    total = n;


    a = new int*[n];
    for( int i=0; i < n; i++)
    {
        a[i] = new int[n];
    }

    for( int p =0; p <n ;p++)
    {
        for( int u= 0; u< n ; u++)
        {
             a[p][u] = -1;
        }
    }

    while (true)
    {
        int node1, node2, distance;

        file >> node1;
        file >> node2;
        file >> distance;
      //  cout << "node 1 " << node1 << " node 2 " << node2 << " distance " << distance << endl;
        a[node1][node2] = distance;
        a[node2][node1] = distance;
        if( file.eof() ) break;
    }

    for( int i=0; i<total; i++)
    {
        for( int k=0; k<total; k++)
        {
            cout << " i : " << i << " k : " << k << " val : " << a[i][k] << endl;
        }
    }
    cout << endl;
    return a;
}

int nexthop( int src, int **a , int d)
{
    if ( a[src][d] != -1)   // destination router is neighbour
    {
        return -1;
    }

    int dist = 999999 , next = -1;

    for( int k=0; k<total; k++)
    {
        if ( a[src][k] != -1)
        {
            if ( dist > (a[src][k] + dijkstra(a,k,d)))
            {
                dist = min ( dist ,a[src][k] + dijkstra(a,k,d));
                next = k;
            }
        }
    }

    return next;
}

void routingTable(int ** a)
{
    int src;
    cout << "Enter the router for which routing table is needed" << endl;
    cin >> src;

    cout << "-------------------------------------------" << endl;
    cout << "Source\t\t| Destination\t| Next hop\n";
    cout << "-------------------------------------------" << endl;

    for( int i=0; i<total; i++)
    {
        if ( i == src)i++;

        cout << "Router " << src;
        cout << "\t|   Router " << i;

        if ( nexthop(src,a,i) == -1)
        {
            cout << "\t| Direct" << endl;
        }

        else
        {
            cout << "\t| Router " << nexthop(src,a,i) << endl;
        }
    }
     cout << "-------------------------------------------" << endl;
}



int main()
{
    int choice = 0,src, dst;
    int ** topography;
    bool exit = false;

    while ( choice != 4 ){
        cout << "Choose from the following : " << endl;
        cout << "1 - Import text file" << endl;
        cout << "2 - Calculate routing table " << endl;
        cout << "3 - Shortest path ( src + dstn ) " << endl;
        cout << "4 - End" << endl;
        cin >> choice;

        switch(choice){

        case 1 : topography = importData(topography);break;

        case 2 : routingTable(topography);break;

        case 3 : {
            cout << "Source : " ;
            cin >> src;

            cout << "Destination : " ;
            cin >> dst;

            cout << "\nShortest distance b/w " << src << " --> " << dst << " = " << dijkstra(topography,src,dst) << endl;
            break;
        }

        case 4 : exit= true; break;
        }

        if ( exit)break;
    }

    return 0;
}
