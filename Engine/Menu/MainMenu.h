#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
#include "ButtonLists/MainMenuButtonList.h"
#include "../Config.h"
#include "../Graphics/Menu.h"
#include "../Mission/MissionController.h"
#include "OptionsMenu.h"
#include "Patapolis.h"
#include "../Graphics/PSprite.h"
class V4Core;
class MainMenu : public Menu
{
    public:
        sf::Font f_font;
        PSprite grass_1,grass_2,grass_3,grass_4;
        PSprite logo,logo_shadow;
        PSprite totem[4];
        PSprite fire_1,fire_2,fire_3,aura,sword;
        PSprite sword_1,sword_2;

        std::vector<std::string> temp_menu = {"New game", "Continue", "Options", "Exit"};

        sf::Text t_option[4];

        sf::VertexArray v_background;

        float maxQX, maxQY;
        int fade = 0;
        float alpha = 240;

        float mouseX = 0, mouseY = 0;

        int totem_sel = 0;
        int old_sel = 0;
        float fire = 0;

        float g_x[4], g_dest[4];

        PatapolisMenu patapolisMenu;
        void Initialise(Config *thisConfig, std::map<int,bool> *keymap,V4Core *parent);

        void Update(sf::RenderWindow &window, float fps, std::map<int,bool> *keyMap, std::map<int,bool> *keyMapHeld);
        void EventFired(sf::Event event);
        void OnExit();
        void UpdateButtons();
        MainMenu();
        ~MainMenu();

};


#endif // CAMERA_H
