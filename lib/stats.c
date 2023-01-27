#include "headers/stats.h"

Stats *get_stats_games(Games *games){
    for(int i = 0; i < games->taille; i++){
        get_stat_game(games->liste[i]);
    }

    return NULL;
}

Stats *get_stat_game(char *game){

    Stats *stats = (Stats*)malloc(sizeof(Stats));
    stats->champion = NULL;
    stats->suivant = NULL;

    char url[URL_SIZE] = "";

    json_t *root;
    json_error_t error;

    strcat(url, URL_FORMAT);
    strcat(url, game);
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

    json_t *info, *gameCreation;

    if(!json_is_object(root)){
        fprintf(stderr, "error: is not an object\n");
        json_decref(root);
        return NULL;
    }

    info = json_object_get(root, "info");
    if(!json_is_object(info)){
        fprintf(stderr, "error: info is not an object\n");
        json_decref(root);
        return NULL;
    }

    gameCreation = json_object_get(info, "gameCreation");
    if(!json_is_integer(gameCreation)){
        fprintf(stderr, "error: gameCreation is not a long\n");
        json_decref(root);
        json_decref(info);
        return NULL;
    }

    time_t creation_time = json_integer_value(gameCreation);

    stats->timeInfos = localtime(creation_time);

    printf( "Date and local time : %04d/%02d/%02d %02d:%02d:%02d\n",
        stats->timeInfos->tm_year+1900, stats->timeInfos->tm_mon+1, stats->timeInfos->tm_mday,
        stats->timeInfos->tm_hour, stats->timeInfos->tm_min, stats->timeInfos->tm_sec
    );

    return NULL;
}