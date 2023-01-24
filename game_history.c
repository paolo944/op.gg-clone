#include "game_history.h"

int get_game_history(char *puuid, char ***games){
    char url[URL_SIZE] = "";

    json_t *root;
    json_error_t error;

    strcat(url, URL_FORMAT);
    strcat(url, puuid);
    strcat(url, API_H);
    strcat(url, API);

    char *text = request(&url);

    if(!text)
        return -1;

    root = json_loads(text, 0, &error);

    free(text);

    if(!root){
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return -1;
    }


    if(!json_is_array(root)){
        fprintf(stderr, "error: is not an array\n");
        json_decref(root);
        return -1;
    }

    int taille = json_array_size(root);

    char **tmp = (char**)realloc(*games, taille*sizeof(char*));

    if(tmp == NULL){
        fprintf(stderr, "erreur d'allocation\n");
        free(tmp);
        return -1;
    }


    for (int i = 0; i < taille; i++){
        tmp[i] = (char*)malloc(16);
        if(tmp[i] == NULL){
            fprintf(stderr, "erreur d'allocation\n");
            return -1;
        }
        printf("sizeof tmp[%d] %p: %ld\n",i ,&tmp[i], sizeof(tmp[i]));
        //printf("sizeof *games[%d] %p: %ld\n",i ,games[i], sizeof(*games[i]));
    }

    for(int i=0; i<taille; i++){
        tmp[i] = json_string_value(json_array_get(root, i));
        if(tmp[i] == NULL)
            printf("c'est null\n");
        printf("%s\n", (tmp[i]));
    }

    *games = tmp;

    json_decref(root);

    return taille;
}