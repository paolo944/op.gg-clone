#ifndef PROFILE_H
#define PROFILE_H

#include <jansson.h>
#include "request.h"

#define URL_FORMAT   "https://euw1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"
#define URL_SIZE     256
#define API          "?api_key=RGAPI-f0c5860c-c59b-4b58-b2c0-da4b4a78a553"

char *afficher_profile(const char *nom);

#endif