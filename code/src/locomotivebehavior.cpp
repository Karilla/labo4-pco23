/*  _____   _____ ____    ___   ___ ___  ____
 * |  __ \ / ____/ __ \  |__ \ / _ \__ \|___ \
 * | |__) | |   | |  | |    ) | | | | ) | __) |
 * |  ___/| |   | |  | |   / /| | | |/ / |__ <
 * | |    | |___| |__| |  / /_| |_| / /_ ___) |
 * |_|     \_____\____/  |____|\___/____|____/
 */

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

using LocoID = int;

void LocomotiveBehavior::emergency(){
    //sharedSection.setEmergency();
}

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
    //sharedSection->access(loco);
    //sharedSection->leave(loco);
    //sharedSection->stopAtStation(loco);

    while(true) {
        //Section critique 25 22
        // 10 14
        // On attend qu'une locomotive arrive sur le contact 1.
        // Pertinent de faire ça dans les deux threads? Pas sûr...
        //attendre_contact(25);
        if((loco.numero() == 0) ){
            attendre_contact(29);
            sharedSection->stopAtStation(loco);
            attendre_contact(28);
            loco.afficherMessage(qPrintable(QString("J'arrive en section critique avec la prorité.").arg(loco.priority)));
            sharedSection->access(loco);
            attendre_contact(15);
            diriger_aiguillage(8,TOUT_DROIT,0);
            attendre_contact(10);
            sharedSection->leave(loco);
          }
        else{
            attendre_contact(33);
            sharedSection->stopAtStation(loco);
            attendre_contact(32);
            loco.afficherMessage(qPrintable(QString("J'arrive en section critique avec la prorité.").arg(loco.priority)));
            sharedSection->access(loco);
            attendre_contact(15);
            diriger_aiguillage(8,DEVIE,0);
            attendre_contact(14);
            sharedSection->leave(loco);
          }
        loco.afficherMessage("J'ai atteint le contact 1");
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
