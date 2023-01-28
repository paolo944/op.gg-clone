#include "headers/profile.h"

char *afficher_profile(const char *nom){

    char *text;
    char url[URL_SIZE] = "";

    json_t *root;
    json_error_t error;

    strcat(url, URL_FORMAT);
    strcat(url, nom);
    strcat(url, API_H);
    strcat(url, API);

    //printf("%s\n", url);

    text = request(&url);
    if(!text)
        return NULL;

    root = json_loads(text, 0, &error);
    free(text);

    if(!root){
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return NULL;
    }

    json_t *id, *accountId, *puuid, *name, *profileIconId, *revisionDate, *summonerLevel;

    if(!json_is_object(root)){
        fprintf(stderr, "error: is not an object\n");
        json_decref(root);
        return NULL;
    }

    id = json_object_get(root, "id");
    if(!json_is_string(id)){
        fprintf(stderr, "error: id is not a string\n");
        json_decref(root);
        return NULL;
    }

    accountId = json_object_get(root, "accountId");
    if(!json_is_string(accountId)){
        fprintf(stderr, "error: accountId is not an object\n");
        json_decref(root);
        return NULL;
    }

    puuid = json_object_get(root, "puuid");
    if(!json_is_string(puuid)){
        fprintf(stderr, "error: puuid is not a string\n");
        json_decref(root);
        return NULL;
    }

    name = json_object_get(root, "name");
    if(!json_is_string(name)){
        fprintf(stderr, "error: name is not a string\n");
        json_decref(root);
        return NULL;
    }

    profileIconId = json_object_get(root, "profileIconId");
    if(!json_is_integer(profileIconId)){
        fprintf(stderr, "error: profileIconId is not a integer\n");
        json_decref(root);
        return NULL;
    }

    revisionDate = json_object_get(root, "revisionDate");
    if(!json_is_integer(revisionDate)){
        fprintf(stderr, "error: revisionDate is not a integer\n");
        json_decref(root);
        return NULL;
    }

    summonerLevel = json_object_get(root, "summonerLevel");
    if(!json_is_integer(summonerLevel)){
        fprintf(stderr, "error: summonerLevel is not a integer\n");
        json_decref(root);
        return NULL;
    }

    printf("summoner name: %s\nsummoner level: %lld\n", json_string_value(name), json_integer_value(summonerLevel));
    //printf("puuid: %s\nicone de profil: %lld\n", json_string_value(puuid), json_integer_value(profileIconId));
    // printf("id: %s\naccount id: %s  \n", json_string_value(id), json_string_value(accountId));

    char *puuid_str = (char*)(malloc(sizeof(char)*(strlen(json_string_value(puuid)) + 1)));
    strcpy(puuid_str, json_string_value(puuid));

    json_decref(root);

    return puuid_str;
}