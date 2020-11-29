#include "Entity.h"
#include "../../V4Core.h"

Entity::Entity()
{

}

void Entity::setEntityID(int new_entityID)
{
    entityID = new_entityID;
}

int Entity::getEntityID()
{
    return entityID;
}

void Entity::doRhythm(std::string current_song, std::string current_drum, int combo, int realcombo, bool advanced_prefever, float beatBounce, float satisfaction)
{
    cout << "Entity::doRhythm() was not overriden by child class" << endl;
}

bool Entity::doAttack()
{
    //cout << "Entity::doAttack() was not overriden by child class" << endl;
    return false;
}

void Entity::doMessages(sf::RenderWindow& window, float fps, InputController& inputCtrl)
{
    //cout << "Entity::doMessages() was not overriden by child class" << endl;
}

void Entity::die()
{
    ///Kills the entity, if entity has a method scripted
    ///Made so it can be called outside of the entity function and do the same work
}

void Entity::LoadConfig(Config *thisConfigs, std::string unitParamPath)
{
    cout << "Entity::LoadConfig() was not overriden by child class" << endl;
}

void Entity::parseAdditionalData(std::vector<std::string> additional_data)
{
    cout << "Entity::parseAdditionalData() was not overriden by child class" << endl;
}

void Entity::dropItem()
{
    if(!dropped_item)
    {
        ///Lets say we're dropping following items: 30 spear, 30 helm, 30 mask, 30 item, 120 in total
        int full_rng = 0;

        for(int i=0; i<loot_table.size(); i++)
        {
            full_rng += loot_table[i].item_chance;
        }

        ///Drop item mechanism! Really cool!
        int rng = rand() % full_rng + 1; ///select 1 - 100;
        int total_rng = 0;
        int id_picked = 0;

        cout << "Rng: " << rng << endl;

        for(int i=0; i<loot_table.size(); i++)
        {
            ///total_rng goes to 30, 60, 90, 120 to check for the item drop. should work
            total_rng += loot_table[i].item_chance;

            if(rng <= total_rng)
            {
                id_picked = loot_table[i].item_id;
                cout << "Picked id: " << id_picked << endl;

                break;
            }
        }

        if(force_drop)
        {
            ///check if there are level requirements
            if(force_drop_mission_lvl != 0)
            {
                ///specific mission level is required, compare it
                if(thisConfig->thisCore->savereader.missionLevels[thisConfig->thisCore->currentController.curMissionID] == force_drop_mission_lvl)
                {
                    ///check if the item was obtained, if not, force drop it
                    if(!thisConfig->thisCore->savereader.invdata.CheckItemObtained(force_drop_item))
                    id_picked = force_drop_item;
                }
            }
            else
            {
                ///there are no level requirements, just drop the item if its not obtained yet
                if(!thisConfig->thisCore->savereader.invdata.CheckItemObtained(force_drop_item))
                id_picked = force_drop_item;
            }
        }

        if(id_picked != 0)
        {
            auto item = thisConfig->thisCore->savereader.itemreg.GetItemByID(id_picked);
            vector<string> data = {item->spritesheet, to_string(item->spritesheet_id), to_string(id_picked)};

            thisConfig->thisCore->currentController.spawnEntity("droppeditem",5,0,getGlobalPosition().x+hitboxes[0].o_x+(hitboxes[0].o_width/2),0,getGlobalPosition().y+hitboxes[0].o_y+(hitboxes[0].o_height/2)-60,0,0,1,sf::Color::White,0,0,0,-1,0,0,1,1,1,false,0,vector<Entity::Loot>(), data);
        }
        else
        {
            cout << "No item dropped :(" << endl;
        }

        dropped_item = true;
    }
}
