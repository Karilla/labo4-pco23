#ifndef PARCOURS_H
#define PARCOURS_H

#include <array>
#include "ctrain_handler.h"

// Le premier index du tableau est le numéro de l'aiguillage, le second la direction (TOUT_DROIT, DEVIE)
using Aiguillage = std::array<int,2>;

using Contact = unsigned int;

class Parcours
{
private:
    Contact station;
    // Dernier contact avant la section partagée
    Contact startSharedSection;
    // Premier contact après la section partagée
    Contact endSharedSection;
    // Aiguillage pour accéder à la section partagée
    Aiguillage accessAiguillage;
    // Aiguillage pour sortir de la section partagée
    Aiguillage leaveAiguillage;

public:
    Parcours(int station, int startSharedSection, int endSharedSection, int accessContact, int accessDirection, int leaveContact, int leaveDirection);

    void waitForStation();

    void waitForStartSharedSection();

    void waitForEndSharedSection();

    void adjustAiguillages();
};



#endif // PARCOURS_H
