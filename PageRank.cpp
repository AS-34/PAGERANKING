#include "PageRank.h"
#include <iostream>
#include<fstream>
double tot = 6;

PageRank::PageRank(double q) : q_(q)
{
    // q_ must < 1
}


PageRank::~PageRank(void)
{
}

void PageRank::Calc(vector<Node*> & nodes, int n)
{
    for (int i=0; i<n; ++i)
    {
    	double dp = 0;
        vector<Node*>::const_iterator citr;
        for (citr = nodes.begin(); citr!=nodes.end(); ++citr)
        {
        	 Node * node = *citr;
        	if(node->sze() == 0)
        		dp = dp + q_ * (node->GetPageRank()) / tot;
        }
        for (citr = nodes.begin(); citr!=nodes.end(); ++citr)
        {
        	Node * node = *citr;
        	node->new_page_rank_ = dp + (1 - q_) / tot;
        	set<Node*>:: const_iterator citr1;
        	for (citr1 = node->linkin_nodes_.begin(); citr1!=node->linkin_nodes_.end(); ++citr1)
        	{
        		Node * node1 = *citr1;
        		node->new_page_rank_ += q_ * (node1->old_page_rank_) / node1->sze();
        	}
       	}
       	for (citr = nodes.begin(); citr!=nodes.end(); ++citr)
       	{
       		Node * node = *citr;
       		node->old_page_rank_ = node->new_page_rank_;
       	}
    }
}

void PageRank::PrintPageRank(vector<Node*> & nodes)
{
    double total_pr = 0;
    vector<Node*>::const_iterator citr = nodes.begin();
    for (; citr!=nodes.end(); ++citr)
    {
        Node * node = *citr;
        cout<<node->GetInfo();
        total_pr += node->GetPageRank();
    }
    cout << "Total PR:" << total_pr << endl;
}

void PageRank::SaveLog(vector<Node*> & nodes,string fname)
{
    ofstream fout(fname.c_str(),ios::trunc);

    if(!fout)
    {
        cerr<<"LOG FILE OPENING FAILED"<<endl;
        return;
    }

    double total_pr = 0;
    vector<Node*>::const_iterator citr = nodes.begin();
    for (; citr!=nodes.end(); ++citr)
    {
        Node * node = *citr;
        fout<<node->GetInfo();
        total_pr += node->GetPageRank();
    }
    fout << "Total PR:" << total_pr << endl;
}
//~~~~~~~~~~~~~~~~~~~[TRASH BUFFER]~~~~~~~~~~~~~~~~~~~~~~~~~//

/*void PageRank::Calc(vector<Node*> & nodes, int n)
{
    for (int i=0; i<n; ++i)
    {
        vector<Node*>::const_iterator citr = nodes.begin();
        for (; citr!=nodes.end(); ++citr)
        {
            Node * node = *citr;
            Calc(node);
        }
    }
}*/

/*double PageRank::Calc(Node * node)
{
    double pr = node->CalcRank();
    if (pr < 0.00000000000000000000001 && pr > -0.00000000000000000000001) //pr == 0
    {
        pr = 1-q_;
    }
    else
    {
        pr = pr * q_ + 1-q_;
    }
    node->SetPageRank(pr);
    return pr;
}
*/