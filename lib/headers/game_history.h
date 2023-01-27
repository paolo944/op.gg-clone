#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H

#include <jansson.h>
#include "request.h"
#include "api.h"

#define URL_FORMAT  "https://europe.api.riotgames.com/lol/match/v5/matches/by-puuid/"
#define URL_SIZE     300
#define API_H       "/ids?start=0&count=20&api_key="

typedef struct games{
    char **liste;
    int taille;
} Games;

Games *get_game_history(char *puuid);

#endif