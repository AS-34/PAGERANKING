#include <iostream>
#include <vector>
#include <string>
#include <map>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include "PageRank.h"

using namespace std;

void FileCreate(vector<Node*> &nodes,string srcFile)
{
	map<string, Node*> m;
	//use try catch
	ifstream fin(srcFile.c_str());
	if(!fin)
	{
		throw 1;
	}

	stringstream ss1;

	string temp;
	getline(fin,temp);
	ss1<<temp;
	while(ss1>>temp)
	{
		Node* tempNode = new Node(temp);
		nodes.push_back(tempNode);
		m[temp] = tempNode;
	}
	
	int ind=0;
	while(!fin.eof())
	{
		stringstream ss;
		getline(fin,temp);
		ss<<temp;
		while(ss>>temp)
		{
			if(m[temp] == 0)
			{
				//cerr<< "Something Went Wrong \n";
				continue;
			}
			nodes[ind]->InsertLinkdInNode(m[temp]);
		}
		ind++;
	}


	fin.close();
}

void InitGraph(vector<Node*> &nodes)
{

    // example 1
    Node * a = new Node("A");
    Node * b = new Node("B");
    Node * c = new Node("C");
    Node * d = new Node("D");

    nodes.push_back(a);
    nodes.push_back(b);
    nodes.push_back(c);
    nodes.push_back(d);
    // link in node
    // a <- b, c, d
    a->InsertLinkdInNode(b);
    a->InsertLinkdInNode(d);
    // b <- d
    b->InsertLinkdInNode(c);
    b->InsertLinkdInNode(d);

    // c <- b, d
    c->InsertLinkdInNode(b);
    c->InsertLinkdInNode(d);

    d->InsertLinkdInNode(b);
}

void TestPageRank(string srcFile,string logFile)
{
    // build graph
    vector<Node*> nodes;

    FileCreate(nodes,srcFile);

    //InitGraph(nodes);
    PageRank pr;
    pr.Calc(nodes, 1000);
    pr.PrintPageRank(nodes);

    pr.SaveLog(nodes,logFile);
}

int main(int argc, const char ** argv)
{

	system("clear");
	char choice='y';
	cout<<"                ~> _WELCOME TO PAGE_RANKING PROGRAM_ <~"<<endl;
	while(choice!='n')
    {
    	string srcFile,logFile;
    	cout<<"\tEnter Graph File Name : ";cin>>srcFile;
    	cout<<"\tEnter Log File Name   : ";cin>>logFile;
    	if(srcFile==logFile)
    	{
    		cerr<<"Graph and Log FileName Cannot be equal!"<<endl;
    		continue;
    	}

    	try
    	{
    		TestPageRank(srcFile,logFile);
    	}
    	catch(int ex)
    	{
    		if(ex==1)
    			cout<<"Graph File Opening Failed"<<endl;
    	}

    	cout<<"================================================"<<endl;
    	cout<<"Continue(Y/N): ";cin>>choice;
    }

    return 0;
}



//~~~~~~~~~~~~~~~~~~~[TRASH BUFFER]~~~~~~~~~~~~~~~~~~~~~~~~~//

/*for(int i=0;i<nodes.size();++i)
			{
				if(temp==nodes[i]->GetName())
				{
					nodes[ind]->InsertLinkdInNode(nodes[i]);
					break;
				}
			}*/