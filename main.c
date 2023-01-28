#include "lib/headers/profile.h"
#include "lib/headers/game_history.h"
#include "lib/headers/stats.h"
#include <sys/resource.h>

void PrintMem(){
    struct rusage r;
    getrusage(0, &r);
    printf("ru_maxrss: %ld octets\n", r.ru_maxrss);
    //Question 2.8
    //On constate que la mémoire est effectivement alloué après l'appel de
    //InitTab.
}

int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "nom du joueur manquant\n");
        return 1;
    }

    char *puuid = afficher_profile(argv[1]);

    Games *games = get_game_history(puuid);

    Stats **stats = get_stats_games(games, puuid);

    Stats *buff = *stats;

    printf("taille: %d\n", games->taille);

    int i = games->taille;
    while(buff){
        printf("Game numéro %d id: %s:\nChampion: %s\nkda: %.2f\n", i, buff->gameId, buff->champion, buff->kda);
        printf("La game a été %s", ("gangé"?buff->win:"perdue"));
        buff = buff->suivant;
        i--;
    }

    PrintMem();

    Stats *buff_free;

    for(int i=0; i<games->taille; i++){
        free(games->liste[i]);
        buff = *stats;
        buff_free = buff->suivant;
        free(buff->champion);
        stats = buff_free;
        free(buff);
    }
    free(games->liste);
    free(games);
    free(puuid);

    return 0;
}