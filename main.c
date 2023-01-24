#include "profile.h"
#include "game_history.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *puuid = afficher_profile(argv[1]);

    char **games = NULL;
    int taille = get_game_history(puuid, &games);

    if(games == NULL)
        printf("c'est null\n");

    printf("games number: %d\n", taille);
    
    for(int i=0; i < taille; i++){
        if(games[i] == NULL)
            printf("c'est null\n");
        else
            printf("ici i=%d\n", i);
            printf("game %d: %s\n", i, games[i]);
    }

    return 0;
}