/**
\file synchro.h
\author Eva Ray, Benoit Delay
\date 26.11.2023

Ce fichier contient l'implémentation de la classe Synchro qui implémente l'interface
SynchroInterface qui propose les méthodes liées à la section partagée.
*/


#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <QDebug>
#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "synchrointerface.h"

/**
 * @brief La classe Synchro implémente l'interface SynchroInterface qui
 * propose les méthodes liées à la section partagée.
 */
class Synchro final : public SynchroInterface
{
public:

    /**
     * @brief Synchro Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    Synchro(unsigned int nbLocomotives):  waiting(0), station(0), mutex(1), nbLoco(nbLocomotives), nbWaitingStation(0), nbWaitingSharedSec(0) {
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée
     * Elle arrête la locomotive et met son thread en attente si nécessaire.
     * @param loco La locomotive qui essaie accéder à la section partagée
     */
    void access(Locomotive &loco) override {

        loco.afficherMessage(qPrintable(QString("Ma priorité est de %1 .").arg(loco.priority)));

        mutex.acquire();

        if(loco.priority){

            mutex.release();
          }
        else{

            nbWaitingSharedSec++;
            // On relâche le mutex pour ne pas bloquer les autres threads
            mutex.release();
            loco.arreter();
            loco.afficherMessage("J'attends mon tour.");
            waiting.acquire();
            loco.demarrer();
          }

        afficher_message(qPrintable(QString("La locomotive no. %1 accède à la section partagée.").arg(loco.numero())));
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section partagée
     * Réveille les threads des locomotives potentiellement en attente.
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {

      mutex.acquire();

      if(nbWaitingSharedSec > 0){

          waiting.release();
          nbWaitingSharedSec--;
        }

      mutex.release();

      afficher_message(qPrintable(QString("La locomotive no. %1 quitte la section partagée.").arg(loco.numero())));
    }

    /**
     * @brief stopAtStation Méthode à appeler quand la locomotive doit attendre à la gare
     * @param loco La locomotive qui doit attendre à la gare
     */
    void stopAtStation(Locomotive& loco) override {

        loco.arreter();
        mutex.acquire();
        nbWaitingStation++;

        // Si on arrive à  la gare en dernier
        if(nbWaitingStation >= nbLoco){

            loco.priority = 1;
            station.release();
            nbWaitingStation = 0;
            mutex.release();
        }
        else{ // Si on n'arrive pas à la gare en dernier

            loco.priority = 0;
            // On relâche le mutex pour ne pas bloquer les autres threads
            mutex.release();
            station.acquire();
        }

        // On attend 5 secondes
        PcoThread::thisThread()->usleep(5000000);

        loco.demarrer();

        afficher_message(qPrintable(QString("The engine no. %1 arrives at the station.").arg(loco.numero())));
    }

private:

    /**
     * @brief waiting Semaphore pour gérer l'accès à la section critique
     */
    PcoSemaphore waiting;
    /**
     * @brief station Semaphore pour gérer les arrivées en gare
     */
    PcoSemaphore station;
    /**
     * @brief mutex Mutex pour protéger les ressources partagées entre plusieurs threads
     */
    PcoSemaphore mutex;
    /**
     * @brief locoCounter Nombre de locomotives qui attendent à la gare
     */
    unsigned int nbWaitingStation;
    /**
     * @brief locoCounterSharedSec Nombre de locomotives qui attendent l'accès à la section partagée
     */
    unsigned int nbWaitingSharedSec;
    /**
     * @brief nbLoco Nombre de locomotives dans la simulation
     */
    unsigned int nbLoco;
};


#endif // SYNCHRO_H
