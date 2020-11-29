#include "MainMenu.h"
#include "ButtonList.h"
#include "iostream"
#include "../V4Core.h"
MainMenu::MainMenu()
{
    //ctor
    isActive=true;
}
void MainMenu::Initialise(Config *thisConfigs, V4Core *parent)
{
    parent->SaveToDebugLog("Initializing Main Menu...");

    f_font.loadFromFile(thisConfigs->fontPath);
    config = thisConfigs;
    int q = thisConfigs->GetInt("textureQuality");
    int r = 1;

    quality = q;

    float ratioX, ratioY;

    switch(q)
    {
        case 0: ///low
        {
            ratioX = thisConfigs->GetInt("resX") / float(640);
            ratioY = thisConfigs->GetInt("resY") / float(360);
            break;
        }

        case 1: ///med
        {
            ratioX = thisConfigs->GetInt("resX") / float(1280);
            ratioY = thisConfigs->GetInt("resY") / float(720);
            break;
        }

        case 2: ///high
        {
            ratioX = thisConfigs->GetInt("resX") / float(1920);
            ratioY = thisConfigs->GetInt("resY") / float(1080);
            break;
        }

        case 3: ///ultra
        {
            ratioX = thisConfigs->GetInt("resX") / float(3840);
            ratioY = thisConfigs->GetInt("resY") / float(2160);
            break;
        }
    }

    float resRatioX = thisConfigs->GetInt("resX") / float(1280);
    float resRatioY = thisConfigs->GetInt("resY") / float(720);

    rs_cover.setSize(sf::Vector2f(thisConfigs->GetInt("resX"), thisConfigs->GetInt("resY")));
    rs_cover.setFillColor(sf::Color(0,0,0,255));
    rs_cover2.setSize(sf::Vector2f(thisConfigs->GetInt("resX"), thisConfigs->GetInt("resY")));
    rs_cover2.setFillColor(sf::Color(0,0,0,0));

    logow_bg.loadFromFile("resources/graphics/ui/menu/logowbg.png", q, r);
    logow_text.loadFromFile("resources/graphics/ui/menu/logowtxt.png", q, r);
    logow_shadow.loadFromFile("resources/graphics/ui/menu/logowsh.png", q, r);

    logow_bg.setColor(sf::Color(120,0,0,ui_alpha));
    logow_shadow.setColor(sf::Color(64,64,64,ui_alpha));
    logow_text.setColor(sf::Color(255,255,255,ui_alpha));

    t_pressanykey.createText(f_font, 26, sf::Color(255,255,255,t_alpha), Func::ConvertToUtf8String(thisConfigs->strRepo.GetUnicodeString(L"menu_pressanykey")), q, r);

    sb_smash.loadFromFile("resources/sfx/menu/smash.ogg");
    s_smash.setBuffer(sb_smash);
    s_smash.setVolume(float(thisConfigs->GetInt("masterVolume"))*(float(thisConfigs->GetInt("sfxVolume"))/100.f));

    grass_1.loadFromFile("resources/graphics/ui/menu/grass_1.png", q, r);
    grass_2.loadFromFile("resources/graphics/ui/menu/grass_2.png", q, r);
    grass_3.loadFromFile("resources/graphics/ui/menu/grass_3.png", q, r);
    grass_4.loadFromFile("resources/graphics/ui/menu/grass_4.png", q, r);

    grass_1.setScale(1.05,1.05);
    grass_2.setScale(1.05,1.05);
    grass_3.setScale(1.05,1.05);
    grass_4.setScale(1.05,1.05);

    grass_1.setOrigin(grass_1.getLocalBounds().width/float(100),grass_1.getLocalBounds().height);
    grass_2.setOrigin(grass_2.getLocalBounds().width/float(100),grass_2.getLocalBounds().height);
    grass_3.setOrigin(grass_3.getLocalBounds().width/float(100),grass_3.getLocalBounds().height);
    grass_4.setOrigin(grass_4.getLocalBounds().width/float(100),grass_4.getLocalBounds().height);

    logo.loadFromFile("resources/graphics/ui/menu/logo.png", q, r);
    logo.setOrigin(logo.getLocalBounds().width/2, logo.getLocalBounds().height/2);

    logo_shadow.loadFromFile("resources/graphics/ui/menu/logo_shadow.png", q, r);
    logo_shadow.setOrigin(logo_shadow.getLocalBounds().width/2, logo_shadow.getLocalBounds().height/2);

    totem[0].loadFromFile("resources/graphics/ui/menu/totem_1.png", q, r);
    totem[1].loadFromFile("resources/graphics/ui/menu/totem_2.png", q, r);
    totem[2].loadFromFile("resources/graphics/ui/menu/totem_3.png", q, r);
    totem[3].loadFromFile("resources/graphics/ui/menu/totem_4.png", q, r);

    totem[0].setOrigin(0,totem[0].getLocalBounds().height);
    totem[1].setOrigin(0,totem[1].getLocalBounds().height);
    totem[2].setOrigin(0,totem[2].getLocalBounds().height);
    totem[3].setOrigin(0,totem[3].getLocalBounds().height);

    fire_1.loadFromFile("resources/graphics/ui/menu/fire_1.png", q, r);
    fire_2.loadFromFile("resources/graphics/ui/menu/fire_2.png", q, r);
    fire_3.loadFromFile("resources/graphics/ui/menu/fire_3.png", q, r);

    fire_1.setOrigin(fire_1.getLocalBounds().width/2, fire_1.getLocalBounds().height);
    fire_2.setOrigin(fire_2.getLocalBounds().width/2, fire_2.getLocalBounds().height);
    fire_3.setOrigin(fire_3.getLocalBounds().width/2, fire_3.getLocalBounds().height);

    aura.loadFromFile("resources/graphics/ui/menu/aura.png", q, r);
    aura.setOrigin(aura.getLocalBounds().width/2, aura.getLocalBounds().height/2);

    sword_1.loadFromFile("resources/graphics/ui/menu/sword.png", q, r);
    sword_2.loadFromFile("resources/graphics/ui/menu/sword.png", q, r);

    sword_1.setOrigin(sword_1.getLocalBounds().width/2, sword_1.getLocalBounds().height/2);
    sword_2.setOrigin(sword_2.getLocalBounds().width/2, sword_2.getLocalBounds().height/2);

    sword_1.setScale(1, 1);
    sword_2.setScale(-1, 1);

    for(int i=0; i<=3; i++)
    {
        t_option[i].createText(f_font, 24, sf::Color::White, "", q, r);
    }

    string vx_params = "0,135,38,23;80,135,38,23;680,205,107,132;-1,205,107,132";

    vector<string> v_vxparams = Func::Split(vx_params,';');
    std::vector<sf::Vector2f> vx_pos;
    std::vector<sf::Color> vx_color;

    for(int i=0; i<v_vxparams.size(); i++)
    {
        vector<string> tmp = Func::Split(v_vxparams[i],',');

        sf::Vector2f tmp_vector;
        sf::Color tmp_color;

        tmp_vector.x = 0;
        tmp_vector.y = atof(tmp[0].c_str()) * resRatioY;

        if(tmp[0] == "-1")
        {
            tmp_vector.y = 720 * resRatioY;
        }

        tmp_color.r = atoi(tmp[1].c_str());
        tmp_color.g = atoi(tmp[2].c_str());
        tmp_color.b = atoi(tmp[3].c_str());

        sf::Vector2f tmp_vector2;

        tmp_vector2.x = 1280 * resRatioX;
        tmp_vector2.y = atof(tmp[0].c_str()) * resRatioY;

        if(tmp[0] == "-1")
        {
            tmp_vector2.y = 720 * resRatioY;
        }

        vx_pos.push_back(tmp_vector);
        vx_color.push_back(tmp_color);

        vx_pos.push_back(tmp_vector2);
        vx_color.push_back(tmp_color);
    }

    sf::VertexArray tmp(sf::TrianglesStrip,vx_pos.size());
    v_background = tmp;

    for(int i=0; i<vx_pos.size(); i++)
    {
        v_background[i].position = vx_pos[i];
        v_background[i].color = vx_color[i];

        cout << "vx_pos: " << vx_pos[i].x << " " << vx_pos[i].y << endl;
    }

    g_x[0] = 0;
    g_x[1] = 0;
    g_x[2] = 0;
    g_x[3] = 0;

    float volume = (float(thisConfigs->GetInt("masterVolume"))*(float(thisConfigs->GetInt("bgmVolume"))/100.f));

    sb_title_loop.loadFromFile("resources/sfx/menu/menuloop.ogg");
    title_loop.setBuffer(sb_title_loop);
    title_loop.setLoop(true);
    title_loop.setVolume(volume);

    Scene::Initialise(thisConfigs,parent);

    optionsMenu.Initialise(config,v4core,this);

    ifstream fr("resources/firstrun");
    if(fr.good())
    {
        firstrun = false;
        premenu = true;
    }
    else
    {
        cout << "It's your first time running the game!" << endl;
        firstrun = true;
    }

    msgcloud.Create(45, sf::Vector2f(640,480), sf::Color::White, true, thisConfig->GetInt("textureQuality"), thisConfig->fontPath);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_1")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_2")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_3")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_4")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_5")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_6")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_7")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_8")), true);
    msgcloud.AddDialog(Func::ConvertToUtf8String(thisConfig->strRepo.GetUnicodeString(L"firstrun_dialog_9")), true);

    temp_menu.push_back(thisConfig->strRepo.GetUnicodeString(L"menu_newgame"));
    temp_menu.push_back(thisConfig->strRepo.GetUnicodeString(L"menu_continue"));
    temp_menu.push_back(thisConfig->strRepo.GetUnicodeString(L"menu_options"));
    temp_menu.push_back(thisConfig->strRepo.GetUnicodeString(L"menu_exit"));

    introductionMenu.Initialise(config,v4core,this);

    parent->SaveToDebugLog("Main menu initialized.");
    //title_loop.play();
    startClock.restart();
    frClock.restart();
}

void MainMenu::EventFired(sf::Event event)
{
    if (patapolisMenu.isActive)
    {
        patapolisMenu.EventFired(event);
    }
    else if (nameEntryMenu.isActive)
    {
        nameEntryMenu.EventFired(event);
    }
    else if (optionsMenu.isActive)
    {
        optionsMenu.EventFired(event);
    }
    else if (v4core->currentController.isInitialized)
    {
        if(event.type == sf::Event::KeyPressed)
        {

        }
    }
    else if(isActive)
    {
        if(firstrun)
        {

        }
        else if(!premenu)
        {
            if(dialogboxes.size() <= 0)
            {
                if(event.type == sf::Event::MouseButtonReleased)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(mouseInBounds)
                        SelectMenuOption();
                    }
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;

                    cout << mouseX << " " << mouseY << endl;

                    UsingMouseSelection=true;
                }
            }
        }
    }
}
void MainMenu::SelectMenuOption()
{
    switch (totem_sel)
    {
        case 0: // load the start game cutscenes and menu
        {
            /*title_loop.stop();

            Hide();
            sf::Thread loadingThreadInstance(v4core->LoadingThread,v4core);
            v4core->continueLoading=true;
            v4core->window.setActive(false);
            loadingThreadInstance.launch();

            nameEntryMenu.Show();
            nameEntryMenu.isActive = true;
            nameEntryMenu.Initialise(config,v4core,this);

            v4core->continueLoading=false;*/

            ifstream check("resources/data/sv1.p4sv");
            bool exists = check.good();
            check.close();

            if(!exists)
            {
                cout << "There is no save. Start new game!" << endl;

                screenFade.Create(thisConfig, 1, 512);
                goto_id = 0;

                /*v4core->savereader.Flush();
                v4core->savereader.CreateBlankSave();

                title_loop.stop();

                introductionMenu.Show();
                introductionMenu.isActive = true;
                introductionMenu.timeout.restart();

                patapolisMenu.loadedSave = false;*/
            }
            else
            {
                cout << "There is an existing save data. Ask if overwrite" << endl;

                std::vector<sf::String> a = {Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"nav_yes")),Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"nav_no"))};

                PataDialogBox db;
                db.Create(f_font, Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"menu_saveexists")), a, config->GetInt("textureQuality"));
                db.id = 0;
                dialogboxes.push_back(db);
            }

            break;
        }
        case 1: // load save and patapolis
        {
            ifstream check("resources/data/sv1.p4sv");
            bool exists = check.good();
            check.close();

            if(exists)
            {
                /** Load save from savereader **/
                v4core->savereader.Flush();
                v4core->savereader.LoadSave(*config);

                if(v4core->savereader.savever != "1.1")
                {
                    cout << "Invalid save data!" << endl;

                    std::vector<sf::String> a = {Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"nav_understood"))};

                    PataDialogBox db;
                    db.Create(f_font, Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"menu_nosupportdata")), a, config->GetInt("textureQuality"));
                    db.id = 2;
                    dialogboxes.push_back(db);
                }
                else
                {
                    screenFade.Create(thisConfig, 1, 512);
                    goto_id = 1;
                }
            }
            else
            {
                cout << "There is no savedata. Error" << endl;

                std::vector<sf::String> a = {Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"nav_understood"))};

                PataDialogBox db;
                db.Create(f_font, Func::ConvertToUtf8String(config->strRepo.GetUnicodeString(L"menu_nodata")), a, config->GetInt("textureQuality"));
                db.id = 1;
                dialogboxes.push_back(db);
            }

            break;
        }
        case 2:
        {
            // load the options menu
            screenFade.Create(thisConfig, 1, 512);
            goto_id = 2;
            break;
        }
        case 3:
        {
            // quit the game probably
            v4core->closeWindow=true;
            break;
        }
    }
}
void MainMenu::Update(sf::RenderWindow &window, float fps, InputController& inputCtrl)
{
    if (v4core->currentController.isInitialized)
    {
        v4core->currentController.Update(window, fps, inputCtrl);
    }
    else if(patapolisMenu.isActive)
    {
        patapolisMenu.Update(window,fps,inputCtrl);
    }
    else if(introductionMenu.isActive)
    {
        introductionMenu.Update(window,fps,inputCtrl);
    }
    else if(optionsMenu.isActive)
    {
        optionsMenu.Update(window,fps,inputCtrl);
    }
    else if(isActive)
    {
        if(firstrun)
        {
            if(frClock.getElapsedTime().asSeconds() > 2)
            {
                if(!msgcloud.done)
                {
                    if(msgcloud.firstrender)
                    msgcloud.Show();
                }
            }

            if(msgcloud.done)
            {
                if(!premenu)
                frwaitClock.restart();

                premenu = true;

                startClock.restart();
            }

            if(premenu)
            {
                if(frwaitClock.getElapsedTime().asSeconds() > 1)
                {
                    firstrun = false;

                    ofstream fr("resources/firstrun", ios::trunc);
                    fr.close();
                }
            }

            msgcloud.Draw(window, fps, inputCtrl);

        }
        else if(premenu)
        {
            if(startClock.getElapsedTime().asSeconds() > 2)
            {
                if(!keypressed)
                {
                    if(ui_alpha < 255)
                    {
                        ui_alpha += 255.0 / fps;
                    }

                    if(ui_alpha >= 255)
                    {
                        ui_alpha = 255;
                    }

                    if(t_alpha < 128)
                    {
                        t_alpha += 128.0 / fps;
                    }

                    if(t_alpha >= 128)
                    {
                        t_alpha = 128;
                    }

                    logow_bg.setColor(sf::Color(120,0,0,ui_alpha));
                    logow_text.setColor(sf::Color(255,255,255,ui_alpha));
                    logow_shadow.setColor(sf::Color(64,0,0,ui_alpha));

                    if(inputCtrl.isAnyKeyPressed())
                    {
                        s_smash.play();
                        logow_bg.setColor(sf::Color(200,0,0,255));
                        logow_shadow.setColor(sf::Color(200,0,0,255));
                        logow_text.setColor(sf::Color(255,255,255,255));
                        ui_alpha = 255;
                        logow_scale = 1.2;
                        logow_shscale = 1.2;
                        dest_y = 360;
                        keypressed = true;
                        menuClock.restart();
                    }
                }

                logow_bg.setOrigin(logow_bg.getLocalBounds().width/2, logow_bg.getLocalBounds().height/2);
                logow_text.setOrigin(logow_text.getLocalBounds().width/2, logow_text.getLocalBounds().height/2);
                logow_shadow.setOrigin(logow_shadow.getLocalBounds().width/2, logow_shadow.getLocalBounds().height/2);

                if(dest_y > cur_y)
                {
                    cur_y += abs(dest_y - cur_y) * 2 / fps;
                }
                if(dest_y < cur_y)
                {
                    cur_y -= abs(dest_y - cur_y) * 2 / fps;
                }

                logow_bg.setPosition(640,cur_y);
                logow_text.setPosition(logow_bg.getPosition().x+1,logow_bg.getPosition().y-3);
                logow_shadow.setPosition(logow_bg.getPosition().x,logow_bg.getPosition().y);

                if(logow_scale > 1)
                logow_scale -= 0.5 / fps;
                if(logow_shscale > 1)
                logow_shscale -= 0.5 / fps;

                if(logow_scale <= 1)
                logow_scale = 1;
                if(logow_shscale <= 1)
                logow_shscale = 1;

                logow_bg.setScale(logow_scale);
                logow_text.setScale(logow_scale);
                logow_shadow.setScale(logow_shscale);

                window.draw(rs_cover);

                logow_shadow.draw(window);
                logow_bg.draw(window);
                logow_text.draw(window);

                if(keypressed)
                {
                    t_alpha -= 255.0 / fps;

                    if(t_alpha <= 0)
                    t_alpha = 0;

                    if(menuClock.getElapsedTime().asSeconds() > 3)
                    {
                        cv_alpha += 255.0 / fps;

                        if(cv_alpha >= 255)
                        cv_alpha = 255;
                    }

                    if(menuClock.getElapsedTime().asSeconds() > 4.5)
                    {
                        premenu = false;
                    }
                }

                t_pressanykey.setOrigin(t_pressanykey.getLocalBounds().width/2, t_pressanykey.getLocalBounds().height/2);
                t_pressanykey.setPosition(640,440);
                t_pressanykey.setColor(sf::Color(255,255,255,t_alpha));
                t_pressanykey.draw(window);

                rs_cover2.setFillColor(sf::Color(0,0,0,cv_alpha));
                window.draw(rs_cover2);
            }
        }
        else
        {
            if(title_loop.getStatus() == sf::Sound::Status::Stopped)
            {
                cout << "I am playing" << endl;
                title_loop.play();
            }

            window.draw(v_background);

            if(fade == 0)
            alpha -= float(15)/fps;

            if(fade == 1)
            alpha += float(15)/fps;

            if(alpha <= 220)
            fade = 1;

            if(alpha >= 250)
            fade = 0;

            float scale = 1 + ((alpha - 220) / 500);
            float aurascale = 1 + ((alpha - 220)) / 250;

            g_dest[0] = (mouseX/320.f - 2.f) * (-1);
            g_dest[1] = (mouseX/106.f - 6.f) * (-1);
            g_dest[2] = (mouseX/45.f - 14.f) * (-1);
            g_dest[3] = (mouseX/21.f - 30.f) * (-1);

            for(int i=0; i<=3; i++)
            {
                if(g_dest[i] < g_x[i])
                g_x[i] -= abs(g_dest[i] - g_x[i]) / 100 / fps * 240;
                if(g_dest[i] > g_x[i])
                g_x[i] += abs(g_dest[i] - g_x[i]) / 100 / fps * 240;
            }


            ///dont make it go off bounds
            if(g_x[0] > 2)
            g_x[0] = 2;

            if(g_x[0] < -2)
            g_x[0] = -2;


            if(g_x[1] > 6)
            g_x[1] = 6;

            if(g_x[1] < -6)
            g_x[1] = -6;


            if(g_x[2] > 14)
            g_x[2] = 14;

            if(g_x[2] < -14)
            g_x[2] = -14;


            if(g_x[3] > 30)
            g_x[3] = 30;

            if(g_x[3] < -30)
            g_x[3] = -30;


            grass_1.setPosition(g_x[0], 630);
            grass_2.setPosition(g_x[1], 696);
            grass_3.setPosition(g_x[2], 724);
            grass_4.setPosition(g_x[3], 724);

            grass_1.draw(window);
            grass_2.draw(window);
            grass_3.draw(window);

            logo_shadow.setPosition(640,140);
            logo.setPosition(640,140);

            logo_shadow.setColor(sf::Color(255,255,255,alpha));
            logo_shadow.setScale(scale,scale);

            logo_shadow.draw(window);
            logo.draw(window);

            float fire_shift = 0;

            //cout << "MouseX: " << (mouseX / window.getSize().x) * 1280 << endl;

            mouseInBounds = false;

            for(int i=0; i<=3; i++)
            {
                //cout << "Totem " << i << " bounds: " << totem[i].getPosition().x << " - " << (totem[i].getPosition().x + totem[totem_sel].getGlobalBounds().width) << endl;

                totem[i].setPosition((float(120) + float(306) * i) + g_x[3]/1.4, 720);
                if (UsingMouseSelection)
                {
                    if((mouseX / window.getSize().x) * 1280 > totem[i].getPosition().x)
                    {
                        if((mouseX / window.getSize().x) * 1280 < (totem[i].getPosition().x + totem[totem_sel].getGlobalBounds().width))
                        {
                            if((mouseY / window.getSize().y) * 720 > totem[i].getPosition().y-totem[i].getLocalBounds().height)
                            {
                                totem_sel = i;
                                mouseInBounds = true;
                            }
                        }
                    }
                }
            }

            float fire_x=0, fire_y=0;

            switch(totem_sel)
            {
                case 0:
                {
                    fire_shift = float(34);
                    fire_x = float(72.333);
                    fire_y = float(320);
                    break;
                }
                case 1:
                {
                    fire_shift = float(40);
                    fire_x = float(59.5);
                    fire_y = float(371);
                    break;
                }
                case 2:
                {
                    fire_shift = float(6);
                    fire_x = float(55);
                    fire_y = float(451.667);
                    break;
                }
                case 3:
                {
                    fire_shift = float(10);
                    fire_x = float(59.3333);
                    fire_y = float(498.667);
                    break;
                }
            }

            fire_1.setPosition(totem[totem_sel].getPosition().x + fire_x, fire_y + fire_shift);
            fire_2.setPosition(totem[totem_sel].getPosition().x + fire_x, fire_y + fire_shift);
            fire_3.setPosition(totem[totem_sel].getPosition().x + fire_x, fire_y + fire_shift);

            //cout << int(floor(fire)) << " " << totem[totem_sel].getGlobalBounds().width << " " << totem[totem_sel].getGlobalBounds().height << " vs " << fire_1.getPosition().x << " " << fire_1.getPosition().y << endl;

            switch(int(floor(fire)))
            {
                case 0:
                fire_1.draw(window);
                break;

                case 1:
                fire_2.draw(window);
                break;

                case 2:
                fire_3.draw(window);
                break;
            }

            fire += float(14) / fps;
            if(fire >= 3)
            fire = 0;

            aura.setPosition(fire_1.getPosition().x, fire_1.getPosition().y - (fire_1.getGlobalBoundsScaled().height/2));
            aura.setScale(aurascale,aurascale);
            aura.draw(window);

            for(int i=0; i<=3; i++)
            totem[i].draw(window);

            grass_4.draw(window);

            if(old_sel != totem_sel)
            {
                cout << "Totem changed to " << totem_sel << endl;
                t_option[totem_sel].setScale(1.2,1.2);
            }

            for(int i=0; i<=3; i++)
            {
                if(t_option[i].getScale().x > 1)
                {
                    float new_scale = t_option[i].getScale().x - float(1)/fps;
                    t_option[i].setScale(new_scale, new_scale);
                }
                else
                {
                    t_option[i].setScale(1,1);
                }

                t_option[i].setString(Func::ConvertToUtf8String(temp_menu[i]));

                //cout << "Text " << i << ": " << t_option[i].orX << " " << t_option[i].orY << " " << t_option[i].getGlobalBounds().width << " " << t_option[i].getGlobalBounds().height << " " << t_option[i].getGlobalBoundsScaled().width << " " << t_option[i].getGlobalBoundsScaled().height << endl;

                //cout << t_option[i].getGlobalBoundsScaled().width/2 << " " << t_option[i].getGlobalBoundsScaled().height/2 << endl;
                t_option[i].setOrigin(t_option[i].getLocalBounds().width/2, t_option[i].getLocalBounds().height/2);

                //cout << "Text " << i << ": " << t_option[i].orX << " " << t_option[i].orY << " " << t_option[i].getGlobalBounds().width << " " << t_option[i].getGlobalBounds().height << " " << t_option[i].getGlobalBoundsScaled().width << " " << t_option[i].getGlobalBoundsScaled().height << endl;

                if(i == totem_sel)
                t_option[i].setPosition(totem[i].getPosition().x + (totem[i].getGlobalBoundsScaled().width/2), 720 - totem[i].getGlobalBoundsScaled().height - fire_1.getGlobalBoundsScaled().height - 35);
                else
                t_option[i].setPosition(totem[i].getPosition().x + (totem[i].getGlobalBoundsScaled().width/2), 720 - totem[i].getGlobalBoundsScaled().height - fire_1.getGlobalBoundsScaled().height/2);

                t_option[i].setColor(sf::Color(255,255,255,96));
                t_option[totem_sel].setColor(sf::Color::White);

                t_option[i].draw(window);
            }

            sword_1.setPosition(fire_1.getPosition().x - (fire_1.getGlobalBoundsScaled().width/2 + t_option[totem_sel].getGlobalBoundsScaled().width/2 + sword_1.getGlobalBoundsScaled().width/2), 720 - totem[totem_sel].getGlobalBoundsScaled().height - fire_1.getGlobalBoundsScaled().height - 30);
            sword_2.setPosition(fire_1.getPosition().x + (fire_1.getGlobalBoundsScaled().width/2 + t_option[totem_sel].getGlobalBoundsScaled().width/2 + sword_2.getGlobalBoundsScaled().width/2), 720 - totem[totem_sel].getGlobalBoundsScaled().height - fire_1.getGlobalBoundsScaled().height - 30);

            sword_1.draw(window);
            sword_2.draw(window);

            old_sel = totem_sel;

            cv_alpha -= 255.0 / fps;

            if(cv_alpha <= 0)
            cv_alpha = 0;

            rs_cover2.setFillColor(sf::Color(0,0,0,cv_alpha));
            window.draw(rs_cover2);

            window.setView(window.getDefaultView());

            screenFade.draw(window, fps);

            if(screenFade.checkFinished())
            {
                if(goto_id != -1)
                {
                    switch(goto_id)
                    {
                        case 0: ///New game
                        {
                            v4core->savereader.Flush();
                            v4core->savereader.CreateBlankSave();

                            title_loop.stop();

                            introductionMenu.Show();
                            introductionMenu.isActive = true;
                            introductionMenu.timeout.restart();

                            patapolisMenu.loadedSave = false;

                            break;
                        }

                        case 1: ///Continue
                        {
                            title_loop.stop();
                            Hide();
                            patapolisClock.restart();

                            if(!patapolisMenu.initialised)
                            {
                                sf::Thread loadingThreadInstance(&V4Core::LoadingThread,v4core);
                                v4core->continueLoading=true;
                                v4core->window.setActive(false);
                                loadingThreadInstance.launch();

                                patapolisMenu.Show();
                                patapolisMenu.isActive = true;
                                patapolisMenu.loadedSave = true;
                                patapolisMenu.Initialise(config,v4core,this);

                                v4core->continueLoading=false;
                            }
                            else
                            {
                                sf::Thread loadingThreadInstance(&V4Core::LoadingThread,v4core);
                                v4core->continueLoading=true;
                                v4core->window.setActive(false);
                                loadingThreadInstance.launch();

                                patapolisMenu.Show();
                                patapolisMenu.isActive = true;
                                patapolisMenu.screenFade.Create(thisConfig, 0, 512);

                                patapolisMenu.location = 3;
                                patapolisMenu.ctrlTips.create(54, patapolisMenu.f_font, 20, sf::String(L"L/R: Move      X: Interact      Select: Save      Start: Title screen"), quality);
                                patapolisMenu.SetTitle(patapolisMenu.location);
                                patapolisMenu.camPos = patapolisMenu.locations[patapolisMenu.location];

                                while(patapolisClock.getElapsedTime().asSeconds() < 3)
                                {
                                    ///do nothing lol
                                }

                                v4core->LoadingWaitForKeyPress();
                                v4core->continueLoading=false;
                            }

                            break;
                        }

                        case 2: ///Options
                        {
                            title_loop.stop();
                            Hide();
                            v4core->ChangeRichPresence("In Options menu", "logo", "");
                            optionsMenu.state = 0;
                            optionsMenu.sel = 0;
                            optionsMenu.Show();

                            optionsMenu.screenFade.Create(thisConfig, 0, 512);

                            break;
                        }
                    }

                    goto_id = -1;
                }
            }

            vector<int> db_e; ///dialog box erase

            for(int i=0; i<dialogboxes.size(); i++)
            {
                dialogboxes[i].x = 640;
                dialogboxes[i].y = 360;
                dialogboxes[i].Draw(window, fps, inputCtrl);

                if(dialogboxes[i].closed)
                db_e.push_back(i);
            }

            for(int i=0; i<db_e.size(); i++)
            {
                dialogboxes.erase(dialogboxes.begin()+db_e[i]-i);
            }

            if(dialogboxes.size() <= 0)
            {
                if((inputCtrl.isKeyPressed(InputController::Keys::LEFT)) || (inputCtrl.isKeyPressed(InputController::Keys::LTRIGGER)))
                {
                    UsingMouseSelection=false;

                    totem_sel-=1;
                    if (totem_sel<0)
                        totem_sel=3;
                    old_sel = totem_sel;

                    mouseX = totem_sel_pos[totem_sel];
                }

                if((inputCtrl.isKeyPressed(InputController::Keys::RIGHT)) || (inputCtrl.isKeyPressed(InputController::Keys::RTRIGGER)))
                {
                    UsingMouseSelection=false;

                    totem_sel+=1;
                    if (totem_sel>3)
                        totem_sel=0;
                    old_sel = totem_sel;

                    mouseX = totem_sel_pos[totem_sel];
                }

                if(inputCtrl.isKeyPressed(InputController::Keys::CROSS))
                {
                    UsingMouseSelection=false;

                    SelectMenuOption();
                    //title_loop.stop();
                }
            }
            else
            {
                if(inputCtrl.isKeyPressed(InputController::Keys::CROSS))
                {
                    switch(dialogboxes[dialogboxes.size()-1].CheckSelectedOption())
                    {
                        case 0:
                        {
                            if(dialogboxes[dialogboxes.size()-1].id == 0)
                            {
                                cout << "Starting new game!" << endl;
                                dialogboxes[dialogboxes.size()-1].Close();

                                screenFade.Create(thisConfig, 1, 512);
                                goto_id = 0;

                                break;
                            }
                            else if(dialogboxes[dialogboxes.size()-1].id == 1)
                            {
                                dialogboxes[dialogboxes.size()-1].Close();
                                break;
                            }
                            else if(dialogboxes[dialogboxes.size()-1].id == 2)
                            {
                                dialogboxes[dialogboxes.size()-1].Close();
                                break;
                            }
                        }

                        case 1:
                        {
                            cout << "Returning to title screen!" << endl;
                            dialogboxes[dialogboxes.size()-1].Close();

                            break;
                        }
                    }
                }
            }
        }
    }
}
void MainMenu::UpdateButtons(){
    /// this should update the text on all the buttons
}
void MainMenu::OnExit(){
    /// when we exit the main menu, we do nothing for now.
    /// perhaps we would want to unload sprites or songs etc
}
MainMenu::~MainMenu()
{
    //dtor
}
