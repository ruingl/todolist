#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <stdio.h>

char *read_database() {
    FILE *file = fopen("database.json", "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *json_data = malloc(length + 1);
    if (!json_data) {
        fclose(file);
        return NULL;
    }

    if (fread(json_data, 1, length, file) != (size_t)length) {
        free(json_data);
        fclose(file);
        return NULL;
    }

    json_data[length] = '\0';
    fclose(file);
    return json_data;
}

void seed_database() {
    FILE *file = fopen("database.json", "w");
    if (!file) return;

    cJSON *json = cJSON_CreateArray();
    char *json_str = cJSON_PrintUnformatted(json);
    if (json_str) {
        fprintf(file, "%s", json_str);
        free(json_str);
    }

    fclose(file);
    cJSON_Delete(json);
}

cJSON *init_database() {
    char *json_data = read_database();
    if (!json_data) {
        seed_database();
        json_data = read_database();
        if (!json_data) return cJSON_CreateArray();
    }

    cJSON *json = cJSON_Parse(json_data);
    free(json_data);

    if (!json) {
        json = cJSON_CreateArray();
        seed_database();
    }

    return json;
}

void print_list() {
    cJSON *json = init_database();
    if (!json) return;

    int array_length = cJSON_GetArraySize(json);
    if (array_length == 0) {
        printf("Nothing to-do yet!\n");
    } else {
        int index = 1;
        cJSON *item = NULL;

        cJSON_ArrayForEach(item, json) {
            if (cJSON_IsString(item)) {
                printf("%d. %s\n", index++, item->valuestring);
            }
        }
    }

    cJSON_Delete(json);
}

int string_exists(cJSON *json, char *str) {
    cJSON *item;
    cJSON_ArrayForEach(item, json) {
        if (cJSON_IsString(item) && strcmp(item->valuestring, str) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_todo(char *todo) {
    FILE *file = fopen("database.json", "w");
    if (!file) return 0;

    cJSON *json = init_database();
    if (!json) {
        fclose(file);
        return 0;
    }

    cJSON *new_todo = cJSON_CreateString(todo);
    if (!new_todo) {
        cJSON_Delete(json);
        fclose(file);
        return 0;
    }

    if (string_exists(json, todo) == 1) {
        return 1;
    }

    cJSON_AddItemToArray(json, new_todo);

    char *json_str = cJSON_PrintUnformatted(json);
    fprintf(file, "%s", json_str);
    fclose(file);

    free(json_str);
    cJSON_Delete(json);

    return 1;
}
