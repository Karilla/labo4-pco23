#include "parcours.h"

Parcours::Parcours(int gare, int startSharedSection, int endSharedSection, int accessContact, int accessDirection, int leaveContact, int leaveDirection)
    : gare(gare), startSharedSection(startSharedSection), endSharedSection(endSharedSection)
{
    accessAiguillage[0] = accessContact;
    accessAiguillage[1] = accessDirection;
    leaveAiguillage[0] = leaveContact;
    leaveAiguillage[1] = leaveDirection;
}
