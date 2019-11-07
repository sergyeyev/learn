#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "tcircle.h"
#include "list2link.h"

list2 *list2_create() {
	list2 *item;
	item = (list2 *)malloc(sizeof(struct list2));
	item->geom = NULL;
	item->next = NULL;
	item->prev = NULL;
	return(item);
};

list2 *list2_ins(list2 *list) {
	list2 *item = list2_create(); //создание эл.
	item->prev = list;  // инициализация указателя предыдущего эл-та
	if (NULL != list) {  // преверяем, существует ли предыдущий элемент (пустой список)
		item->next = list->next;
		if (NULL != list->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			list->next->prev = item;
		}
		list->next = item; // переопределение упредыдущего эл-та указателя следующего на себя
	}
	return(item);
};

void list2_del(list2 *list) {
	if (NULL == list) {
		return;
	}
	list2 *nxt, *prv;
	nxt = list->next;
	prv = list->prev;
	if (NULL != nxt) {   // не является ли элемент конечным в списке? 
		nxt->prev = list->prev;
	}
	if (NULL != prv) {   // не является ли элемент первым в списке?
		prv->next = list->next;
	}
	if (NULL != list->geom) {
		delete list->geom;
	}
	free(list);
};

list2 *list2_gotofirst(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while(NULL != item->prev) {
			item = item->prev;
		}
	}
	return (item);
};

 list2 *list2_gotolast(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while (NULL != item->next) {
			item = item->next;
		}
	}
	return (item);
};

int list2_count(list2 *list) {
	int result = 0;
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		result++;
		item = item->next;
	}
	return result;
 };


void list2_swap(list2 *item1, list2 *item2) {
	if ( (NULL == item1) || (NULL == item2) ) {
		return;
	}
	if ( (item1->next == item2) && (item2->prev == item1) ) { // рядом стоящие элементы
		list2 *next0 = item2->next;
		list2 *prev0 = item1->prev;
		item1->next = next0;
		item1->prev = item2;
		item2->next = item1;
		item2->prev = prev0;
		if (NULL != next0) {
			next0->prev = item1;
		}
		if (NULL != prev0) {
			prev0->next = item2;
		}
	}else if ((item2->next == item1) && (item1->prev == item2)) { // рядом стоящие элементы
		list2 *next0 = item1->next;
		list2 *prev0 = item2->prev;
		item1->next = item2;
		item1->prev = prev0;
		item2->next = next0;
		item2->prev = item1;
		if (NULL != next0) {
			next0->prev = item2;
		}
		if (NULL != prev0) {
			prev0->next = item1;
		}
	}else { // отстоящие друг от друга элементы
		list2 *next2 = item1->next;
		list2 *prev2 = item1->prev;
		item1->next = item2->next;
		item1->prev = item2->prev;
		item2->next = next2;
		item2->prev = prev2;
		if (NULL != item1->next) {
			item1->next->prev = item1;
		}
		if (NULL != item1->prev) {
			item1->prev->next = item1;
		}
		if (NULL != item2->next) {
			item2->next->prev = item2;
		}
		if (NULL != item2->prev) {
			item2->prev->next = item2;
		}
	}
}

void list2_print(list2 *list) {
 	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->geom) {
			item->geom->Print();
		}
		item = item->next;
	}
 };

void list2_printtext(list2 *list) {
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->geom) {
			item->geom->PrintText();
		}
		item = item->next;
	}
};

void list2_clear(list2 *list) {
	list2 *item = list2_gotolast(list);
	while (NULL != item) {
		list2 *delitem = item;
		item = item->prev;
		list2_del(delitem);
	}
}

int list2_savetofile(list2 *list, const char *filename) {
	FILE *file;
	int result = fopen_s(&file, filename, "w+");
	if (0 == result) {
		list2 *item = list2_gotofirst(list);
		while (NULL != item) {
			item->geom->SaveToFile(file);
			item = item->next;
		}
		fclose(file);
	}
	return result;
}


list2 *list2_loadfromfile(list2 *list, const char *filename) {
	list2 *item = list;
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		char *objname = (char *)malloc( defaultNameLength * sizeof(char));
		char *buffer  = (char *)malloc(1024 * sizeof(char));
		char *work = buffer;
		nullStr(buffer, 1024);
		while (EOF != (*work = fgetc(file))) {
			if ('\n' == *work) {
				parseItem(buffer, '|', objname);
				item = list2_ins(item);
				if (0 == strcmp(objname, "TPOIN")) {
					item->geom = new TPoint();
				}else if (0 == strcmp(objname, "TRECT")) {
					item->geom = new TRect();
				}else if (0 == strcmp(objname, "TCIRC")) {
					item->geom = new TCircle();
				}

				

				if (NULL != item->geom) {
					item->geom->LoadFromStr(buffer);
				}
				nullStr(buffer, 1024);
				work = buffer;
			}else {
				work++;
			}
		}
		if( (work != buffer) && (0 < strlen(buffer)) ){
			parseItem(buffer, '|', objname);
			item = list2_ins(item);
			if (0 == strcmp(objname, "TPOIN")) {
				item->geom = new TPoint();
			}else if (0 == strcmp(objname, "TRECT")) {
				item->geom = new TRect();
			}else if (0 == strcmp(objname, "TCIRC")) {
				item->geom = new TCircle();
			}
			if (NULL != item->geom) {
				item->geom->LoadFromStr(buffer);
			}
		}
		free(buffer);
	    free(objname);
		fclose(file);
	}
	return item;
}

int list2_contains(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->geom->Contains(x, y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
};

list2 *list2_findxy(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->geom->Contains(x, y)) {
			return item;
		}
		item = item->next;
	}
	return NULL;
};

void list2_sortby_y(list2 *list) {
	int swapCount = 0;
	list2 *p = NULL;
	do {
		swapCount = 0;
		p = list2_gotofirst(list);
		while (NULL != p) {
			if (NULL != p->next) {
				if (p->geom->getY() > p->next->geom->getY()) {
					list2_swap(p, p->next);
					swapCount++;
				}
			}
			p = p->next;
		}
	} while (swapCount != 0);
}

void list2_sortby_name(list2 *list) {

}

void list2_search_name(list2 *list, char *searchStr) {
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->geom) {
			if ( NULL != strstr(item->geom->nameupper, searchStr) ) {
				item->geom->PrintText();
			}
		}
		item = item->next;
	}
}

void list2_search_nametype(list2 *list, char *searchStr, TPointType t) {
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->geom) {
			TPoint *p = (TPoint *)item->geom;
			if( (NULL != strstr(p->nameupper, searchStr)) && (p->getTyp() == t) ) {
				item->geom->PrintText();
			}
		}
		item = item->next;
	}
}