#ifndef SYMBOLE_H
#define SYMBOLE_H

typedef struct symbole {
	char * name;
	int is_constant;
	//value val;
	struct symbole *next;
} symbole;

typedef struct tab {
	symbole *debut;
	symbole *fin;
} tab;

symbole* symbole_newtemp(tab *);
symbole* symbole_lookup(tab,char*);
symbole* symbole_add(tab * , char*);
void tab_symbole_free(tab);

#endif
