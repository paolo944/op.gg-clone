#include "profile.h"
#include "game_history.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *puuid = afficher_profile(argv[1]);


    /*games = malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++){
        games[i] = malloc(17 * sizeof(char));
        if(games[i] == NULL){
            for(int j = 0; j <= i; j++){
                free(games[j]);
            }
            free(games);
        }
    }*/

    Games *games = (Games*)malloc(sizeof(Games));
    games->liste = (char**)malloc(sizeof(char*)*20);
    games->taille = 20;

    games = get_game_history(puuid);
    
    for(int i=0; i<20; i++){
        printf("%s\t%p\n", games->liste[i], &(games->liste[i]));
    }

    return 0;
}