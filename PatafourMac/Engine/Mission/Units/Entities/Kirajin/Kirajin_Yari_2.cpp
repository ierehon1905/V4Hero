#include "Kirajin_Yari_2.h"
#include "math.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../../../Func.h"
#include "../../../../V4Core.h"

Kirajin_Yari_2::Kirajin_Yari_2()
{
    /// Kirajin that normally hides in the bushes ready to ambush the Patapons
    /// Full AI required including changing layers when Patapons are nearby.
}

void Kirajin_Yari_2::LoadConfig(Config *thisConfigs)
{
    /// all (normal) kacheeks have the same animations, so we load them from a hardcoded file
    AnimatedObject::LoadConfig(thisConfigs,"resources\\units\\entity\\kirajin.p4a");
    AnimatedObject::setAnimationSegment("idle_armed_focused");
}

void Kirajin_Yari_2::parseAdditionalData(std::vector<std::string> additional_data)
{
    action = IDLE;
    swap_layer = 0;
    talk = false;
    talk_id = "";
    custom_dmg = false;
    view_range = 750;

    for(int i=0; i<additional_data.size(); i++)
    {
        if(additional_data[i].find("hidden") != std::string::npos)
        {
            action = HIDING;
            string a = additional_data[i].substr(additional_data[i].find_first_of(":")+1);
            swap_layer = stoi(a);
        }
        else if(additional_data[i].find("talk") != std::string::npos)
        {
            talk_id = additional_data[i].substr(additional_data[i].find_first_of(":")+1);
            talk = true;
        }
        else if(additional_data[i].find("equip") != std::string::npos)
        {
            vector<string> eq = Func::Split(additional_data[i], ':');

            applySpear(stoi(eq[1]));
            applyHelm(stoi(eq[2]));
        }
        else if(additional_data[i].find("damage") != std::string::npos)
        {
            vector<string> eq = Func::Split(additional_data[i], ':');

            mindmg = stoi(eq[1]);
            maxdmg = stoi(eq[2]);

            custom_dmg = true;
        }
        else if(additional_data[i].find("range") != std::string::npos)
        {
            vector<string> eq = Func::Split(additional_data[i], ':');

            view_range = stoi(eq[1]);
        }
        else if(additional_data[i].find("forceSpawnOnLvl") != std::string::npos)
        {
            vector<string> eq = Func::Split(additional_data[i], ':');

            force_spawn = true;
            force_spawn_lvl = stoi(eq[1]);
        }
        else if(additional_data[i].find("forceDropIfNotObtained") != std::string::npos)
        {
            vector<string> eq = Func::Split(additional_data[i], ':');

            force_drop = true;
            force_drop_item = stoi(eq[1]);

            if(eq[2] != "any")
            force_drop_mission_lvl = 0;
        }
    }
}

bool Kirajin_Yari_2::doAttack()
{
    if(action == ATTACK)
    {
        if(enemy_in_range)
        {
            if(attackmode == -2) ///prepare the attack (move around)
            {
                ///To-do: distance from Patapon
                attackmode = -1;
            }

            if(attackmode == -1) ///start the attack
            {
                attack_clock.restart();
                attackmode = 0;

                vspeed = -683;
            }

            if(attackmode == 0) ///begin the attack
            {
                canThrow = true;

                if(AnimatedObject::getAnimationSegment() != "attack_fever_start")
                AnimatedObject::setAnimationSegment("attack_fever_start", true);

                if(attack_clock.getElapsedTime().asMilliseconds() > 500)
                {
                    AnimatedObject::setAnimationSegment("attack_fever_throw", true);
                    attack_clock.restart();
                    attackmode = 1;
                }
            }

            if(attackmode == 1) ///attack continously
            {
                if(getAnimationPos() > 0.28)
                {
                    if(canThrow)
                    {
                        threw = true;
                        canThrow = false;
                    }
                }

                if(attack_clock.getElapsedTime().asSeconds() > attack_speed)
                {
                    if(canThrow)
                    {
                        if(threw == false)
                        threw = true;
                    }

                    AnimatedObject::setAnimationSegment("attack_fever_throw", true);
                    attack_clock.restart();

                    canThrow = true;
                }

                if(local_y >= 0)
                {
                    AnimatedObject::setAnimationSegment("idle_armed_focused", true);
                    attackmode = 2;
                }
            }
        }
        else
        {
            action = IDLE;
        }

        if(attackmode == 2)
        {
            canThrow = true;
            action = IDLE;
            attack_timer.restart();
        }
    }
    else
    {
        attackmode = -1;
    }

    if(threw)
    {
        threw = false;
        return true;
    }
    else
    {
        return false;
    }
}

void Kirajin_Yari_2::doMessages(sf::RenderWindow& window, float fps, InputController& inputCtrl)
{
    vector<int> m_rm;

    for(int i=0; i<messageclouds.size(); i++)
    {
        messageclouds[i].startpos = sf::Vector2f(getGlobalPosition().x-5, getGlobalPosition().y-25);

        if(messageclouds[i].firstrender)
        messageclouds[i].Show();

        if(message_clock.getElapsedTime().asSeconds() >= 5)
        messageclouds[i].End();

        if((messageclouds[i].done) && (floor(messageclouds[i].xsize) == 0) && (floor(messageclouds[i].ysize) == 0))
        messageclouds[i].Hide();

        messageclouds[i].Draw(window, fps, inputCtrl);

        if((!messageclouds[i].active) && (messageclouds[i].done))
        m_rm.push_back(i);
    }

    for(int i=0; i<m_rm.size(); i++)
    {
        messageclouds.erase(messageclouds.begin()+m_rm[i]-i);
    }
}

void Kirajin_Yari_2::Draw(sf::RenderWindow& window)
{
    //cout << "Kirajin_Yari_2: " << action << " " << getAnimationSegment() << " " << cur_pos << " " << attackmode << " " << attack_timer.getElapsedTime().asSeconds() << " " << walk_clock.getElapsedTime().asSeconds() << " " << distance_to_unit << endl;

    if(dead)
    {
        cout << "I'm dead now" << endl;

        if(getAnimationSegment() == "stagger")
        {
            cout << "Animation segment is stagger " << cur_pos << " " << anim_end << endl;

            if(cur_pos >= anim_end)
            {
                cout << "Setting death animation" << endl;

                setAnimationSegment("death", true);
            }
        }

        if(death_timer.getElapsedTime().asSeconds() > 5)
        {
            cout << "Death clock passed 3 seconds. Time to bury into the ground" << endl;

            if(getAnimationSegment() == "death")
            {
                cout << "I am despawning" << endl;
                setAnimationSegment("death_despawn", true);

                dropItem();
            }

            if(getAnimationSegment() == "death_despawn")
            {
                if(cur_pos >= anim_end)
                {
                    ready_to_erase = true;
                }
            }
        }
    }
    else
    {
        ///Not dead
        if(action == IDLE)
        {
            if(walk_clock.getElapsedTime().asSeconds() > 4)
            {
                if(enemy_in_range)
                {
                    if((distance_to_unit > 370) || (distance_to_unit < 520))
                    {
                        if(jumped == false)
                        {
                            action = WALK;
                            dest_distance = 370 + (rand() % 150);

                            walk_clock.restart();
                        }
                    }
                }
            }

            if(action != WALK)
            {
                if(getAnimationSegment() == "stagger")
                {
                    if(cur_pos >= anim_end)
                    {
                        setAnimationSegment("idle_armed_focused", true);
                    }
                }

                if(getAnimationSegment() == "walk_yari_focused")
                {
                    if(jumped)
                    {
                        if(local_y >= 0)
                        {
                            setAnimationSegment("idle_armed_focused", true);
                            jumped = false;
                        }
                    }
                    else
                    {
                        setAnimationSegment("idle_armed_focused", true);
                    }
                }

                attackmode = -1;

                if(attack_timer.getElapsedTime().asSeconds() >= 4)
                {
                    action = ATTACK;
                    attack_timer.restart();
                }
            }
        }
        else if(action == HIDING)
        {
            if(distance_to_unit <= view_range)
            {
                layer = swap_layer;
                hspeed = 200;
                vspeed = -420;

                jumped = true;

                setAnimationSegment("walk_yari_focused", true);

                action = IDLE;
                attack_timer.restart();
            }
        }
        else if(action == WALK)
        {
            if(enemy_in_range)
            {
                if((distance_to_unit >= dest_distance-5) && (distance_to_unit <= dest_distance+5))
                action = IDLE;

                if(getAnimationSegment() != "walk_yari_focused")
                {
                    setAnimationSegment("walk_yari_focused", true);
                }

                if(distance_to_unit >= dest_distance)
                {
                    global_x -= float(150) / fps;
                }

                if(distance_to_unit <= dest_distance)
                {
                    if(getGlobalPosition().x - spawn_x < 1000) ///1000 is max distance an entity can go to the right
                    global_x += float(150) / fps;
                }
            }
            else
            {
                ///return to spawn_x
                dest_distance = spawn_x-getGlobalPosition().x;
            }
        }

        if(enemy_in_range)
        {
            if(action != HIDING)
            {
                if(talk)
                {
                    MessageCloud tmp;
                    tmp.Create(20, sf::Vector2f(getGlobalPosition().x-5, getGlobalPosition().y-25), sf::Color(222,102,102,255), false, thisConfig->GetInt("textureQuality"), thisConfig->fontPath);
                    tmp.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(talk_id)), false);
                    messageclouds.push_back(tmp);

                    message_clock.restart();

                    talk = false;
                }
            }
        }

        if(distance_to_unit <= view_range)
        {
            enemy_in_range = true;
        }
        else
        {
            enemy_in_range = false;
        }
    }

    vspeed += gravity / fps;

    if(hspeed > 0)
    hspeed -= 230.0 / fps;
    else
    hspeed = 0;

    if(vspeed >= 0)
    {
        if(local_y >= 0)
        {
            vspeed = 0;
            local_y = 0;
        }
    }

    local_x += hspeed / fps;
    local_y += vspeed / fps;

    /// call the parent function to draw the animations
    AnimatedObject::Draw(window);
}

void Kirajin_Yari_2::die()
{
    if(!dead)
    {
        //cout << "Kirajin_Yari_2::die()" << endl;

        int a = rand() % 4 + 1;
        string death_id = "kirajin_death_"+to_string(a);

        MessageCloud tmp;
        tmp.Create(20, sf::Vector2f(getGlobalPosition().x-5, getGlobalPosition().y-25), sf::Color(222,102,102,255), false, thisConfig->GetInt("textureQuality"), thisConfig->fontPath);
        tmp.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(death_id)), false);
        messageclouds.push_back(tmp);

        message_clock.restart();

        dead = true;
        hspeed = 340;
        vspeed = -250;

        if(global_y != floorY)
        {
            local_y = global_y - floorY;
            global_y -= local_y;
        }

        isCollidable = false;
        isAttackable = false;

        AnimatedObject::setAnimationSegment("stagger", true);
        death_timer.restart();
    }
}

void Kirajin_Yari_2::OnCollide(CollidableObject* otherObject, int collidedWith, vector<string> collisionData)
{
    cout << "Kirajin_Yari_2::OnCollide" << endl;

    if(AnimatedObject::getAnimationSegment() != "death")
    {
        if(collisionData.size() > 0)
        {
            if(isCollidable)
            {
                if(action == HIDING)
                layer = swap_layer;

                action = IDLE;
                attackmode = -1;

                ///collisionData received from Projectile, process it
                int dmgDealt = atoi(collisionData[0].c_str());
                curHP -= dmgDealt;

                cout << "I received " << to_string(dmgDealt) << "damage, my HP is " << curHP << "/10" << endl;

                hspeed = 120 + (rand() % 50);
                vspeed = -170;

                AnimatedObject::setAnimationSegment("stagger", true);
            }
        }

        if(curHP <= 0)
        {
            die();
        }
    }

    /// note we don't call the parent function. It does nothing, it just serves
    /// as an incomplete function to be overridden by child classes.
}
