#include <iostream>
#include "grman/grman.h"
#include <iostream>
#include "graph.h"
#include "Menu.h"

using namespace std;


int main()
{
    std::string NomDuGraph ="graph1";
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    Menu menu;

    menu.Affichermenu();
while (!key[KEY_SPACE])
    {
        menu.update();

        switch(menu.choixgraph())
        {
        case 1:
             NomDuGraph ="graph1";
            g.Charger(NomDuGraph);
            while(!key[KEY_SPACE]&& g.Boutonsgraph(NomDuGraph)!=1)
             {
              g.update(NomDuGraph);
              grman::mettre_a_jour();
             }
             g.detruire_graph();

            break;

        case 2:
             NomDuGraph ="graph2";
             g.Charger(NomDuGraph);
            while(!key[KEY_SPACE] && g.Boutonsgraph(NomDuGraph)!=1)
             {
              g.update(NomDuGraph);
              grman::mettre_a_jour();
             }
             g.detruire_graph();

            break;

        case 3:
            NomDuGraph ="graph3";
             g.Charger(NomDuGraph);
            while(!key[KEY_SPACE] && g.Boutonsgraph(NomDuGraph)!=1)
             {
              g.update(NomDuGraph);
              grman::mettre_a_jour();
             }
             g.detruire_graph();

            break;
        case 4:
            return 0;
            break;
        default:
            grman::mettre_a_jour();

        }


    }


    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


/*while (NomDuGraph=="")
    {
    menu.choixgraph();
    menu.update();
    }
    //g.Charger(NomDuGraph);

    if(NomDuGraph!="")
    while ( !key[KEY_ESC] )
    {
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update(NomDuGraph);

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    g.detruire_graph();
    grman::fermer_allegro();*/
