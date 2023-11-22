#include "parcours.h"

Parcours::Parcours(int station, int startSharedSection, int endSharedSection, int accessContact, int accessDirection, int leaveContact, int leaveDirection)
    : station(station), startSharedSection(startSharedSection), endSharedSection(endSharedSection)
{
    accessAiguillage[0] = accessContact;
    accessAiguillage[1] = accessDirection;
    leaveAiguillage[0] = leaveContact;
    leaveAiguillage[1] = leaveDirection;
}

void Parcours::waitForStation(){

    attendre_contact(station);
}

void Parcours::waitForStartSharedSection(){

    attendre_contact(startSharedSection);
}

void Parcours::waitForEndSharedSection(){

    attendre_contact(endSharedSection);
}

void Parcours::adjustAiguillages(){

    diriger_aiguillage(accessAiguillage[0], accessAiguillage[1], 0);
    diriger_aiguillage(leaveAiguillage[0], leaveAiguillage[1], 0);
}
