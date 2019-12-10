#ifndef INVENTORY_DATA_H
#define INVENTORY_DATA_H
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "InventoryItem.h"
class InventoryData
{
    public:
        std::vector<InventoryItem> items;
        InventoryItem GetItemByInvID(int id);
        int GetItemCountByTypeID(int id);
        int GetItemCountByName(std::string itemname);
        InventoryData();
        ~InventoryData();
};

#endif // INVENTORY_DATA_H