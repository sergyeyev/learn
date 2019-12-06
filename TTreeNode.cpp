#include "pch.h"
#include <iostream>
#include "TTreeNode.h"

TTreeNode::TTreeNode(TTreeNode *parent, TTreeNode *prior, int id, const char *name) {
	Id   = id;
	Name = (char *)malloc(255 * sizeof(char));
	strcpy_s(Name, 255, name);
	Parent = parent;
	Childs = NULL;
	Next   = NULL;
	Prior  = prior;
};

TTreeNode::~TTreeNode() {
	if (NULL != Next) {
		Next->setPrior( Prior );
	}
	if (NULL != Prior) {
		Prior->setNext( Next );
	}
	free(Name);
};

TTreeNode *TTreeNode::getNext() {
	return Next;
};

void TTreeNode::setNext(TTreeNode *next) {
	Next = next;
};

TTreeNode *TTreeNode::getPrior() {
	return Prior;
};

void TTreeNode::setPrior(TTreeNode *prior) {
	Prior = prior;
};

TTreeNode *TTreeNode::First() {
	TTreeNode *item = this;
	while (NULL != item->getPrior()) {
		item = item->getPrior();
	}
	return item;
};

TTreeNode *TTreeNode::Last() {
	TTreeNode *item = this;
	while (NULL != item->getNext()) {
		item = item->getNext();
	}
	return item;
};

int TTreeNode::Count() {
	int result = 0;
	TTreeNode *item = First();
	while (NULL != item) {
		result++;
		item = item->getNext();
	}
	return result;
};

TTreeNode *TTreeNode::Add(int id, char *name) {
	TTreeNode *item = new TTreeNode(Parent, this, id, name);
	if (NULL != Next) {
		Next->setPrior(item);
		item->setNext(Next);
	}
	setNext(item);
	return item;
};

TTreeNode *TTreeNode::AddChild(int id, char *name) {
	if (NULL == Childs) {
		Childs = new TTreeNode(this, NULL, id, name);
		return Childs;
	} else {
		return Childs->Last()->Add(id, name);
	}
};

void TTreeNode::PrintNode(const int Level) {
	for (int i = 0; i < Level; i++) {
		printf("  ");
	}
	printf("%2d.%-50s\n", Id, Name);
};

void TTreeNode::Print(const int Level) {
	TTreeNode *item = First();
	while (NULL != item) {
		item->PrintNode(Level);
		
		if (item->getChildCount() > 0) {
			item->getChilds()->Print( Level + 1 );
		}
		
		item = item->getNext();
	}
};

bool TTreeNode::isRoot() {
	return (NULL == Parent);
};

TTreeNode *TTreeNode::getParent() {
	return Parent;
};

int TTreeNode::getChildCount() {
	int result = 0;
	if (NULL != Childs) {
		result = Childs->Count();
	}
	return result;
};

TTreeNode *TTreeNode::getChilds() {
	TTreeNode *item = Childs;
	if (NULL != item) {
		item = item->First();
	}
	return item;
};

