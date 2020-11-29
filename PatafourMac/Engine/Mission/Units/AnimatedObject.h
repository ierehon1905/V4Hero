#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <SFML/Graphics.hpp>
#include "../../Config.h"
#include "../../P4A.h"
#include "Object.h"
#include "Hitbox.h"

using namespace std;

class AnimatedObject
{
    public:
    int ao_version = 0;

    vector<Object> objects;
    vector<Hitbox> hitboxes;
    float max_time = 0;
    float cur_pos = 0;

    string anim_path = ""; //identifier

    ///OLD
    sf::Sprite s_wall;
    string current_animation = "";
    float anim_begin = 0;
    float anim_end = 0;

    float current_frame = 0;
    ///THIS IS FOR GLOBAL MOVEMENT, like an arrow in Patapon 3 Multiplayer, that decides your "main" point on the map/whatever
    float global_x = 0;
    float global_y = 0;
    ///THIS IS FOR LOCAL MOVEMENT, basically if you want to keep the original global position, but you want to slightly go off that (like Patapons coming closer to an opponent)
    float local_x = 0;
    float local_y = 0;

    float fps = 60;
    float width = 0;
    float scaleX = 1, scaleY = 1; ///TEMPORARY
    float rotation = 0;

    float animation_framerate = 30;

    sf::Color color = sf::Color(255,255,255,255);

    float framerate = 1;
    sf::Rect<float> hitBox;

    bool ready_to_erase = false;

    ///temporary
    bool worm_fever = false;

    bool loopable = true;

    bool offbounds = false;

    bool manual_spritesheet = false;

    map<string,vector<sf::Texture>> animation_textures;

    vector<float> animation_begin;
    vector<float> animation_end;
    vector<string> animation_names;
    vector<string> animation_goto;
    vector<bool> animation_loop;

    ///for getSegmentIndex
    map<string, int> animation_index;

    ///for new spritesheet implementation
    struct Animation
    {
        string name;
        sf::Image spritesheet; ///data
    };

    struct AnimationFrameBound
    {
        sf::Image image;
        sf::IntRect rect;
        sf::Vector2f origin;
    };

    vector<vector<vector<Object::Pixel>>> all_swaps;

    float xBound=0, yBound=0;

    map<int, map<int, sf::IntRect>> animation_bounds;
    map<int, map<int, sf::Vector2f>> animation_origins;

    vector<Animation> animation_spritesheet;

    map<int, map<int, AnimationFrameBound>> afb;

    bool manual_mode = false;

    int curFrame, lastFrame, index;
    bool force_origin_null = false;

    sf::Vector2f spear_origin;
    sf::Vector2f helm_origin;

    vector<int> animation_frames;
    Config *thisConfig;
    AnimatedObject();
    void loadAnim(std::string data, P4A handle);
    int getSegmentIndex(std::string segment_name);
    void setAnimationSegment(std::string new_segment_name);
    void setAnimationSegment(std::string new_segment_name, bool force_start);
    std::string getAnimationSegment();
    float getAnimationLength(std::string segment_name);
    float getAnimationPos();
    void setGlobalPosition(sf::Vector2f pos);
    sf::Vector2f getGlobalPosition();
    void moveGlobalPosition(sf::Vector2f pos);
    void setLoop(bool loop);
    void setColor(sf::Color new_color);
    sf::Color getColor();
    virtual void LoadConfig(Config *thisConfigs,std::string unitParamPath);
    void applySpear(int id);
    void applyHelm(int id);
    virtual void Draw(sf::RenderWindow& window);
};

#endif // ANIMATEDOBJECT_H
