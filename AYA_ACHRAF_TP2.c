#include <stdio.h>
#include <string.h>
#define TAILLE_NOM 30
#define TAILLE_CNE 10
#define MAX_ETUDIANTS 20

struct Etudiant {
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    char cne[TAILLE_CNE];
    float moyenne;
};

struct Etudiant promo[MAX_ETUDIANTS];
int nb_etudiants = 0; // nombre d'etudiants actuellement dans le tableau

// Exercice 1
void saisirEtudiant(struct Etudiant* e){
    printf("Nom: ");
    scanf("%s",e->nom);
    printf("Prenom: ");
    scanf("%s",e->prenom);
    printf("CNE: ");
    scanf("%s",e->cne);
    printf("Moyenne: ");
    scanf("%f",&e->moyenne);
    printf("Fiche etudiant: %s %s (%s) - %.2f\n",e->nom, e->prenom, e->cne, e->moyenne);
}

// Exercice 2
void saisirPromo(struct Etudiant promo[], int *nb){
    int n;
    printf("Combien d'etudiants voulez vous saisir?");
    scanf("%d",&n);
    while (n<0 || n>MAX_ETUDIANTS){
        printf("Nombre invalide. Saisissez un nombre entre 0 et %d : ",MAX_ETUDIANTS);
        scanf("%d", &n);
    }
    *nb = n;
    for (int i=0; i<*nb; i++){
        printf("\n---Etudiant %d---\n", i + 1);
        saisirEtudiant(&promo[i]);
    }
}

void afficherPromo(struct Etudiant promo[], int nb) {
    if (nb == 0){
        printf("La promotion est vide.\n");
        return;
    }
    for (int i = 0; i < nb; i++){
        printf("%d. %s %s (%s) - Moyenne : %.2f\n",i+1,promo[i].nom,promo[i].prenom,promo[i].cne,promo[i].moyenne);
    }
}

// Exercice 3
int insererEtudiant(struct Etudiant promo[], int* nb, int position, struct Etudiant nouveau) {
    int i;
    if (*nb >=MAX_ETUDIANTS) { // le tableau est plein
        return 0; 
    }
    //on decale vers la droite
    for (i=*nb; i>position; i--) {
        promo[i]=promo[i-1];
    }
    //on insere le nouvel etudiant dans une position precise
    promo[position]=nouveau;
    // on incremente le nombre des etudiants
    (*nb)++;
    return 1;
}

// Exercice 4
int supprimerEtudiant(struct Etudiant promo[], int *nb, int position){
    int i;
    if (position<0 || position>=*nb){  // la position n'est pas valide
        return 0;
    }
    //on decale vers la gauche
    for (i=position; i<*nb-1; i++){
        promo[i]=promo[i+1];
    }
    //on decremente
    (*nb)--;
    return 1;
}

// Exercice 5
int main(void) {
    struct Etudiant promo[MAX_ETUDIANTS];
    struct Etudiant nouveau;
    int nb_etudiants =0;
    int choix, position;
    saisirPromo(promo, &nb_etudiants);
    do {
        printf("\n===== MENU =====\n");
        printf("1.Afficher la promotion\n");
        printf("2.Inserer un etudiant\n");
        printf("3.Supprimer un etudiant\n");
        printf("4.Quitter\n");
        printf("Choix: ");
        if (scanf("%d",&choix)!=1) {
            printf("Saisie invalide.\n");
            return 1;
        }
        switch (choix) {
            case 1:
                afficherPromo(promo, nb_etudiants);
                break;
            case 2:
                if (nb_etudiants >= MAX_ETUDIANTS) {
                    printf("La promotion est pleine.\n");
                    break;
                }
                printf("Nouvel etudiant :\n");
                saisirEtudiant(&nouveau);
                printf("Position d'insertion (0 a %d) : ",nb_etudiants);
                if (scanf("%d", &position)!=1) {
                    printf("Saisie invalide.\n");
                    return 1;
                }
                if (position<0 || position>nb_etudiants) {
                    printf("Position invalide.\n");
                    break;
                }
                if (insererEtudiant(promo, &nb_etudiants, position, nouveau)) {
                    printf("Insertion reussie.\n");
                    afficherPromo(promo, nb_etudiants);
                }
                break;
            case 3:
                if (nb_etudiants==0) {
                    printf("La promotion est vide.\n");
                    break;
                }
                afficherPromo(promo, nb_etudiants);
                printf("Position de suppression (0 a %d) : ",nb_etudiants - 1);
                if (scanf("%d", &position)!=1) {
                    printf("Saisie invalide.\n");
                    return 1;
                }
                if (supprimerEtudiant(promo, &nb_etudiants, position)) {
                    printf("Suppression reussie.\n");
                    afficherPromo(promo, nb_etudiants);
                } else {
                    printf("Position invalide.\n");
                }
                break;
            case 4:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.Choisissez entre 1 et 4.\n");
        }
    } while (choix!= 4);
    return 0;
}