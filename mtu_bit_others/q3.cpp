#include<iostream>
using namespace std;

void fragmentation(int frag_size,int mtu_size,int no_of_frag)
{ 
    	int fragment[no_of_frag],offset[no_of_frag];	
	 
  	for(int i=0;i<no_of_frag;i++)
  	{
  		if(mtu_size>frag_size)
    		fragment[i]=frag_size+20;
		else
		fragment[i]=mtu_size+20;
		if(i==0)    
		offset[i]=0;
		else
    		offset[i]= offset[i-1]+(fragment[i-1]-20)/8;
		frag_size = frag_size + 20 - fragment[i];
		
  	}
	for(int i=0;i<no_of_frag;i++)
	{
		cout<<"Fragment "<<(i+1)<<" : "<<fragment[i]<<" with offset : "<<offset[i]<<endl;
  	}

}

int reassembly(int fragLength[],int fragOffset[],int frag_count)
{

    for(int i=1;i<frag_count;i++)
    {
      for(int j=i;j>0;j--)
      {
        if(fragOffset[j]>fragOffset[j-1])
        break;
        int temp=fragOffset[j];
        fragOffset[j]=fragOffset[j-1];
        fragOffset[j-1]=temp;
        temp=fragLength[j];
        fragLength[j]=fragLength[j-1];
        fragLength[j-1]=temp;
      }
    }
 
  int length =0;
  for(int i=0;i<frag_count;i++)
  {
     length+=fragLength[i]-20;
  }
   length+=20;

  return length;
}



int main()
{
  int frag_size,mtu_size;
  cout<<"Enter the fragmentation size of packet(This includes the 20 byte size of header)\n";
  cin>>frag_size;
  cout<<"Enter the Maximum Transmission Units(This includes the 20 byte size of header)\n";
  cin>>mtu_size;
  frag_size-=20;
  mtu_size-=20;
  int no_of_frag=frag_size/mtu_size;
  if(frag_size%mtu_size!=0)
  no_of_frag++;

  fragmentation(frag_size,mtu_size,no_of_frag);
  
  int frag_count;	
  cout<<"Enter the number of fragments received\n";
  cin>>frag_count;
  int fragLength[frag_count];
  int fragOffset[frag_count];
  for(int i=0;i<frag_count;i++)
  {
    cout<<"Enter the fragment size of fragment ";
    cin>>fragLength[i];
    cout<<"Enter the offset of fragment ";
    cin>>fragOffset[i];
  }

   cout<<"Reassembled length of the fragments is "<<reassembly(fragLength,fragOffset,frag_count)<<endl;
  for(int k=0;k<frag_count;k++)
  {
	cout<<"Length of the fragment "<<(k+1)<<" : "<<fragLength[k]<<" and offset : "<<fragOffset[k]<<endl;
  }

 return 0;
}

 

