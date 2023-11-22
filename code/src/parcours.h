#ifndef PARCOURS_H
#define PARCOURS_H

#include <array>

class Parcours
{
private:
    int gare;
    int startSharedSection;
    int endSharedSection;
    std::array<int,2> accessAiguillage;
    std::array<int,2> leaveAiguillage;
public:
    Parcours(int gare, int startSharedSection, int endSharedSection, int accessContact, int accessDirection, int leaveContact, int leaveDirection);
};



#endif // PARCOURS_H
