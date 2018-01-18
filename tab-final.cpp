//This is a C++ implementation of Quine-McCluskey Method
#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<cstring>
using namespace std;
//function to convert decimal to binary
string to_binary(int n,int m)
{string a;
 for(int i=0;i<m;i++)
  {if(n%2==0)
  	a.push_back('0');
   else 
  	a.push_back('1');
   n=n/2;
  }
  reverse(a.begin(),a.end());
  return a;
}
//function to compare 2 binary numbers if there is a difference of 1 bit or they are equal or neither of two
int compare(string a,string b)
{int n=a.length(); int c=0,d=0,k;
  for(int i=0;i<n;i++)
  	{if(a[i]!=b[i]){c++;k=i;}
     else if(a[i]==b[i]){d++;}
    }
  if(c==1) return k;
  else if(d==n) return -2;
  else return -1;
 } 
//function to change the bit to _ at the position of 1 bit difference
string change(string a,int l)
{ a[l]='_';
  return a;
}
//function to check if the binary string is already present in the prime vector
void check_like(string a,vector<string>&b)
{int flag=0,n=b.size();
 for(int i=0;i<n;i++)
  {if(compare(a,b[i])==-2)return;
   else flag++;
  }
 if(flag==n)
 {b.push_back(a);
 }
 return;
}
//string vector is used to store the terms.prime vector stores prime implicants.ep vector stores minimized function
int main() 
{int n,m,i,j,k,l,row,col,count;
 vector<string>terms;
 vector<string>vect;
 vector<string>prime;
 vector<string>temp1;
 vector<string>ep;
 vector<int>temp2;
 vector<pair<int,int> >temp3;
 cout<<"Enter the number of variables\n";
 cin>>m;
 cout<<"enter the number of terms\n";
 cin>>n;
 int*a=new int[n];
 cout<<"Enter the terms\n";
 for(int i=0;i<n;i++)
 	{cin>>a[i];}
for(int i=0;i<n;i++)
	{
	 vect.push_back(to_binary(a[i],m));
	}
 for(i=0;i<vect.size();i++)
	   	{
	   		terms.push_back(vect[i]);
	   	}
//Line 75 to 110 finds the prime implicants
while(!vect.empty())
	{
	 for( i=0;i<vect.size()-1;i++)
	  {int c=0;
	    for( j=i+1;j<vect.size();j++)
	     {l=compare(vect[i],vect[j]);
	       if(l!=-1 && l!=-2)
	        {temp1.push_back(change(vect[i],l));
	         temp2.push_back(j);
	    
	        }
	       else c++;
	     }
	     if(c==j-i-1)
	     	{ int d=0;for(int k=0;k<temp2.size();k++)
	     		{if(i==(temp2[k]))
	     			{d=1;break;}}
	     		 if(d==0) check_like(vect[i],prime);
	        }
	  }
	  int d=0;
	  for(int k=0;k<temp2.size();k++)
	  {
	  	if(i==(temp2[k]))
	  		{d=1;break;}
	  }
	  if(d==0)check_like(vect[i],prime);
	  vect.clear();
	  for(i=0;i<temp1.size();i++)
	   	{
	   		vect.push_back(temp1[i]);
	   	}
	   temp1.clear();
	   temp2.clear();
	}
vector<string>().swap(temp1);
vector<int>().swap(temp2);
vector<string>().swap(vect);
//print the prime implicants
cout<<"Prime Implicants are:"<<endl;
for(int i=0;i<prime.size();i++)
	{cout<<prime[i]<<endl;}


row=prime.size();
col=n;
/*declaring prime implicant table.
row+1 = no. of rows in table
col = no. of column in table
t stands for table*/

int**t = new int*[row+1];
for(i=0;i<row+1;i++)
{  t[i]=new int[col];
}

for(i=0;i<row+1;i++)
{for(j=0;j<col;j++)
  t[i][j]=0;
}
//lines 137 to 180 find the essential prime implicants
for(i=0;i<row;i++)
 { int c;
 int n1=terms.size();
 int m1=prime[i].length();
 for( j=0;j<n1;j++)
 { c=1;
   for( k=0;k<m1;k++)
   { if(prime[i][k]!='_'){if(prime[i][k]!=terms[j][k]){c=0;break;}}}
   if(c==1)t[i][j]=1;
 }
 }
for(j=0;j<col;j++)
 {count=0;
   for(i=0;i<row;i++)
    { if(t[i][j]==1) {count++;k=i;}}
   if(count==1){temp3.push_back(make_pair(j,k));}
 }

for(i=0;i<temp3.size();i++)
{ if(t[row][temp3[i].first]!=1)
   { ep.push_back(prime[temp3[i].second]);
     t[temp3[i].second][temp3[i].first]=-1;
     t[row][temp3[i].first]=1;
     for(j=0;j<col;j++)
      { if(t[temp3[i].second][j]==1)
          {for(k=0;k<row;k++)
            { if(t[k][j]==1)
               t[k][j]=-1;
            }
           t[row][j]=1;
          }
       }
     }
}
temp3.clear();

for(i=0;i<row;i++)
{ count=0;
  for(j=0;j<col;j++)
  { if(t[i][j]==1)
    count++;
  }
  if(count>0){temp3.push_back(make_pair(count,i));}
}
//lines 181 to 223 find the remaining minterms of minimized function which get stored in ep vector
sort(temp3.begin(),temp3.end());
if(!temp3.empty())
{i=temp3.size()-1;
{ ep.push_back(prime[temp3[i].second]);
  for(j=0;j<col;j++)
    { if(t[temp3[i].second][j]==1)
      { for(k=0;k<row;k++)
        { if(t[k][j]==1)
           {t[k][j]=-1;}
        }
      }
    }
}

while(1)
{k=1;
 for(i=0;(i<temp3.size()-k && i>=0);i++)
 {count=0;
  for(j=0;j<col;j++)
  { if(t[temp3[i].second][j]==1)
     count++;
  }
  if(count>0)
  {temp3[i].first=count;}else temp3[i].first=0;
  }
 sort(temp3.begin(),temp3.end()-k);
 i=temp3.size()-1-k;
 if(temp3[i].first>0)
 {ep.push_back(prime[temp3[i].second]);
  for(j=0;j<col;j++)
    { if(t[temp3[i].second][j]==1)
      { for(k=0;k<row;k++)
        { if(t[k][j]==1)
           {t[k][j]=-1;}
        }
      }
    }
}
else 
break;
k++;
}
//Printing minimized terms.
cout<<"Minimized terms are"<<endl;
for(i=0;i<ep.size();i++)
{ cout<<ep[i]<<endl;
}
}
else
{cout<<"Minimized terms are:"<<endl;
  for(i=0;i<prime.size();i++)
	   	{
	   		ep.push_back(prime[i]);
	   	}
  for(int i=0;i<ep.size();i++)
	{cout<<ep[i]<<endl;}
}

  
return 0;
}



