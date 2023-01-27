#ifndef STATS_H
#define STATS_H

#include <time.h>
#include "request.h"
#include "game_history.h"

#define URL         "https://europe.api.riotgames.com/lol/match/v5/matches/"
#define API_H       "?api_key="
#define URL_SIZE    80

typedef struct stats{
    float kda;
    int win;
    char *champion;
    struct tm *timeInfos;
    struct stats *suivant;
} Stats;

Stats *get_stats_games(Games *games);

Stats *get_stat_game(char *game);

#endif