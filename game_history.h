#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H

#include <jansson.h>
#include "request.h"

#define URL_FORMAT  "https://europe.api.riotgames.com/lol/match/v5/matches/by-puuid/"
#define URL_SIZE     300
#define API          "/ids?start=0&count=20&api_key=RGAPI-f0c5860c-c59b-4b58-b2c0-da4b4a78a553"

int get_game_history(char *puuid, char ***games);

#endif