//============================================================================
// Name        : log_analyzer.cpp
// Author      : 3109
// Version     :
// Copyright   : 
// Description : HTTP log analyzer
//============================================================================

#include <iostream>
#include <map>
#include<iomanip>
#include <string.h>
using namespace std;
#include <fstream>


class weblog
{
	ifstream file;
	int total,tuv,turf,tsf,t404,tr,log_size;
	public:
	char file_name[100];
	void read(const char*);
	void count_visits();
	void count_hosts();
	void get_line(string);
	void status_code();
	void os();
	void browsers();
	void unique_visits();
	void http_404();
	void sort(std::map<string,unsigned int> &temp_map);
	void static_files();
	void requested_files();
	void referrers_url();
	void analysis();
	void line();
};

void weblog::read(const char* file_name)
{
	file.open(file_name,ios::in);
}

void weblog::count_visits()
{
	read(file_name);
	int count=0;
	string line;
	if (file.is_open())
	{
		while ( getline (file,line) )
	    {
	    	count++;
	    }
	    file.close();
	}
	else
		cout << "Unable to open file";
	total=count;
}

void weblog::count_hosts()
{
	cout<<"\nHosts:\n\n";
	cout <<"No.of hits\tPercentage\tIP address\n";
	string line;
	int count;
    map<string, unsigned int>m;
    {
    	read(file_name);
        if (file.is_open())
        {
        	while ( getline (file,line))
		    {
        		string word;
		        int i=line.find (' ');
		        word=line.substr(0,i);
		        if (m.find(word) == m.end())
		        	m[word] = 1;
		        else
		        m[word]++;
		    }
		    file.close();
        }
		else
			cout<< "Couldn't open the file." << endl;
    }
    sort(m);
}

void weblog::get_line(string m)
{
	read(file_name);
	int count=0;
	string line;
	if (file.is_open())
	{
		while ( getline (file,line) )
		{
			if(line.find (m) != string::npos)
			{
				count++;
				cout<<line<<endl;
			}
	    }
	    file.close();
	}
	else
		cout << "Unable to open file";
	cout<<"Total no. of "<<m<<" methods:"<<count<<endl;
}

void weblog::status_code()
{
	cout<<"\nHTTP status codes:\n\n";
	cout <<"No.of hits\tStatus codes\n";
	string line;
	map<string, unsigned int>m;
    {
		read(file_name);
		if (file.is_open())
		{
			while ( getline (file,line))
			{
				string word;
				int i;
				i=line.find ("HTTP");
				word=line.substr(i+9,5);
			    if (m.find(word) == m.end())
			    	m[word] = 1;
			    else
			    	m[word]++;
			}
			file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
    }
    map<string, unsigned int>::iterator p;
    for (p = m.begin(); p != m.end(); p++)
    cout << p->first <<"\t\t"<< p->second << endl;
}

void weblog::os()
{
	cout<<"\nOperating Systems:\n\n";
	cout <<"No.of machines\tPercentage\tOperating system\n";
	string line;
	int count=0;
	map<string, unsigned int>m;
	map<string, unsigned int>h;
	{
		m["Windows"]=0;
		m["Macintosh"]=0;
		m["Linux"]=0;
		m["Unknown"]=0;
		read(file_name);
		if (file.is_open())
	    {
			while ( getline (file,line))
	        {

	            string word=line.substr(0,line.find(' '));
	            if (h.find(word) == h.end())
	            	h[word] = 1;
	            else
	              	h[word]++;
	           	if(h[word]==1)
	           	{
	           		if(line.find ("Windows")!=-1)
	           			m["Windows"]++;
	           		else if(line.find ("Macintosh")!=-1)
	           			m["Macintosh"]++;
	           		else if(line.find ("Linux")!=-1)
	           			m["Linux"]++;
	           		else
	           			m["Unknown"]++;
	           	}
	        }
	        file.close();
	    }
		else
			cout<< "Couldn't open the file." << endl;
	}
	sort(m);
}

void weblog::browsers()
{
	cout<<"\nBrowsers:\n\n";
	cout <<"No.of machines\tPercentage\tBrowsers\n";
	string line;
	map<string, unsigned int>m;
	{
		read(file_name);
		string temp="";
		if (file.is_open())
		{
			while ( getline (file,line))
			{
				string word=line.substr(0,line.find(' '));
				if(temp!=word)
				{
				if(line.find ("MSIE")!=-1)
	           		m["MSIE"]++;
	           	else if(line.find ("Crawlers")!=-1)
	           		m["Crawlers"]++;
	           	else if(line.find ("Firefox")!=-1)
	           		m["Firefox"]++;
	           	else if(line.find ("Opera")!=-1)
	           		m["Opera"]++;
	           	else if(line.find ("Safari")!=-1)
	           		m["Safari"]++;
	           	else if(line.find ("Chrome")!=-1)
	           		m["Chrome"]++;
	           	else
	           		m["Others"]++;
			}
			temp=word;
			}
	        file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
	}
	sort(m);
}

void weblog::unique_visits()
{
	cout<<"\nUnique visitors per day\n\n";
	cout <<"No.of hits\tPercentage\tClient IP address\tDate\n";
	string line;
	map<string,unsigned int>m;
	{
	 	 read(file_name);
	 	 if (file.is_open())
	 	 {
	 		 while ( getline (file,line))
	 		 {
	 			 string word,word1,word2,word3;
	    	     int i=line.find ("[");
	    	     word1=line.substr(0,i-5);
	    	     word2=line.substr(i+1,11);
	    	     //word3=line.substr(line.find('('),line.find(')'));
	    	     word=word1+"\t\t"+word2;//+'\t'+word3;
	    	     if (m.find(word) == m.end())
	    	    	 m[word] = 1;
	    	     else
	    	    	 m[word]++;
	 		 }
	 		 file.close();
	 	 }
	 	 else
	 		 cout<< "Couldn't open the file." << endl;
	}
	tuv=m.size();
	sort(m);
}

void weblog::http_404()
{
	cout<<"\nHTTP 404 Not Found URLs\n\n";
	cout <<"No.of hits\tPercentage\tHTTP 404 URLs\n";
	string line;
	map<string, unsigned int>m;
    {
		read(file_name);
		if (file.is_open())
		{
			while ( getline (file,line))
	        {
				string word,url="";
	           	int i;
	           	i=line.find ("HTTP");
	           	word=line.substr(i+9,5);
	           	if (word == " 404 ")
	           	{
	           		int i,t=line.find("GET");
	           		for(i=t+4;i<line.length()-1;i++)
	           		{
	           			if(line.at(i)!=' ')
	           				url+=line.at(i);
	           			else
	        	   		   break;
	           		}
	        	    if (m.find(url) == m.end())
	        	    	m[url] = 1;
	        	   	else
	        	   		m[url]++;
	           	}
	        }
	        file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
    }
	t404=m.size();
	sort(m);
}

void weblog::sort(std::map<string,unsigned int>&temp_map)
{
	multimap<unsigned int,string>m;
	map<string, unsigned int>::iterator p;
	for (p = temp_map.begin(); p != temp_map.end(); p++)
	{
		m.insert(pair<unsigned int,string>(p->second,p->first));
	}
	multimap<unsigned int,string>::reverse_iterator rit;
	rit=m.rbegin();
	for(int i=1;i<10;i++)
	{
		if(rit!=m.rend())
		{
			double percent=(double(rit->first*100))/double(total);
			cout << rit->first <<"\t\t"<<setprecision (2) << fixed <<percent<<"\t\t"<< rit->second << endl;
			rit++;
		}
		else
			break;
	}
}

void weblog::static_files()
{
	cout<<"\nRequested static files\n\n";
	cout <<"No.of hits\tPercentage\tRequested static files\n";
	string format[]={"jpg","css","swf","js","gif","png"};
	string line;
	int k=-1;
	map<string, unsigned int>m;
	{
		read(file_name);
		if (file.is_open())
		{
			while ( getline (file,line))
		    {
				for(int j=0;j<6;j++)
				{
					if(line.find(format[j])!=-1)
					{
						k=line.find(format[j]);
						break;
					}
				}
				string word;
		      	int i;
		        i=line.find ("www");
		        if(k!=-1 and i!=-1)
		        {
		        	word=line.substr(i,k+3-i);
		        	if (m.find(word) == m.end())
		        	 	m[word] = 1;
		        	else
		        		m[word]++;
		        	k=-1;
		        }
		    }
		        file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
	}
	tsf=m.size();
	sort(m);
}

void weblog::requested_files()
{
	cout<<"\nRequested URLs\n\n";
	cout <<"No.of hits\tPercentage\tRequested files\n";
	string line;
	string method[]={"GET","POST"};
	map<string, unsigned int>m;
    {
		read(file_name);
		if (file.is_open())
		{
			while ( getline (file,line))
	        {
				string url="";
	           	int i,t;
				for(int j=0;j<2;j++)
				{
					if(line.find(method[j])!=-1)
					{
						t=line.find(method[j]);
						break;
					}
				}
	           if(t!=-1)
	           {
	        	   url+=line.at(t+4);
	        	   for(i=t+5;i<line.length()-1;i++)
	              	{
	           		if(line.at(i)!=' ')
	           			url+=line.at(i);
	           		else
	        		   break;
	              	}
	           }

	        	if (m.find(url) == m.end())
	        	   	m[url] = 1;
	        	else
	        		m[url]++;
	        }
	        file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
    }
	turf=m.size();
    sort(m);
}

void weblog::referrers_url()
{
	cout<<"\nReferrers URLs\n\n";
	cout <<"No.of hits\tPercentage\tReferrer URL\n";
	string line;
	map<string, unsigned int>m;
    {
		read(file_name);
		if (file.is_open())
		{
			while ( getline (file,line))
	        {
				string url="";
	           	int i,t=line.find("\"http://");
	           	if(t!=-1)
	           	{
	           		for(i=t+1;i<line.length()-1;i++)
	              	{
	           			if(line.at(i)!='"')
	           				url+=line.at(i);
	           			else
	           				break;
	              	}
	           	if (m.find(url) == m.end())
	           		m[url] = 1;
	           	else
	           		m[url]++;
	           	}
	        }
	        file.close();
		}
		else
			cout<< "Couldn't open the file." << endl;
    }
	tr=m.size();
    sort(m);
}
void weblog::analysis()
{
	cout<<"\nSTATISTICS:";
	cout<<"\n\nTotal number of visits:"<<total<<"\n\nTotal number of unique visitors:"<<tuv<<"\n\nTotal number of unique reqested files:"<<turf<<"\n\nTotal number of static files:"<<tsf<<"\n\nTotal number of HTTP 404 URLs:"<<t404<<"\n\nTotal number of referrer URLs:"<<tr<<endl;
}

void weblog::line()
{
	for(int i=0;i<100;i++)
	cout<<"-";
}

int main()
{
	weblog w;
	cout<<"\nEnter log file path:";
	cin.getline(w.file_name, 100);
	cout<<"\nHTTP LOG FILE ANALYSIS:\n";
	w.count_visits();
    w.line();
	w.unique_visits();
	w.line();
	w.requested_files();
	w.line();
	w.static_files();
	w.line();
	w.http_404();
	w.line();
	w.count_hosts();
	w.line();
	w.os();
	w.line();
	w.browsers();
	w.line();
	w.referrers_url();
	w.line();
	w.status_code();
	w.line();
	w.analysis();
	w.line();
	//w.get_line("GET");
	return 0;
}
