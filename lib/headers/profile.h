#ifndef PROFILE_H
#define PROFILE_H

#include <jansson.h>
#include "request.h"
#include "api.h"

#define URL_FORMAT   "https://euw1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"
#define URL_SIZE     256
#define API_H        "?api_key="

char *afficher_profile(const char *nom);

#endif