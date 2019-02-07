/*
 * Options_list.h
 *
 *  Created on: Feb 2, 2019
 *      Author: ibrahim
 */

#ifndef SRC_OPTIONS_LIST_H_
#define SRC_OPTIONS_LIST_H_

#include <string.h>
#include <stdio.h>
#include "List.h"
#include "Utils.h"

class Options_list {
private:
    char *key;
    char *val;
    int used;
public:
	Options_list(char *key, char *val);
	virtual ~Options_list();

	static void option_insert(List *l, char *key, char *val) {
		Options_list *p = new Options_list(key, val);
	    l->list_insert(p);
	}

	static char *option_find(List *l, char const *key) {
		Node *n = l->getFront();
		while (n) {
			Options_list *p = (Options_list *) n->getVal();
			if (strcmp(p->getKey(), key) == 0) {
				p->setUsed(1);
				return p->getVal();
			}
			n = n->getNext();
		}
		return 0;
	}

	static int option_find_int(List *l, char const *key, int def) {
		char *v = option_find(l, key);
		if (v)
			return atoi(v);
		fprintf(stderr, "%s: Using default '%d'\n", key, def);
		return def;
	}

	static float option_find_float(List *l, char *key, float def)
	{
	    char *v = option_find(l, key);
	    if(v) return atof(v);
	    fprintf(stderr, "%s: Using default '%lf'\n", key, def);
	    return def;
	}

	static float option_find_float_quiet(List *l, char *key, float def)
	{
	    char *v = option_find(l, key);
	    if(v) return atof(v);
	    return def;
	}

	static char *option_find_str(List *l, char *key, char *def)
	{
	    char *v = option_find(l, key);
	    if(v) return v;
	    if(def) fprintf(stderr, "%s: Using default '%s'\n", key, def);
	    return def;
	}

	static int option_find_int_quiet(List *l, char const *key, int def)
	{
	    char *v = option_find(l, key);
	    if(v) return atoi(v);
	    return def;
	}

	static int read_option(char *s, List *options)
	{
	    size_t i;
	    size_t len = strlen(s);
	    char *val = 0;
	    for(i = 0; i < len; ++i){
	        if(s[i] == '='){
	            s[i] = '\0';
	            val = s+i+1;
	            break;
	        }
	    }
	    if(i == len-1) return 0;
	    char *key = s;
	    option_insert(options, key, val);
	    return 1;
	}

	static List *read_data_cfg(char *filename)
	{
	    FILE *file = fopen(filename, "r");
	    if(file == 0) Utils::file_error(filename);
	    char *line;
	    int nu = 0;
	    List *options = new List();
	    while((line = Utils::fgetl(file)) != 0){
	        ++ nu;
	        Utils::strip(line);
	        switch(line[0]){
	            case '\0':
	            case '#':
	            case ';':
	                free(line);
	                break;
	            default:
	                if(!read_option(line, options)){
	                    fprintf(stderr, "Config file error line %d, could parse: %s\n", nu, line);
	                    free(line);
	                }
	                break;
	        }
	    }
	    fclose(file);
	    return options;
	}

	char* getKey() {
		return key;
	}

	void setKey(char* key) {
		this->key = key;
	}

	int getUsed() {
		return used;
	}

	void setUsed(int used) {
		this->used = used;
	}

	char* getVal() {
		return val;
	}

	void setVal(char* val) {
		this->val = val;
	}
};

#endif /* SRC_OPTIONS_LIST_H_ */
