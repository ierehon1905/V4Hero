#ifndef KIRAJINPOWEREDTOWERBIG_H
#define KIRAJINPOWEREDTOWERBIG_H

#include <SFML/Graphics.hpp>
#include "../../../../Config.h"
#include "../../Entity.h"

using namespace std;

class KirajinPoweredTowerBig : public Entity
{
    public:
    bool droppeditem = false;
    float shake = 0;
    bool negative = false;
    sf::Clock death_timer;
    sf::Clock shake_timer;
    float shake_delay = 80;

    sf::SoundBuffer s_broken;

    KirajinPoweredTowerBig();
    void LoadConfig(Config *thisConfigs);
    void parseAdditionalData(std::vector<std::string> additional_data);
    void Draw(sf::RenderWindow& window);
    void OnCollide(CollidableObject* otherObject, int collidedWith=-1, vector<string> collisionData = {});
};

#endif // KIRAJINPOWEREDTOWERBIG_H
