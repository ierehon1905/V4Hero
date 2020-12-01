#include "SaveFileCreatedMenuButtonList.h"
#include "string"
#include "../MenuButton.h"
#include <iostream>
#include "../../Mission/MissionController.h"
#include "../MainMenu.h"
#include "../SaveFileCreated.h"
#include "../../V4Core.h"

using namespace std;
SaveFileCreatedMenuButtonList::SaveFileCreatedMenuButtonList()
{
    
}
void SaveFileCreatedMenuButtonList::Initialise(sf::Font *font,Config &newConfig,MissionController *controller,SaveFileCreatedMenu *parMenu)
{
    ButtonList::Initialise(font,newConfig,controller,parMenu);
    MenuButton* level1Button = new MenuButton(L"menu_button_confirm",font,42,550,this,0);
    buttons.push_back(*level1Button);
    buttons[0].SetSelected(false);
    
    this->SelectButtons = false;
    svCrtMnu = parMenu;
}
void SaveFileCreatedMenuButtonList::SelectButton(int index){
    currentIndex = index;
//    *parentMenu->v4core->LoadingThread;
    switch (currentIndex){
        case 0:
//            sf::Thread loadingThreadInstance(parentMenu->v4core->LoadingThread,parentMenu->v4core);
//            parentMenu->v4core->continueLoading=true;
//            parentMenu->v4core->window.setActive(false);
//            loadingThreadInstance.launch();
//            
//            parentMenu->Hide();
//            parentMenu->isActive = false;
//            svCrtMnu->nameEntryMenu->Hide();
//            
//            currentController->Initialise(*config,config->GetString("mission1Background"),*parentMenu->v4core);
//            currentController->StartMission(config->GetString("mission1Theme"),1,1);
//            
            break;
            
    }
}
SaveFileCreatedMenuButtonList::~SaveFileCreatedMenuButtonList()
{
    
}
