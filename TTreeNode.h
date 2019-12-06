#ifndef TTREENODE_H
#define TTREENODE_H

class TTreeNode {
private:
	int Id;
	char *Name;
	TTreeNode *Parent;
	TTreeNode *Childs;
	TTreeNode *Next;
	TTreeNode *Prior;
public:
	TTreeNode(TTreeNode *parent, TTreeNode *prior, int id, const char *name);
	virtual ~TTreeNode();
	TTreeNode *getNext();
	void setNext(TTreeNode *next);
	TTreeNode *getPrior();
	virtual void setPrior(TTreeNode *next);
	TTreeNode *First();
	TTreeNode *Last();
	TTreeNode *Add(int id, char *name);
	int Count();
	virtual void PrintNode(const int Level);
	virtual void Print(const int Level);
	TTreeNode *getParent();
	int getChildCount();
	TTreeNode *getChilds();
	bool isRoot();
	TTreeNode *AddChild(int id, char *name);
protected:

};

#endif