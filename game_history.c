#include "game_history.h"

Games *get_game_history(char *puuid){
    char url[URL_SIZE] = "";

    json_t *root;
    json_error_t error;

    strcat(url, URL_FORMAT);
    strcat(url, puuid);
    strcat(url, API_H);
    strcat(url, API);

    char *text = request(&url);

    if(!text)
        return NULL;

    root = json_loads(text, 0, &error);

    free(text);

    if(!root){
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return NULL;
    }


    if(!json_is_array(root)){
        fprintf(stderr, "error: is not an array\n");
        json_decref(root);
        return NULL;
    }

    int taille = json_array_size(root);
    
    for(int i=0; i<taille; i++){
        games->liste[i] = json_string_value(json_array_get(root, i));
        printf("%s\t%p\n", games->liste[i], &(games->liste[i]));
    }

    json_decref(root);

    return;
}