#ifndef MENU_H
#define MENU_H


#include <vector>
#include <map>
#include <string>
#include <memory>
#include "grman/grman.h"



class BoutonMenu
{
    friend class Menu;

public:
    BoutonMenu(int x, int y, int h, int l);
private:
    grman::WidgetBox m_boite;

    grman::WidgetBox m_Bouton_graph1;
    grman::WidgetBox m_Bouton_graph2;
    grman::WidgetBox m_Bouton_graph3;
    grman::WidgetBox m_quitter;
    grman::WidgetText m_quitter_txt;

    grman::WidgetImage m_png_graph1;
    grman::WidgetImage m_png_graph2;
    grman::WidgetImage m_png_graph3;


};


class Menu
{
    friend class BoutonMenu;
    public:
        Menu(BoutonMenu *interface=nullptr): m_interface(interface){  };
        void update();
        int choixgraph();
        void Affichermenu();

    virtual ~Menu();

    private:
        std::shared_ptr<BoutonMenu> m_interface = nullptr;

};

#endif // MENU_H
