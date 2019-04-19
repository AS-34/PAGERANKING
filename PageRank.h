#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// use graph store webpage, weight representlink times
class Node
{
private:
    string name_;
public:
    
    set<Node*> linkin_nodes_;
    set<Node*> linkout_nodes_;
    double old_page_rank_;
    double new_page_rank_;
    explicit Node(string name, double pr = 1/6){
        name_ = name;
        old_page_rank_ = pr;
    }

    ~Node()
    {
        linkin_nodes_.clear();
    }
    int sze()
    {
        return linkout_nodes_.size();
    }
    void InsertLinkdInNode(Node* node)
    {
        if (linkin_nodes_.find(node) == linkin_nodes_.end())
        {
            linkin_nodes_.insert(node);
        }
        node->InsertLinkOutNode(this);
    }

    void InsertLinkOutNode(Node* node)
    {
        if (linkout_nodes_.find(node) == linkout_nodes_.end())
        {
            linkout_nodes_.insert(node);
        }
    }

    double GetPageRank()
    {
        return old_page_rank_;
    }

    void SetPageRank(double pr)
    {
        old_page_rank_ = pr;
    }

    double CalcRank()
    {
        double pr = 0;
        set<Node*>::const_iterator citr = linkin_nodes_.begin();
        for (; citr != linkin_nodes_.end(); ++citr)
        {
            Node * node = *citr;
            pr += node->GetPageRank()/node->GetOutBoundNum();
        }
        return pr;
    }

    size_t GetOutBoundNum()
    {
        return linkout_nodes_.size();
    }

    size_t GetInBoundNum()
    {
        return linkin_nodes_.size();
    }

    void PrintNode()
    {
        cout << "Node:" << name_ << "'s pagerank is: " << new_page_rank_ << endl;
    }

    string GetInfo()
    {
        return "Node:" + name_ + "'s pagerank is: "+ to_string(new_page_rank_) +"\n";
    }
    string GetName()
    {
        return name_;
    }

};

class PageRank
{
private:
    double q_;
public:
    PageRank(double q=0.85);
    ~PageRank(void);
    void Calc(vector<Node*> & nodes, int n);
    double Calc(Node* node);
    void PrintPageRank(vector<Node*> & nodes);
    void SaveLog(vector<Node*> & nodes,string fname);
};