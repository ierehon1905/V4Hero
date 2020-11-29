#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "../Config.h"
#include "../Graphics/PSprite.h"
class Background
{
    public:
    Camera camera;

    sf::VertexArray v_background;
    std::vector<sf::Vector2f> vx_pos;
    std::vector<sf::Color> vx_color;

    Config *thisConfig;
    std::vector<sf::Texture> t_background;
    std::vector<PSprite> s_background;
    std::vector<sf::Vector2f> p_background;
    std::vector<float> background_xspeed;
    std::vector<float> background_y;
    sf::RectangleShape r_ground;

    float temp_camerax = 0;
    float floor_height = 0;
    int quality = 0;

    Background();
    void setCamera(Camera camera);
    void Load(std::string bg_name,Config &thisConfigs);
    void Draw(sf::RenderWindow& window);
};

#endif // BACKGROUND_H
