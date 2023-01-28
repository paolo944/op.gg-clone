#ifndef STATS_H
#define STATS_H

#include <time.h>
#include "request.h"
#include "game_history.h"

#define URL_FORMAT  "https://europe.api.riotgames.com/lol/match/v5/matches/"
#define API_H       "?api_key="
#define URL_SIZE    80

typedef struct stats{
    char *gameId;
    float kda;
    int win;
    char *champion;
    char *timeInfos;
    struct stats *suivant;
} Stats;

Stats **get_stats_games(Games *games, char*puuid);

Stats *get_stat_game(char *game, char*puuid);

#endif