#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbole.h"

symbole* symbole_newtemp(tab * tds)
{
    symbole * new_symb = (symbole *)malloc(sizeof(symbole));
    if(new_symb==NULL)
    {
        fprintf(stderr,"plus de memoire dispo\n");
        exit(EXIT_FAILURE);
    }
    new_symb->next =NULL;
	if (tds->fin == NULL)
	{
        tds->debut = new_symb;
        tds->fin = new_symb;
	}
	else
	{
        tds->fin->next = new_symb;
        tds->fin = new_symb;
	}
    return new_symb;
}

symbole* symbole_lookup(tab tds,char * s)
{
	symbole *pt = tds.debut; 
	while (pt != NULL)
	{
        if(pt->name != NULL && strcmp(s,pt->name)==0)
            break;
        pt = pt->next;
	}
	return pt;
}

symbole* symbole_add(tab *tds, char * s)
{
	symbole * pt = symbole_lookup(*tds,s);
	if(pt == NULL)
	{
		pt = symbole_newtemp(tds);
		pt->name = s;
		pt->is_constant = 0;
	}
    else
    {
        free(s);
    }
	return pt;
}

void tab_symbole_free(tab tds){
	symbole *pt = tds.debut;
	symbole *ptfree;
	while(pt != NULL)
	{
		ptfree = pt;
		pt = pt->next;
        free(ptfree->name);
        ptfree->next = NULL;
		free(ptfree);
	}
}
