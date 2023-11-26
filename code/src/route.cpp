/**
\file route.cpp
\author Eva Ray, Benoit Delay
\date 26.11.2023

Ce fichier contient l'implémentation de la classe route, qui définit les caractéristiques d'un parcours
suivi par une locomotive, tels que la position de la gare, du début et de la fin de la section
partagée, ainsi que la position des aiguillages critiques pour le parcours.
*/

#include "route.h"

Route::Route(int station, int startSharedSection, int endSharedSection, std::vector<Aiguillage> aiguillages)
    : station(station), startSharedSection(startSharedSection), endSharedSection(endSharedSection),
      aiguillages(aiguillages){}

void Route::waitForStation(){

    attendre_contact(station);
}

void Route::waitForStartSharedSection(){

    attendre_contact(startSharedSection);
}

void Route::waitForEndSharedSection(){

    attendre_contact(endSharedSection);
}

void Route::adjustAiguillages(){

    for(Aiguillage aiguillage : aiguillages){
        diriger_aiguillage(aiguillage[0], aiguillage[1], 0);
    }
}
