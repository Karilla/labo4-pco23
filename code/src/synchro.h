/*  _____   _____ ____    ___   ___ ___  ____
 * |  __ \ / ____/ __ \  |__ \ / _ \__ \|___ \
 * | |__) | |   | |  | |    ) | | | | ) | __) |
 * |  ___/| |   | |  | |   / /| | | |/ / |__ <
 * | |    | |___| |__| |  / /_| |_| / /_ ___) |
 * |_|     \_____\____/  |____|\___/____|____/
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
    Synchro() {
        this->compteurLoco = 0;
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée
     *
     * Elle doit arrêter la locomotive et mettre son thread en attente si nécessaire.
     *
     * @param loco La locomotive qui essaie accéder à la section partagée
     */
    void access(Locomotive &loco) override {
      loco.afficherMessage(qPrintable(QString("Ma priorité est de %1 .").arg(loco.priority)));
        // TODO

        mutex.acquire();
        if(loco.priority){
            mutex.release();
          }
        else{
            mutex.release();
            loco.arreter();
            loco.afficherMessage("J'attends de pouvoir accéder à la section critique.");
            waiting.acquire();
            mutex.acquire();
            loco.demarrer();
            mutex.release();
          }

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section partagée
     *
     * Réveille les threads des locomotives potentiellement en attente.
     *
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        // TODO

      if(loco.priority){
          waiting.release();
        }
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

    /**
     * @brief stopAtStation Méthode à appeler quand la locomotive doit attendre à la gare
     *
     * Implémentez toute la logique que vous avez besoin pour que les locomotives
     * s'attendent correctement.
     *
     * @param loco La locomotive qui doit attendre à la gare
     */
    void stopAtStation(Locomotive& loco) override {

        loco.arreter();
        mutex.acquire();
        compteurLoco++;
        if(compteurLoco >= 2){
            loco.priority = 1;
            gare.release();
            compteurLoco = 0;
            mutex.release();
        }
        else{
            loco.priority = 0;
            mutex.release();
            gare.acquire();
        }
        PcoThread::thisThread()->usleep(5000000);
        loco.demarrer();
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 arrives at the station.").arg(loco.numero())));
    }

    /* A vous d'ajouter ce qu'il vous faut */

private:
    PcoSemaphore waiting{0};
    PcoSemaphore mutex{1};
    PcoSemaphore gare{0};

    // Méthodes privées ...
    // Attribut privés ...
    int compteurLoco;

};


#endif // SYNCHRO_H
