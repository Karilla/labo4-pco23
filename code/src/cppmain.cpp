/**  _____   _____ ____    ___   ___ ___  ____
 * |  __ \ / ____/ __ \  |__ \ / _ \__ \|___ \
 * | |__) | |   | |  | |    ) | | | | ) | __) |
 * |  ___/| |   | |  | |   / /| | | |/ / |__ <
 * | |    | |___| |__| |  / /_| |_| / /_ ___) |
 * |_|     \_____\____/  |____|\___/____|____/
 *
 *
\file cppmain.cpp
\author Eva Ray, Benoit Delay
\date 26.11.2023

Ce fichier contient la fonction principale de la simulation. On y définit le parcours de base, la section
partagée, ainsi que le parours de chaque locomotive. On y crée et lance les threads des locomotives.
*/

#include "ctrain_handler.h"

#include "locomotive.h"
#include "locomotivebehavior.h"
#include "synchrointerface.h"
#include "synchro.h"
#include "route.h"
#include <iostream>

// Locomotives :
// Locomotive A
static Locomotive locoA(0 /* Numéro (pour commande trains sur maquette réelle) */, 10 /* Vitesse */);
// Locomotive B
static Locomotive locoB(1 /* Numéro (pour commande trains sur maquette réelle) */, 12 /* Vitesse */);
// Nombre de locomotives
const int NB_LOCO = 2;

//Arret d'urgence
void emergency_stop()
{
    locoA.arreter();
    locoB.arreter();
    // On met la vitesse à 0 pour être sûr que les locomotives ne redémarrent pas
    locoA.fixerVitesse(0);
    locoB.fixerVitesse(0);
    afficher_message("\nSTOP!");
}


//Fonction principale
int cmain()
{
    /************
     * Maquette *
     ************/

    //Choix de la maquette (A ou B)
    selection_maquette(MAQUETTE_A /*MAQUETTE_B*/);

    /**********************************
     * Initialisation des aiguillages *
     **********************************/

    // Initialisation des aiguillages
    diriger_aiguillage(1,  TOUT_DROIT, 0);
    diriger_aiguillage(2,  DEVIE     , 0);
    diriger_aiguillage(3,  DEVIE     , 0);
    diriger_aiguillage(4,  TOUT_DROIT, 0);
    diriger_aiguillage(5,  TOUT_DROIT, 0);
    diriger_aiguillage(6,  TOUT_DROIT, 0);
    diriger_aiguillage(7,  DEVIE,      0);
    diriger_aiguillage(8,  DEVIE     , 0);
    diriger_aiguillage(9,  DEVIE     , 0);
    diriger_aiguillage(10, TOUT_DROIT, 0);
    diriger_aiguillage(11, TOUT_DROIT, 0);
    diriger_aiguillage(12, TOUT_DROIT, 0);
    diriger_aiguillage(13, TOUT_DROIT, 0);
    diriger_aiguillage(14, DEVIE     , 0);
    diriger_aiguillage(15, DEVIE     , 0);
    diriger_aiguillage(16, DEVIE,      0);
    diriger_aiguillage(17, TOUT_DROIT, 0);
    diriger_aiguillage(18, TOUT_DROIT, 0);
    diriger_aiguillage(19, TOUT_DROIT, 0);
    diriger_aiguillage(20, DEVIE     , 0);
    diriger_aiguillage(21, DEVIE     , 0);
    diriger_aiguillage(22, TOUT_DROIT, 0);
    diriger_aiguillage(23, TOUT_DROIT, 0);
    diriger_aiguillage(24, TOUT_DROIT, 0);

    /********************************
     * Position de départ des locos *
     ********************************/

    // Loco 0
    locoA.fixerPosition(31, 1);

    // Loco 1
    locoB.fixerPosition(34, 5);

    /***********
     * Message *
     **********/

    afficher_message("Hit play to start the simulation...");

    /*********************
     * Threads des locos *
     ********************/

    // Création de la section partagée
    std::shared_ptr<SynchroInterface> sharedSection = std::make_shared<Synchro>(NB_LOCO);

    // Création des aiguillages critiques du parcours pour chaque locomotive
    std::vector<Aiguillage> aiguillagesLoco0 = {{15, TOUT_DROIT}, {8, TOUT_DROIT}};
    std::vector<Aiguillage> aiguillagesLoco1 = {{15, DEVIE}, {8, DEVIE}};

    // Création des parcours des locomotives
    Route parcoursLoco0  = Route(29, 28, 10, aiguillagesLoco0);
    Route parcoursLoco1  = Route(33, 32, 14, aiguillagesLoco1);

    // Création du thread pour la loco 0
    std::unique_ptr<Launchable> locoBehaveA = std::make_unique<LocomotiveBehavior>(locoA, sharedSection, parcoursLoco0 /*, autres paramètres ...*/);
    // Création du thread pour la loco 1
    std::unique_ptr<Launchable> locoBehaveB = std::make_unique<LocomotiveBehavior>(locoB, sharedSection, parcoursLoco1 /*, autres paramètres ...*/);

    // Lancement des threads
    afficher_message(qPrintable(QString("Lancement thread loco A (numéro %1)").arg(locoA.numero())));
    locoBehaveA->startThread();
    afficher_message(qPrintable(QString("Lancement thread loco B (numéro %1)").arg(locoB.numero())));
    locoBehaveB->startThread();

    // Attente sur la fin des threads
    locoBehaveA->join();
    locoBehaveB->join();

    //Fin de la simulation
    mettre_maquette_hors_service();

    return EXIT_SUCCESS;
}
