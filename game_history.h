#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H

#include <jansson.h>
#include "request.h"

#define URL_FORMAT  "https://europe.api.riotgames.com/lol/match/v5/matches/by-puuid/"
#define URL_SIZE     300
#define API          "/ids?start=0&count=20&api_key=RGAPI-60599a0b-5450-4b71-8e5a-09af3b36eb40"

int get_game_history(char *puuid, char ***games);

#endif