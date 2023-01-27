#include "lib/headers/profile.h"
#include "lib/headers/game_history.h"
#include "lib/headers/stats.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *puuid = afficher_profile(argv[1]);

    Games *games = get_game_history(puuid);
    
    for(int i=0; i<games->taille; i++){
        printf("%s\n", games->liste[i]);
    }

    get_stats_games(games);

    for(int i=0; i<games->taille; i++){
        free(games->liste[i]);
    }
    free(games->liste);
    free(games);
    free(puuid);

    return 0;
}