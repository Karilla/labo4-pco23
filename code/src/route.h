/**
\file route.h
\author Eva Ray, Benoit Delay
\date 26.11.2023

Ce fichier contient la définition de la classe route, qui définit les caractéristiques d'un parcours
suivi par une locomotive, tels que la position de la gare, du début et de la fin de la section
partagée, ainsi que la position des aiguillages critiques pour le parcours.
*/

#ifndef ROUTE_H
#define ROUTE_H

#include <array>
#include <vector>
#include "ctrain_handler.h"

// Le premier index du tableau est le numéro de l'aiguillage, le second la direction (TOUT_DROIT, DEVIE)
using Aiguillage = std::array<int,2>;

using Contact = unsigned int;

class Route
{
private:
    Contact station;
    // Dernier contact avant la section partagée
    Contact startSharedSection;
    // Premier contact après la section partagée
    Contact endSharedSection;
    // Position de tous les aguillages critiques pour le parcours
    std::vector<Aiguillage> aiguillages;

public:
    Route(int station, int startSharedSection, int endSharedSection, std::vector<Aiguillage> aiguillages);

    /**
     * @brief waitForStation Attend que le contact de la gare soit détecté
     */
    void waitForStation();

    /**
     * @brief waitForStartSharedSection Attend que le contact de début de section partagée soit détecté
     */
    void waitForStartSharedSection();

    /**
     * @brief waitForEndSharedSection Attend que le contact de fin de section partagée soit détecté
     */
    void waitForEndSharedSection();

    /**
     * @brief adjustAiguillages Tourne les aiguillages selon les informations contenues dans l'attribut "aiguillages"
     */
    void adjustAiguillages();
};



#endif // ROUTE_H
