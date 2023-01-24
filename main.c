#include "profile.h"
#include "game_history.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *puuid = afficher_profile(argv[1]);

    const char **games = NULL;
    int taille = get_game_history(puuid, games);

    printf("games number: %d\n", taille);
    
    for(int i=0; i < taille; i++){
        printf("game %d: %s\n", i, games[i]);
    }

    return 0;
}