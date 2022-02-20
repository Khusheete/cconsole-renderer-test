/*
 * Collection de macros et de petites fonctions faites
 * pour embellir le programme des autres fichiers
*/

//TODO refactor to fit in the library
//eg. have a second terminal opened for the program ?

#ifndef CONSTS_H
#define CONSTS_H


#include <stdlib.h>
#include <stdio.h>


//quelques CSI pour mettre des couleurs et des variations dans la console
#define RED "\x1b[38;2;255;0;0m"
#define GREEN "\x1b[38;2;0;255;0m"
#define BLUE "\x1b[38;2;0;0;255m"
#define YELLOW "\x1b[38;2;255;255;0m"
#define CYAN "\x1b[38;2;0;255;255m"
#define MAGENTA "\x1b[38;2;255;0;255m"

#define BOLD "\x1b[1m"
#define FAINT "\x1b[2m"
#define ITALICS "\x1b[3m"
#define UNDERLINE "\x1b[4m"

#define CLEAR "\x1b[m"
#define RESET_INTENSITY "\x1b[22m"


//quelques constantes
#define PI 3.141592654

//pour afficher des tableaux
#define PRINT_TAB(type, tab, size) printf("["); \
for (int i = 0; i < size; i++) {                \
    printf(type, tab[i]);                       \
    if (i + 1 < size) printf(", ");             \
}                                               \
printf("]\r\n")


//pour afficher des booléens
#define BOOL(x) (x)? "true" : "false"


//petite macro pour rapidament écrire des vérification
#define VERIFY(x, prefix, str...)                       \
if (x)                                                  \
    printf("%s%s%s ", GREEN, prefix, CLEAR);            \
else                                                    \
    printf("%s%s%s ", RED, prefix, CLEAR);              \
printf(str);                                            \
printf("\r\n")


//affiche le titre d'une section
#define TITLE(title...) printf("\r\n%s ===== ", BOLD); printf(title); printf(" ===== %s\r\n\r\n", CLEAR)


//pour des erreurs un peu plus sympa que des asserts
#define FATAL_ERROR(cond, error...)                                         \
if (cond) {                                                                 \
    printf("%s[Fatal Error %s:%i]%s ", RED, __FILE__, __LINE__, CLEAR);     \
    printf(error);                                                          \
    printf("\r\n");                                                         \
    exit(EXIT_FAILURE);                                                     \
}


#define WARNING(cond, error...)                                             \
if (cond) {                                                                 \
    printf("%s[Warning %s:%i]%s ", YELLOW, __FILE__, __LINE__, CLEAR);      \
    printf(error);                                                          \
    printf("\r\n");                                                         \
}


#endif //#ifndef CONSTS_H