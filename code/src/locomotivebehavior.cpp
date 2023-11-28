/**
\file locomotivebehavior.cpp
\author Eva Ray, Benoit Delay
\date 26.11.2023


Ce fichier contient l'implémentation de la classe locomotivebehavior, qui permet de
défnir le comportement d'une locomotive dans la simulation.
*/

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

using LocoID = int;


void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Prêt!");

    while(true) {

        route.waitForStation();
        loco.afficherMessage("J'arrive à la gare.");
        sharedSection->stopAtStation(loco);


        route.waitForStartSharedSection();
        loco.afficherMessage(qPrintable(QString("J'arrive en section critique avec la prorité.").arg(loco.priority)));
        sharedSection->access(loco);
        loco.afficherMessage("J'acccède à la section critique.");
        route.adjustAiguillages();

        route.waitForEndSharedSection();
        sharedSection->leave(loco);
        loco.afficherMessage("Je quitte la section critique.");
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}
