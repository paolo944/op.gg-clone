#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <curl/curl.h>

#define URL_FORMAT   "https://euw1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"
#define URL_SIZE     256
#define API          "?api_key=RGAPI-60599a0b-5450-4b71-8e5a-09af3b36eb40"

int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *text;
    char url[URL_SIZE];

    json_t *root;
    json_error_t error;

    strcat(url, URL_FORMAT);
    strcat(url, argv[1]);
    strcat(url, API);

    printf("%s\n", url);

    //Curl:

    CURL *curl_handle;
    CURLcode res;
 
    struct MemoryStruct chunk;
 
    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */
 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* init the curl session */
    curl_handle = curl_easy_init();
 
    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.example.com/");
 
    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* some servers do not like requests that are made without a user-agent
    field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    /* get it! */
    res = curl_easy_perform(curl_handle);
 
    /* check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
        return 1;
    }
    else {
        if(!text)
            return 1;

        root = json_loads(text, 0, &error);
        free(text);

    if(!root){
           fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return 1;
        }

        if(!json_is_array(root)){
            fprintf(stderr, "error: root is not an array\n");
            json_decref(root);
            return 1;
        }

        json_t *id, *account_id, *puuid, *name, *profileIconId, *revisionDate, *summonerLevel;

        if(!json_is_object(root)){
            fprintf(stderr, "error: is not an object\n");
            json_decref(root);
            return 1;
        }

        id = json_object_get(root, "id");
        if(!json_is_string(id)){
            fprintf(stderr, "error: id is not a string\n");
            json_decref(root);
            return 1;
        }

        account_id = json_object_get(account_id, "commit");
        if(!json_is_object(account_id)){
            fprintf(stderr, "error: account_id is not an object\n");
            json_decref(root);
            return 1;
        }

        puuid = json_object_get(root, "puuid");
        if(!json_is_string(puuid)){
            fprintf(stderr, "error: puuid is not a string\n");
            json_decref(root);
            return 1;
        }

        name = json_object_get(root, "name");
        if(!json_is_string(name)){
            fprintf(stderr, "error: name is not a string\n");
            json_decref(root);
            return 1;
        }

        profileIconId = json_object_get(root, "profileIconId");
        if(!json_is_string(profileIconId)){
            fprintf(stderr, "error: profileIconId is not a string\n");
            json_decref(root);
            return 1;
        }

        revisionDate = json_object_get(root, "revisionDate");
        if(!json_is_string(revisionDate)){
            fprintf(stderr, "error: revisionDate is not a string\n");
            json_decref(root);
            return 1;
        }

        summonerLevel = json_object_get(root, "summonerLevel");
        if(!json_is_string(summonerLevel)){
            fprintf(stderr, "error: summonerLevel is not a string\n");
            json_decref(root);
            return 1;
        }

        printf("summoner name: %s\nsummoner level: %s\n", json_string_value(name), json_string_value(summonerLevel));


        json_decref(root);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
 
    /* we are done with libcurl, so clean it up */
    curl_global_cleanup();

    return 0;
}