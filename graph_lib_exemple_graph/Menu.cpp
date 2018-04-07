#include "Menu.h"

BoutonMenu::BoutonMenu(int x, int y, int h, int l)
{
    m_boite.set_dim(1000,740);
    m_boite.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_boite.set_bg_color(JAUNECLAIR);

    m_boite.add_child(m_Bouton_graph1);
    m_Bouton_graph1.set_dim(300,200);
    m_Bouton_graph1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
    m_Bouton_graph1.add_child(m_png_graph1);
    m_png_graph1.set_pic_name("graph1.png");
    m_png_graph1.set_pic_idx(0);
    m_png_graph1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);


     m_boite.add_child(m_Bouton_graph2);
     m_Bouton_graph2.set_dim(300,200);
     m_Bouton_graph2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
     m_Bouton_graph2.add_child(m_png_graph2);
     m_png_graph2.set_pic_name("graph2.png");
     m_png_graph2.set_pic_idx(0);
     m_png_graph2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

     m_boite.add_child(m_Bouton_graph3);
     m_Bouton_graph3.set_dim(300,200);
     m_Bouton_graph3.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
     m_Bouton_graph3.add_child(m_png_graph3);
     m_png_graph3.set_pic_name("graph3.png");
     m_png_graph3.set_pic_idx(0);
     m_png_graph3.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);

     m_boite.add_child(m_quitter);
     m_quitter.set_dim(116,30);
     m_quitter.set_bg_color(BLEUCLAIR);
     m_quitter.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
     m_quitter.add_child(m_quitter_txt);
     m_quitter_txt.set_message("Quitter");
     m_quitter_txt.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
}






int Menu::choixgraph()
 {

     if(grman::mouse_click&1 && m_interface->m_Bouton_graph1.is_mouse_over())
     {
         return 1;
     }

      if(grman::mouse_click&1 && m_interface->m_Bouton_graph2.is_mouse_over())
     {
         return 2;
     }

      if(grman::mouse_click&1 && m_interface->m_Bouton_graph3.is_mouse_over())
     {
         return 3;
     }

    if(grman::mouse_click&1 && m_interface->m_quitter.is_mouse_over())
     {
         return 4;
     }

 }

void Menu::Affichermenu()
{
    m_interface= std::make_shared<BoutonMenu>(0,0,1000,740);
}
 void Menu::update()
 {
     if (!m_interface)
        return;

     m_interface->m_boite.update();
     choixgraph();

 }
Menu::~Menu()
{
    //dtor
}
