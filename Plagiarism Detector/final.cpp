#include<iostream>
#include<dirent.h>
#include<fstream>
#include<unordered_set>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
void plagiarism();
int tot_count=0;
int LCS(string a,string b);
bool call_rout(string,string &,string,string,string);
bool call_rout(string,string,unordered_set<string>,vector<string>,string,string,string);
void prepare_lps(string pattern,int lps[],int n);
int KMPSearch(string pat, string txt) ;
int main()
{
	cout<<"\t\t\t\t-----------------------------------------------\n\t\t\t\t\t\tPLAGIARISM CHECKER";
	cout<<"\n\t\t\t\t-----------------------------------------------\n\n";
//	cout<<"Enter file name:\t";
	plagiarism();
	return 0;
}

void plagiarism()
{
	unordered_set <string> myset;
	myset.insert("is"); myset.insert("am"); myset.insert("are"); myset.insert("was"); myset.insert("were");myset.insert("has"); 
	myset.insert("have");myset.insert("had");myset.insert("a");myset.insert("an"); myset.insert("the"); myset.insert("and"); myset.insert("And");
	myset.insert("Is"); myset.insert("Am"); myset.insert("Are"); myset.insert("Was"); myset.insert("Were");myset.insert("Has"); 
	myset.insert("Have");myset.insert("Had");myset.insert("A");myset.insert("An"); myset.insert("The");myset.insert("in");
	myset.insert("So");myset.insert("I"); myset.insert("you");myset.insert("we"); myset.insert("it"); myset.insert("he");
	myset.insert("she"); myset.insert("It"); myset.insert("on"); myset.insert("of"); myset.insert("to");
	  
	ifstream input_file,source_file; //Stream class to read from files
	input_file.open("abc.txt");
//	input_file.open("C:\\Users\\DELL\\Desktop\\Plagiarism\\1.txt");
	int count_iplines=0;
	string word="";
	string str="";
	DIR *dir;
	dirent *ent; // pointer to directory entry
	vector<string> all_files;
	if ((dir = opendir ("C:\\Users\\DELL\\Desktop\\Plagiarism\\")) != NULL)  //// opendir returns NULL if couldn't open directory 
	{
	 	while ((ent = readdir (dir)) != NULL) 
		{
	 	   all_files.push_back(ent->d_name); //It also defines the structure dirent which includes the following members:
						// ino_t  d_ino       file serial number
						// char   d_name[]    name of entry
		}
	  	closedir (dir);
	} 
	else {
	  perror (""); //Print error message
		// Interprets the value of errno as an error message, and prints it to stderr (the standard error output stream, usually the console), optionally preceding it with the custom message specified in str.
	  return ;
	}
	int l_ip=0,l_sr=0;
	string ip_to_print,op_to_print,print;
	int n_comma_ip=0,n_comma_sr=0; bool com=false,f=false,uniq=true;
	unordered_set<string> comma_words;
	vector<string> list_ip;
	while(input_file)
	{	str=""; uniq=true;
		string sk="", temp=""; com=false;f=false; n_comma_ip=0; ip_to_print="";
		while(input_file>>word)
		{	
			if(ip_to_print=="")
				ip_to_print=word;
			else
			{
				ip_to_print+=" ";
				ip_to_print+=word;
			}
			l_ip=word.length();
			if(l_ip==0)
				break;
			if(l_ip==2||l_ip==3)
             {
                    if(word[0]>='1'&&word[0]<='9')
                    {
                        if(l_ip==2)
                        {
							if(word[1]=='.')
                            {   word="";
								if(input_file)
                            	{
									input_file>>word;
									ip_to_print+=" ";
									ip_to_print+=word;
								}
							}
						}
                            else
                            {
                                if(word[1]>='0'&&word[1]<='9')
                                {
                                    if(word[2]=='.')
                                     {
                                     	word="";
										if(input_file)
		                            	{
											input_file>>word;
											ip_to_print+=" ";
											ip_to_print+=word;
										}
									 }
                                }
                            }
                    }
             }
			if(word[l_ip-1]==',')
			{
				com=true;
				n_comma_ip++;
				word=word.substr(0,l_ip-1);
				str+=word; sk="";
				while(input_file)
				{
				 char ch;
					input_file.get(ch);
					ip_to_print+=ch;
					if(ch==',')
					{  
						n_comma_ip++; 
						sk+=temp;
						list_ip.push_back(sk); 
						sk=""; temp="";
					}
					else if(ch=='.')
					{
						char t;
						input_file.get(t);
						if(t==' '||t=='\n' || t == '\r')
						{
						sk+=temp; 	list_ip.push_back(sk); sk="";temp=""; 
							break;	
						}
						else
						{
							temp+=t;
							ip_to_print+=t;
						}
							
					}
					else
					{	
						if(ch!=' ')
							temp+=ch;
						else
						{
							if(!(myset.find(temp)==myset.end()))
								temp="";
							else
							{
								sk+=temp; 
								temp="";
							}
												
						}
					}
				}
				if(str.length()<=15)
				{
					str+=list_ip[0];
					list_ip.erase(list_ip.begin());
				}
				for(int k=0;k<list_ip.size();k++)
					comma_words.insert(list_ip[k]);
			}
			if(com)
				break;
			if(word[l_ip-1]=='.')
			{
				word=word.substr(0,l_ip-1);
				str+=word;
				break;
			}
			else
			{
				if(myset.find(word)==myset.end())
					str+=word;
			}
			word="";
		}
		count_iplines++;
		print=ip_to_print;

	//	cout<<"ip original: "<<ip_to_print<<endl;
	//	cout<<"input formeed: "<<str<<endl<<"line number: "<<count_iplines<<endl;
		string source="";
		if(str=="")
		{
			count_iplines--; uniq=false;
		}
		int size=all_files.size();
		for(int i=0;i<size;i++)
		{
			sk="";
			string s="C:\\Users\\DELL\\Desktop\\Plagiarism\\";
			s+=all_files[i];
			source_file.open(s);
			word=""; sk="";	list_ip.erase(list_ip.begin(),list_ip.end());
		if(!(str==""))
		{
			while(source_file)
			{
				vector<string>list;
				com=false; n_comma_sr=0;
				while(source_file>>word)
				{
					if(op_to_print=="")
						op_to_print=word;
					else
					{
						op_to_print+=" ";
						if(word.length()!=2||word.length()!=3)
							op_to_print+=word;
					}
					 l_sr=word.length();
				if(l_sr==0)
					break;
				 if(l_sr==2||l_sr==3)
                {
                    if(word[0]>='0'&&word[0]<='9')
                    {
                        if(l_sr==2)
                        {
							if(word[1]=='.')
                            {
                            	 word="";
								if(source_file)
                            	{
									source_file>>word;
									op_to_print+=" ";
									op_to_print+=word;
								}
							}
							else
								op_to_print+=word;
						
						}
                            else
                            {
                                if(word[1]>='0'&&word[1]<='9')
                                {
                                    if(word[2]=='.')
                                     {
                                    	word="";
										if(source_file)
                            			{
											source_file>>word;
											op_to_print+=" ";
											op_to_print+=word;
										}
									 }
                                }
                                else
									op_to_print+=word;
                            }
                    }
                }
				if(word[l_sr-1]==',')
					{	com=true; temp=""; sk="";
						n_comma_sr++;
						word=word.substr(0,l_sr-1);
						source+=word;
						while(source_file)
						{
						 	char ch;
							source_file.get(ch);
							op_to_print+=ch;
							if(ch==',')
							{
								n_comma_sr++; sk+=temp;
								list.push_back(sk); sk=""; temp="";
							}
							else if(ch=='.')
							{
								char t;
								source_file.get(t);
								if(t==' '||t=='\n'||t=='\r')
								{
									sk+=temp;	
									list.push_back(sk);sk="";temp=""; break;
								}
								else
								{
								
									temp+=t;
									op_to_print+=t;
								}
									
							}
							else
							{
								if(ch!=' ')
								{  
									temp+=ch;
									
								}
								else
								{
									if(!(myset.find(temp)==myset.end()))
									{
										temp="";
									}
									else
									{
										if(!(temp==""))
											sk+=temp;
										 temp="";
									}
								}
							}
						}
				
						if(n_comma_sr)
						{
							if(source.length()<=15)
							{
								source+=list[0]; list.erase(list.begin());
							}
							f=call_rout(str,source,comma_words,list,ip_to_print,op_to_print,all_files[i]);
							source="";	op_to_print="";
							if(f)
								break;
						}
					}
					if(com)
						break;
					if(word[l_sr-1]=='.')
					{
						word=word.substr(0,l_sr-1);
						source+=word;
						f=call_rout(str,source,ip_to_print,op_to_print,all_files[i]);
						source=""; 	
						op_to_print="";
						if(f)
							break;
					}
					else
					{
						if(myset.find(word)==myset.end())
							source+=word;
					}
					word="";
					
				}
				if(f)
				{	
					break;
				}
			}
		}
			source_file.close();
			if(f)
				break;
			
		}
		if(f==false&&uniq==true)
		{
			cout<<"line of your document:\n "<<print<<endl;
			cout<<"\t\t\nUnique\n\n\n";
		}
	comma_words.erase(comma_words.begin(),comma_words.end());
	}
	cout<<"Total lines of your document= "<<count_iplines<<endl<<"Lines copied: "<<tot_count<<endl;
	double plag=(double)tot_count/count_iplines;
	plag*=100;
	cout<<"PLAGIARISED: "<<plag<<"%\t\t\tUNIQUE: "<<(100-plag)<<"%\n";	
}
bool call_rout(string str,string source,unordered_set<string> comma_words,vector<string> list,string ip_to_print,string op_to_print,string all_files)
{
	int l=0;
	l=KMPSearch(str,source);
	int count=0;
	for(int i=0;i<list.size();i++)
	{
		if(comma_words.count(list[i]))
		{
			string temp=list[i]; count+=temp.length();
		}
	}
	double b=str.length();
	unordered_set<string>:: iterator itr;
	for(itr=comma_words.begin();itr!=comma_words.end();itr++)
	{
		string temp=*itr; b+=temp.length(); 
	}
	b=(double)(l+count)/b;
	b*=100;
	if(b>=75)
	{ 
		tot_count++;
		cout<<"line of your document:\n "<<ip_to_print<<endl;
		cout<<"\n\tCOPIED\n\n";
		cout<<"line from document: "<<all_files<<"\n"<<op_to_print<<"\n\n\n";
		return true;
	}
	return false;
	
}
bool call_rout(string str,string &source,string ip_to_print,string op_to_print,string all_files)
{
	int l;
	if(str.length()<=source.length())
		l=KMPSearch(str,source);
	else
		l=KMPSearch(source,str);
	if(str.length()==l)
	{
		tot_count++;
		cout<<"line of your document:\n "<<ip_to_print<<endl;
		cout<<"\n\tCOPIED\n\n";
		cout<<"line from document: "<<all_files<<"\n"<<op_to_print<<"\n\n\n";
		return true;
	}
	else 
	{
		double b;
		 b=((double)l/str.length())*100;
		if(b>=75)
		{	tot_count++;
			cout<<"line of your document:\n "<<ip_to_print<<endl;
			cout<<"\n\tCOPIED\n\n";
			cout<<"line from document: "<<all_files<<"\n"<<op_to_print<<"\n\n\n";
			return true;
		}
		else if(b>=40)
		{
			l=LCS(str,source);
			b=((double)l/str.length())*100;
			if(b>=75)
			{
				tot_count++;
				cout<<"line of your document:\n "<<ip_to_print<<endl;
				cout<<"\n\tCOPIED\n\n";
				cout<<"line from document: "<<all_files<<"\n"<<op_to_print<<"\n\n\n";
				return true;
			}
		}
		
	}
	
	return false;
}
int KMPSearch(string pattern,string str)
{
    int i=0,j=-1,max_count=-1,k=0;
    int lps[pattern.length()];
    transform(pattern.begin(),pattern.end(),pattern.begin(),::tolower);
	transform(str.begin(),str.end(),str.begin(),::tolower);  
    prepare_lps(pattern,lps,pattern.length());
    while(str[i]!='\0')
    {
        if(str[i]==pattern[j+1])
        {
            i++;
            j++;
            k++;
        }
        else if(j!=-1)
        {
            if(k>max_count)
           {
               max_count=k;
           }
            k=0;
            j=lps[j];
            j=j-1;
        }
        else
            i++;

        if(j==pattern.length()-1)
        {
            return pattern.length();
        }
    }
   	return max_count;

}  
void prepare_lps(string pattern,int lps[],int n)
{
   lps[0]=0;
   int i=1,j=0,k=1;
   while(i<pattern.length())
   {
   if(pattern[i]==pattern[j])
   {
       lps[k]=j+1;
       i++;
       j++;
       k++;
   }
   else if(j!=0)
   {
       j=lps[j-1];
   }
   else
    {
        lps[k]=0;
        i++;
        k++;
    }
    }
}

int LCS(string a,string b)
{
	int n=a.length();
	int m=b.length();
	int arr[n+1][m+1];
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if(i==0||j==0)
				arr[i][j]=0;
			else if(a[i-1]==b[j-1])
			{
			
				arr[i][j]=1+arr[i-1][j-1];
			}
			else
			{
			
				arr[i][j]=max(arr[i-1][j],arr[i][j-1]);
			}
		}
	}
	return arr[n][m];	
}  
