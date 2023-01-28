#include "headers/stats.h"

Stats **get_stats_games(Games *games, char *puuid){
    Stats **liste = get_stat_game(games->liste[0], puuid);
    //(*liste)->gameId = games->liste[0];
    Stats *stats = NULL;
    for(int i = 1; i < games->taille; i++){
        stats = get_stat_game(games->liste[i], puuid);
        stats->gameId = games->liste[i];
        stats->suivant = *liste;
        *liste = stats;
    }
    return liste;
}

Stats *get_stat_game(char *game, char*puuid){

    Stats *stats = (Stats*)malloc(sizeof(Stats));
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

    json_t *info, *gameCreation, *participants, *id, *puuid_search, *summonerName, *kda, *challenges, *championName, *teams, *team, *win;

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
        fprintf(stderr, "error: gameCreation is not an integer\n");
        json_decref(root);
        json_decref(info);
        return NULL;
    }

    time_t creation_time = json_integer_value(gameCreation);
    time_t rawtime = creation_time;
    struct tm *ts;
    char buffer[80];

    stats->timeInfos = (char*)malloc(sizeof(char)*80);
    if(stats->timeInfos == NULL){
        fprintf(stderr, "erreur d'allocation de buf\n");
        free(stats->timeInfos);
    }

    ts = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "le %d/%m/%Y à %H:%M:%S", ts);
    strcpy(stats->timeInfos, buffer);

    participants = json_object_get(info, "participants");
    if(!json_is_array(participants)){
        fprintf(stderr, "error: participants is not an array\n");
        json_decref(root);
        json_decref(info);
        return NULL;
    }

    //finding summoner's number:

    size_t index;

    json_array_foreach(participants, index, id){
        if(!json_is_object(id)){
            fprintf(stderr, "error: id is not an object\n");
            json_decref(root);
            json_decref(info);
            json_decref(participants);
            return NULL;
        }

        puuid_search = json_object_get(id, "puuid");

        if(!json_is_string(puuid_search)){
            fprintf(stderr, "error: puuid_search is not a string\n");
            json_decref(root);
            json_decref(info);
            json_decref(participants);
            json_decref(id);
            return NULL;
        }

        if(strcmp(puuid, json_string_value(puuid_search)) == 0){
            break;
        }
    }

    summonerName = json_object_get(id, "summonerName");

    if(!json_is_string(summonerName)){
        fprintf(stderr, "error: summonerName is not a string\n");
        json_decref(root);
        json_decref(info);
        json_decref(participants);
        json_decref(id);
        return NULL;
    }

    challenges = json_object_get(id, "challenges");

    if(challenges != NULL){
        if(!json_is_object(challenges)){
            fprintf(stderr, "error: challenges is not an object\n");
            json_decref(root);
            json_decref(info);
            json_decref(participants);
            json_decref(id);
            return NULL;
        }

        kda = json_object_get(challenges, "kda");

        if(!json_is_real(kda)){
            if(!json_is_integer(kda)){
                fprintf(stderr, "error: kda is not a real\n");
                json_decref(root);
                json_decref(info);
                json_decref(participants);
                json_decref(id);
                return NULL;
            }
            else
                stats->kda = json_integer_value(kda);
        }
        else
            stats->kda = json_real_value(kda);
    }
    else
        stats->kda = -1;

    json_decref(challenges);

    championName = json_object_get(id, "championName");

    if(!json_is_string(championName)){
        fprintf(stderr, "error: championName is not a string\n");
        json_decref(root);
        json_decref(info);
        json_decref(participants);
        json_decref(id);
        return NULL;
    }

    stats->champion = json_string_value(championName);

    teams = json_object_get(info, "teams");

    if(!json_is_array(teams)){
        fprintf(stderr, "error: teams is not an array\n");
        json_decref(root);
        json_decref(info);
        return NULL;
    }

    if(index<6)
        team = json_array_get(teams, 0);
    else
        team = json_array_get(teams, 1);

    if(!json_is_object(team)){
        fprintf(stderr, "error: team is not an object\n");
        json_decref(root);
        json_decref(info);
        json_decref(teams);
        return NULL;
    }

    win = json_object_get(team, "win");

    if(!json_is_boolean(win)){
        fprintf(stderr, "error: win is not a boolean\n");
        json_decref(root);
        json_decref(info);
        json_decref(teams);
        json_decref(team);
        return NULL;
    }

    stats->win = json_boolean_value(win);

    json_decref(root);

    return stats;
}