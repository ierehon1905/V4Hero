#ifndef CONFIG_H
#define CONFIG_H
#include <SFML/Graphics.hpp>
#include "StringRepository.h"
#include <vector>
#include <map>
#include <string>
#include "DebugOut.h"
class Config
{
    public:
    std::vector<std::string> configKeys = {"resX",
    "resY",
    "textureQuality",
    "framerateLimit",
    "enableFullscreen",
    "enableBorderlessWindow",
    "enableDrumChants",
    "enableDrums",
    "enablePataponChants",
    "keybindPata",
    "keybindPon",
    "keybindDon",
    "keybindChaka",
    "secondaryKeybindPata",
    "secondaryKeybindPon",
    "secondaryKeybindDon",
    "secondaryKeybindChaka",
    "keybindMenuEnter",
    "mission1Theme",
    "mission1Background",
    "mission2Theme",
    "mission2Background",
    "showDebugMsg",
    "showRhythmDebugMsg",
    "showImportantDebugMsg",
    "lang"};
    std::vector<std::string> configDefaults = {"1280",
    "720",
    "1",
    "240",
    "0",
    "0",
    "0",
    "1",
    "1",
    "71",
    "72",
    "74",
    "73",
    std::to_string(sf::Keyboard::A),
    std::to_string(sf::Keyboard::D),
    std::to_string(sf::Keyboard::S),
    std::to_string(sf::Keyboard::W),
    std::to_string(sf::Keyboard::Space),
    "Donja Lalin Theme",
    "nanjarohills",
    "Freakout Rock Theme",
    "patapineforest",
    "0",
    "0",
    "1",
    "1"};
    std::map<std::string,std::string> configMap;
    int configDebugID=0;
    bool changedLang = false;
    Config();
    void LoadConfig();
    void ReloadLanguages();
    DebugOut* debugOut;

    StringRepository strRepo;
    ///I wanted to overload these two in a single function, but somehow it just doesnt want to work...
    ///Will change it into one someday
    int GetInt(std::string key);
    std::string GetString(std::string key);
    void SetString(std::string key,std::string val);
    std::wstring GetLanguageName();
    void SaveConfig();
};

#endif // CONFIG_H
