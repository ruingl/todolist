#ifndef DB_H
#define DB_H

#include "cJSON.h"

char *read_database(void);
void seed_database(void);
cJSON *init_database(void);
void print_list(void);
int string_exists(cJSON *json, char *str);
int add_todo(char *todo);

#endif // DB_H
