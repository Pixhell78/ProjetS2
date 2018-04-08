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

    /// Le nom du r�pertoire o� se trouvent les images � charger
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


