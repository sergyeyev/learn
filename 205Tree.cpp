#include "pch.h"
#include <iostream>
#include "TTreeNode.h"

int main() {
	int i = 0;
	int j, k, cnt, cnt2;
	char *name = (char *)malloc(255 * sizeof(char));
	strcpy_s(name, 255, "RootNode");
	TTreeNode *items = new TTreeNode(NULL, NULL, 0, name);
	for (i = 1; i < 10; i++) {
		strcpy_s(name, 255, "Node");
		items = items->Add(i, name);
		cnt = rand() % 10 + 1;
		for (j = 0; j < cnt; j++) {
			TTreeNode *Child1 = items->AddChild(j, name);
			cnt2 = rand() % 10 + 1;
			for (k = 0; k < cnt2; k++) {
				Child1->AddChild(k, name);
			}
		}
	}

	items->Print(0);

	return 0;
}
