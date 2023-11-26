/**
\file locomotivebehavior.h
\author Eva Ray, Benoit Delay
\date 26.11.2023


Ce fichier contient la définition de la classe locomotivebehavior, qui permet de
défnir le comportement d'une locomotive dans la simulation.
*/

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "synchrointerface.h"
#include "route.h"

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SynchroInterface> sharedSection, Route parcours) : loco(loco), sharedSection(sharedSection), parcours(parcours){
    }

protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;


    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SynchroInterface> sharedSection;

    /**
     * @brief parcours Informations sur le parcours que suit la locomotive
     */
    Route parcours;
};

#endif // LOCOMOTIVEBEHAVIOR_H
