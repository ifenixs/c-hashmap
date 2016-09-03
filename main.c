#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main(int argc, char *argv[]) {

    hashmap_t map = hashmap_init();

    FILE *str_case;
    str_case = fopen("str_case.dat", "r");

    while (!feof(str_case)) {
        char *str = (char *)malloc(12);
        fscanf(str_case, "%s\n", str);
        hashmap_put(map, str, (void *)str);
    }
    fclose(str_case);

    //hashmap_remove(map, "KY8831g");
    hashmap_dump(map);
    hashmap_destory(map);
    exit(0);
}
