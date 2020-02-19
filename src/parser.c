#include "parser.h"
#include<stdio.h>
#include"hashtable.h"
#include "parserDef.h"
#include <string.h>
#include<stdlib.h>
#include "lexDef.h"
#include <stdbool.h>
#include "set.h"
#define RULES_BUFF 100

hashtable strToEnum;

set* nonterminal_FS;
set* First_Set;

bool isterminal(type t)
{
    return ((t>=$) && (t<ENUM_END));
}

bool isNonterminal(type t)
{
    return ((t>ENUM_START)&&(t<$));
}

void make_str_to_enum()
{
    strToEnum = getHashTable(100);
    for(int i=ENUM_START+1;i<ENUM_END;i++)
        insertTable(strToEnum,symbol_map[i],i);
}

void getFirstSet(productions grammar)
{
    nonterminal_FS = (set *)malloc(sizeof(set)*($));
    for(int i=0;i<$;i++)
	nonterminal_FS[i] = getSet();
    
    First_Set = (set *)malloc(sizeof(set)*(grammar.no_productions));
    for(int i =0;i<grammar.no_productions;i++)
	First_Set[i] = getSet();

    bool updated = true;
    while(updated)
    {
	updated = false;
	for(int i=0;i<grammar.no_productions;i++)
	{
	    prodn temp = grammar.rules[i];  //1 production rule
	    for(int j=1;j<temp.size;j++) //start j from 1.
	    {
		if(isterminal(temp.rule[j]))
		{
			if(!isSetMember(First_Set[i],temp.rule[j]))
			{
			    insertSet(First_Set[i],temp.rule[j]);			
			    updated = true;
			}
			if(!isSetMember(nonterminal_FS[temp.non_terminal],temp.rule[j]))
			{
			    insertSet(nonterminal_FS[temp.non_terminal],temp.rule[j]);
			    updated = true;
			}
			break;	
		}
		else if(isNonterminal(temp.rule[j]))
		{

		    if(setUnion(First_Set[i],nonterminal_FS[temp.rule[j]]))
			updated = true;
		    
		    if(setUnion(nonterminal_FS[temp.non_terminal],nonterminal_FS[temp.rule[j]]))
			updated = true;
		    
		    if(!isSetMember(nonterminal_FS[j],EPS))
			break;
		}
		else
		{
		    printf("INCORRECT SYMBOL\n");
		    return;
		}
	    }
	}
    }
    printf("\n\n");
    for(int i=ENUM_START+1;i<$;i++)
	printSet(nonterminal_FS[i]);
    
    printf("\n\n");
    for(int i =0;i<grammar.no_productions;i++)
	printSet(First_Set[i]);


}

productions read_grammar()
{
    FILE* fptr = fopen("productions.txt","r");
    char buff[1000];
    int rule_count = 0;

    //allocate space to store grammar rules
    productions grammar;
    grammar.rules = (prodn *)malloc(sizeof(prodn)*RULES_BUFF);
    
    //read line by line rules
    while(fgets(buff, 1000, fptr))
    {
	int count = 0;
	type* rule =(type*)malloc(RULES_BUFF*sizeof(type));
	char* tok;  
	tok = strtok(buff,"\n");
	tok = strtok(buff, " "); 
	//tokenize rules into Nonterminals and Terminals
	//then conver to enum and store in prodn struct.
	while (tok != 0) {
	    rule[count] = searchTable(strToEnum,tok)->val;
	    tok = strtok(0, " "); 
	    count++;
	    
	}
	//remove extra wasted space using realloc
	rule =(type *) realloc(rule, sizeof(type)*count);
	
	//make production from given rule
	prodn temp;
	temp.rule = rule;
	//count stores the size of the production rule
	//including rhs and lhs.
	temp.size = count;
	//LHS non terminal
	temp.non_terminal = rule[0];

	//add the parsed rule into the grammar
	grammar.rules[rule_count] = temp;
	rule_count++;
    }
    // resize grammar struct to remove wasted space
    grammar.rules = (prodn*)realloc(grammar.rules,sizeof(prodn)*rule_count);
    //no of rules in grammar
    grammar.no_productions = rule_count;
  
    return grammar;
}
