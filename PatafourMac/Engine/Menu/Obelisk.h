#ifndef OBELISK_H
#define OBELISK_H
#include <SFML/Graphics.hpp>
#include "../Config.h"
#include "../Graphics/Menu.h"
#include "../Graphics/PText.h"
#include "../Dialog/ControlTips.h"

class V4Core;
class PatapolisMenu;
class ObeliskMenu : public Menu
{
    public:
        sf::Font font;
        int quality=1;

        ControlTips ctrlTips;

        ///worldmap contents
        vector<PSprite> location_bgs;
        vector<PSprite> location_icons;
        vector<PSprite> mission_icons;
        vector<PSprite> worldmap_icons;
        vector<PSprite> worldmap_fields;
        PSprite location_bg_a, location_bg_b;
        PSprite dullpon;

        ///boxes
        PSprite mainbox,descbox,iconbox,missionbox;
        PSprite missionselect;

        ///text
        PText worldmap_title;
        PText location_title;
        PText location_desc;
        PText select_quest;
        PText mission_title;
        PText mission_desc;

        int cur_location = 0;
        float mainbox_destX=640,mainbox_destY=360;
        float alphaA = 0;
        float alphaB = 255;
        float location_bg_a_destAlpha = 0;
        float location_bg_b_destAlpha = 255;

        bool displayMissions = false;
        bool runonce = false;

        PSprite unavailable;
        PSprite location_highlight;
        PSprite mission_select;

        int sel_location = 1;
        int sel_mission = 0;

        vector<int> unlocked = {0};
        vector<int> missions_unlocked = {1,2,3,6};

        int field_unlocked = 1;

        struct Mission
        {
            PText p_mis;
            int mis_ID=0; ///mission ID
            int loc_ID=0; ///location ID
            std::wstring title;
            std::wstring desc;
            std::string mission_file;
        };

        vector<Mission> missions; ///Missions returned for a specific location

        sf::Texture test_tex;
        sf::Sprite test_spr;

        float mapX = 0;
        float mapXdest = 0;

        sf::View v_render_map;
        sf::View v_render_missions_map;

        PatapolisMenu *parentMenu;

        void addMission(string missiondata);
        void Initialise(Config *thisConfig, V4Core *parent,PatapolisMenu *curParentMenu);
        void Reload();
        void Update(sf::RenderWindow &window, float fps, InputController& inputCtrl);
        void EventFired(sf::Event event);
        void OnExit();
        void UpdateButtons();
        ObeliskMenu();
        ~ObeliskMenu();



};


#endif // OBELISK_H
