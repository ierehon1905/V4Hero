#include "SaveReader.h"
#include "Func.h"
#include "DebugOut.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include "Config.h"
using namespace std;

SaveReader::SaveReader()
{
    ifstream check("resources/data/sv1.p4sv");
    bool exists = check.good();
    check.close();

    ///if config not exists -update: then dont create fresh one :)
    /*if(!exists)
    {
        ofstream conf("resources/data/sv1.p4sv");

        if(conf.is_open())
        {
            ///Safety warning
            conf << "# Take caution! The data below represents your save data! Don't edit it unless you know what you're doing, and if you must, PLEASE back it up somewhere else first <3 #";
            conf << '\n';
        }

        conf.close();
    }*/

    isNewSave = !exists;

    itemreg.ReadItemFiles();
}

void SaveReader::LoadSave(Config& tconfig)
{
    config = &tconfig;
    debugOut = config->debugOut;

    ifstream conf("resources/data/sv1.p4sv");
    if(conf.good())
    {
        string line;
        while(getline(conf, line))
        {
            ///ignore comments
            if(line.find("#") == std::string::npos && line.find("//") == std::string::npos && line.length()>0)
            {
                ///Split the Key and Value
                vector<string> key = Func::Split(line,':');
                //configMap[key[0]] = key[1];
                //cout << "Loaded key '" << key[0] << "' with value '" << key[1] << "'" << endl;
                if(key[0]=="name"){
                    kaminame = key[1];
                } else if(key[0]=="timeslaunched"){
                    timeslaunched = stoi(key[1]);
                    timeslaunched++;
                } else if(key[0]=="yariponsUnlocked"){
                    timeslaunched = stoi(key[1]);
                } else if(key[0]=="ITEM"){
                    InventoryItem invItem;
                    invItem.item = itemreg.GetItemByID(stoi(key[1]));
                    invItem.inventoryId =invdata.items.size();
                    cout << "ITEM: " << invItem.item->category_id << endl;
                    invdata.items.push_back(invItem);
                } else if(key[0]=="heroUnlocked"){
                    heroUnlocked = stoi(key[1]);
                } else if(key[0]=="PON"){
                    cout << "PON reading: " << line << endl;
                    vector<string> ponData = Func::Split(key[1],'|');
                    Pon newPon = Pon(this);
                    newPon.pon_id=stoi(ponData[0]);
                    newPon.pon_class=stoi(ponData[1]);
                    newPon.pon_squad_position=stoi(ponData[2]);


                    newPon.pon_exp=stoi(ponData[3]);
                    newPon.pon_level=stoi(ponData[4]);

                    if (stoi(ponData[5])!=-1){
                        newPon.GiveItem(stoi(ponData[5]));
                    }
                    if (stoi(ponData[6])!=-1){
                        newPon.GiveItem(stoi(ponData[6]));
                    }
                    if (stoi(ponData[7])!=-1){
                        newPon.GiveItem(stoi(ponData[7]),1);
                    }
                    if (stoi(ponData[8])!=-1){
                        newPon.GiveItem(stoi(ponData[8]));
                    }

                    ponreg.pons.push_back(newPon);
                }
                else if(key[0] == "MISSION")
                {
                    missionsUnlocked.push_back(stoi(key[1]));
                }
                else if(key[0] == "LOCATIONS")
                {
                    locationsUnlocked = stoi(key[1]);
                }
                else if(key[0] == "MISSIONLEVEL")
                {
                    vector<string> l = Func::Split(key[1], ',');

                    int lvl = stoi(l[1]);

                    if(lvl < 0)
                    lvl = 1;

                    missionLevels[stoi(l[0])] = lvl;
                }
                else if(key[0] == "version")
                {
                    savever = key[1];
                }
            }
        }
    }
    else
    {
        cout << "ERROR! Could not load save file!" << endl;
    }
    conf.close();
}

void SaveReader::Flush() ///Empties the save data.
{
    missionsUnlocked.clear();
    missionLevels.clear();
    locationsUnlocked = 1;

    //invdata.items.clear();

    PonRegistry n_ponreg;
    InventoryData n_invdata;

    ponreg = n_ponreg;
    invdata = n_invdata;
}

void SaveReader::CreateBlankSave() ///Creates a blank save data for use
{
    cout << "SaveReader::CreateBlankSave()" << endl;

    ///name of god
    kaminame = "Kamipon";

    ///times launched (unnecessary?)
    timeslaunched = 0;
    yariponsUnlocked = 3;
    heroUnlocked = 1;

    ///Adding starter items
    vector<int> starter_items = {1,1,1,16,16,16}; ///3x wooden spear, 3x wooden helm

    for(int i=0; i<starter_items.size(); i++)
    {
        InventoryItem invItem;
        invItem.item = itemreg.GetItemByID(starter_items[i]);
        invItem.inventoryId = invdata.items.size();
        invdata.items.push_back(invItem);

        cout << "Adding item with InvID " << invItem.inventoryId << " realID: " << invItem.item->item_id << endl;
    }

    ///Defining 3 Yaripons

    for(int i=0; i<3; i++)
    {
        Pon newPon = Pon(this);

        newPon.pon_id = i;
        newPon.pon_class = 1;
        newPon.pon_squad_position = i;

        newPon.pon_exp = 0;
        newPon.pon_level = 1;

        newPon.GiveItem(0+i);
        newPon.GiveItem(3+i);

        ponreg.pons.push_back(newPon);
    }

    ///Worldmap data
    missionsUnlocked.push_back(1);
    locationsUnlocked = 1;
}

void SaveReader::Save()
{
    ofstream conf2("resources/data/sv1.p4sv", ios::ate);
    conf2.seekp(0);
    if(conf2.is_open())
    {
        conf2 << "Take caution! The data below represents your save data! Don't edit it unless you know what you're doing, and if you must, PLEASE back it up somewhere else first <3 #" <<'\n';
        conf2 << "version:1.1" << '\n';
        conf2 << "name:" << kaminame.toAnsiString() <<'\n';
        conf2 << "timeslaunched:" << timeslaunched <<'\n';
        conf2 << "yariponsUnlocked:" << yariponsUnlocked <<'\n';
        conf2 << "heroUnlocked:" << heroUnlocked <<'\n';
        conf2 << "# item layout:" <<'\n';
        conf2 << "# ITEM:id" <<'\n';
        for (int i=0; i<invdata.items.size(); i++){
            InventoryItem current_item = invdata.items[i];
            conf2 << "ITEM:" << current_item.item->item_id <<'\n';
        }
        conf2 << "# pon layout: " <<'\n';
        conf2 << "# PON:unitTypeID (0 hero, 1 yaripon)|totalExpNum|lvlNum|slot1_Item_Id|slot2_Item_Id|slot3_Item_Id|slot4_Item_Id|slot5_Item_Id|" <<'\n';
        for (int j=0; j<ponreg.pons.size(); j++){
            Pon current_pon = ponreg.pons[j];
            cout  <<"PON:" << current_pon.pon_id<<'|' <<current_pon.pon_class<<'|' <<current_pon.pon_squad_position<<'|' <<current_pon.pon_exp<<'|' <<current_pon.pon_level<<'|' <<current_pon.weapon_invItem_id<<'|' <<current_pon.armour_invItem_id<<'|' <<current_pon.weapon2_invItem_id<<'|' <<current_pon.mask_invItem_id<<'|' <<'\n';

            conf2 << "PON:" << current_pon.pon_id<<'|' <<current_pon.pon_class<<'|' <<current_pon.pon_squad_position<<'|' <<current_pon.pon_exp<<'|' <<current_pon.pon_level<<'|' <<current_pon.weapon_invItem_id<<'|' <<current_pon.armour_invItem_id<<'|' <<current_pon.weapon2_invItem_id<<'|' <<current_pon.mask_invItem_id<<'|' <<'\n';
        }

        conf2 << "# missions unlock" <<'\n';
        conf2 << "# MISSION:id" <<'\n';
        conf2 << "# LOCATIONS:number of locations unlocked" <<'\n';
        for (int i=0; i<missionsUnlocked.size(); i++){
            conf2 << "MISSION:" << to_string(missionsUnlocked[i]) <<'\n';
        }
        conf2 << "LOCATIONS:" << to_string(locationsUnlocked) <<'\n';

        conf2 << "# mission levels" << '\n';
        conf2 << "# MISSIONLEVEL:id,level" << '\n';

        for (auto const& x : missionLevels)
        {
            conf2 << "MISSIONLEVEL:" << to_string(x.first) << "," << to_string(x.second) << '\n';
        }

            /*for(int i=0; i<configMap.size(); i++)
        {
            if(i == 0){
                conf2 << "# Take caution! Changing some of the settings below may cause your game to crash or become unstable! Don't edit this file unless you know what you're doing! #" <<'\n';
            }
            /*
            ///save all keys and defaults
            conf2 << configKeys[i] << ":" << configMap[configKeys[i]];

            cout << "Saving config entry: " << configKeys[i] << " = " << configMap[configKeys[i]] << endl;

            ///remember to newline
            if(i != configMap.size()-1)
            conf2 << '\n';*/
        //}
    }

    conf2.close();
}

bool SaveReader::isMissionUnlocked(int mission)
{
    if(std::find(missionsUnlocked.begin(), missionsUnlocked.end(), mission) != missionsUnlocked.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
