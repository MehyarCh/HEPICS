/*
 * Utils.h
 *
 *  Created on: Feb 2, 2019
 *      Author: ibrahim
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "List.h"

#define TWO_PI 6.2831853071795864769252866f

class Utils {
public:

	static void error(const char *s)
	{
	    perror(s);
	    assert(0);
	    exit(-1);
	}

	static void malloc_error()
	{
	    fprintf(stderr, "Malloc error\n");
	    exit(-1);
	}

	static void file_error(char *s)
	{
	    fprintf(stderr, "Couldn't open file: %s\n", s);
	    exit(0);
	}

	static void del_arg(int argc, char **argv, int index)
	{
	    int i;
	    for(i = index; i < argc-1; ++i) argv[i] = argv[i+1];
	    argv[i] = 0;
	}

	static int find_int_arg(int argc, char **argv, char *arg, int def)
	{
	    int i;
	    for(i = 0; i < argc-1; ++i){
	        if(!argv[i]) continue;
	        if(0==strcmp(argv[i], arg)){
	            def = atoi(argv[i+1]);
	            del_arg(argc, argv, i);
	            del_arg(argc, argv, i);
	            break;
	        }
	    }
	    return def;
	}

	static void strip(char *s)
	{
	    size_t i;
	    size_t len = strlen(s);
	    size_t offset = 0;
	    for(i = 0; i < len; ++i){
	        char c = s[i];
	        if(c==' '||c=='\t'||c=='\n') ++offset;
	        else s[i-offset] = c;
	    }
	    s[len-offset] = '\0';
	}



	static char *fgetl(FILE *fp)
	{
	    if(feof(fp)) return 0;
	    size_t size = 512;
	    char *line = (char *)malloc(size*sizeof(char));
	    if(!fgets(line, size, fp)){
	        free(line);
	        return 0;
	    }

	    size_t curr = strlen(line);

	    while((line[curr-1] != '\n') && !feof(fp)){
	        if(curr == size-1){
	            size *= 2;
	            line = (char *)realloc(line, size*sizeof(char));
	            if(!line) {
	                printf("%ld\n", size);
	                malloc_error();
	            }
	        }
	        size_t readsize = size-curr;
	        if(readsize > INT_MAX) readsize = INT_MAX-1;
	        fgets(&line[curr], readsize, fp);
	        curr = strlen(line);
	    }
	    if(line[curr-1] == '\n') line[curr-1] = '\0';

	    return line;
	}

	static List *get_paths(char *filename)
	{
	    char *path;
	    FILE *file = fopen(filename, "r");
	    if(!file) file_error(filename);
	    List *lines = new List();
	    while((path=fgetl(file))){
	        lines->list_insert(path);
	    }
	    fclose(file);
	    return lines;
	}

	static char **get_labels(char *filename)
	{
	    List *plist = get_paths(filename);
	    char **labels = (char **)(plist->list_to_array());
	    plist->~List();
	    return labels;
	}

	// From http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
	static float rand_normal()
	{
	    static int haveSpare = 0;
	    static double rand1, rand2;

	    if(haveSpare)
	    {
	        haveSpare = 0;
	        return sqrt(rand1) * sin(rand2);
	    }

	    haveSpare = 1;

	    rand1 = rand() / ((double) RAND_MAX);
	    if(rand1 < 1e-100) rand1 = 1e-100;
	    rand1 = -2 * log(rand1);
	    rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;

	    return sqrt(rand1) * cos(rand2);
	}

	static float rand_uniform(float min, float max)
	{
	    if(max < min){
	        float swap = min;
	        min = max;
	        max = swap;
	    }
	    return ((float)rand()/RAND_MAX * (max - min)) + min;
	}

	static void top_k(float *a, int n, int k, int *index)
	{
	    int i,j;
	    for(j = 0; j < k; ++j) index[j] = -1;
	    for(i = 0; i < n; ++i){
	        int curr = i;
	        for(j = 0; j < k; ++j){
	            if((index[j] < 0) || a[curr] > a[index[j]]){
	                int swap = curr;
	                curr = index[j];
	                index[j] = swap;
	            }
	        }
	    }
	}

	static float sec(clock_t clocks){
	    return (float)clocks/CLOCKS_PER_SEC;
	}

};

#endif /* SRC_UTILS_H_ */
