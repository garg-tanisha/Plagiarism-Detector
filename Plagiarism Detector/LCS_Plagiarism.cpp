#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_set>
#include<dirent.h>
#include<bits/stdc++.h>
using namespace std;

int WordCountCopy=0;
int WordCount=0;
//string StringArray1[10000][30],StringArray2[10000][30];
vector <string> StringArray1,StringArray2;
int LenStringArray1=0;
int LenStringArray2=0;
int const Maxi=10001;
int Array1[Maxi][Maxi];

int Check1(string,string,int,int);
void Partition(string,string,int ,int);

int LCS(vector <string> A,vector <string> B,int M,int N) 
{  
	int L[M+1][N+1]; 
   int i, j; 
   
   for (i=0; i<=M; i++) 
   { 
     for (j=0; j<=N; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
   
       else if (A[i-1] == B[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
   
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 
   }
   return L[M][N]; 

}

void Plagiarism()
{
	unordered_set <string> myset;
	myset.insert("is"); myset.insert("am"); myset.insert("are"); myset.insert("was"); myset.insert("were");myset.insert("has"); 
	myset.insert("have");myset.insert("had");myset.insert("a");myset.insert("an"); myset.insert("the"); myset.insert("and"); myset.insert("And");
	myset.insert("Is"); myset.insert("Am"); myset.insert("Are"); myset.insert("Was"); myset.insert("Were");myset.insert("Has"); 
	myset.insert("Have");myset.insert("Had");myset.insert("A");myset.insert("An"); myset.insert("The");myset.insert("in");
	myset.insert("So");myset.insert("I"); myset.insert("you");myset.insert("we"); myset.insert("it"); myset.insert("he");
	myset.insert("she"); myset.insert("It"); myset.insert("on"); myset.insert("of"); myset.insert("to");
    string str1,str2;
	ifstream fin1;
   fin1.open("CopyFile.txt");
   vector<string> ip_to_print;
   string op_to_print;
	int i=0;
	if(fin1)
	{
	    while(!fin1.eof())
	    {
	    	fflush(stdin);
			getline(fin1,str1);
			StringArray1.clear();
			LenStringArray1=0;
			istringstream iss(str1);
			op_to_print=str1;
			string S1;
			while(iss >> S1)
			{
				if(myset.find(S1)==myset.end())
				{ 
					transform(S1.begin(),S1.end(),S1.begin(),::tolower); 
					StringArray1.push_back(S1);
					LenStringArray1++;
				}
			}
			ifstream fin2;
			fin2.open("SourceFile.txt");
			i++;
			int j=0, Count=0;
	        while(!fin2.eof())
	        {
	    		fflush(stdin);
	            getline(fin2,str2);
				StringArray2.clear();
				LenStringArray2=0;
				istringstream iss(str2);
				string S2;
				 Count=0;
				while(iss >> S2)
				{
					ip_to_print.push_back(str2);
					if(myset.find(S2)==myset.end())
					{
						transform(S2.begin(),S2.end(),S2.begin(),::tolower); 
						StringArray2.push_back(S2);
						LenStringArray2++;
						Count++;
						if(i==1)
							WordCount++;
					}
				}
				ip_to_print.push_back(str2);
				j++;
	    		Array1[i-1][j-1]=Check1(str1,str2,i,j);
	        }
	        int z=0;
			fin2.close();
			int max1=Array1[0][z];
			for(z=1;z<=j;z++)
			{
				max1=max(max1,Array1[i][z]);
			}
			double x=((max1*1.0)/(Count*1.0));
			if (x>=0.75)
			{
				WordCountCopy=WordCountCopy +max1;
			//	cout<<"\n";
			//	cout<<"line of your document:\n "<<ip_to_print[idx]<<endl;
			//	cout<<"\n\tCOPIED\n\n";
			//	cout<<"line from document: "<<"\n"<<op_to_print<<"\n\n\n";
			}
	    }
		fin1.close();
		}
	//cout<<LenStringArray1<<endl;
	//cout<<LenStringArray2<<endl;
}

int Check1(string A,string B,int a,int b)
{
    return LCS(StringArray1,StringArray2,LenStringArray1,LenStringArray2);
}

double Calc()
{
    double a= WordCountCopy*1.0;
    double b= WordCount*1.0;
	if (WordCount<WordCountCopy)
		return 100.0;
    double Percentage=(a/b)*100.0;
    return Percentage;
}

int main()
{
    Plagiarism();
    try
    {	if(WordCount==0)
        {
            throw WordCount;
        }
		cout<<"Percentage of Plagiarism is:\t"<<Calc()<<endl;
    }
    catch(int Q)
    {
        cout<<"No string to check"<<endl;
    }
	cout<<WordCount<<endl;
	cout<<WordCountCopy<<endl;
    return 0;
}
