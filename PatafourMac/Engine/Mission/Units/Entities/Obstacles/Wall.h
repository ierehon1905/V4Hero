#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "../../../../Config.h"
#include "../../Entity.h"

using namespace std;

class Wall : public Entity
{
    public:

    Wall();
    void LoadConfig(Config *thisConfigs);
    void Draw(sf::RenderWindow& window);
    void OnCollide(CollidableObject otherObject);
};

#endif // WALL_H
