#include "graph.h"
#include <fstream>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_top_box.add_child(m_option);
    m_option.set_dim(15,15);
    m_option.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_option.set_bg_color(ROUGECLAIR);
    m_option.add_child(m_option_img);
    m_option_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_option_img.set_pic_name("option.jpg");


}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
    Bouton_Vertex();

}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Center);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(118,736);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Center);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(880,736);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Center);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child(m_sauvegarde);
    m_sauvegarde.set_dim(116,30);
    m_sauvegarde.set_pos(-2,0);

    m_sauvegarde.set_bg_color(BLEUCLAIR);
    m_sauvegarde.add_child(m_sauvegarde_text);
    m_sauvegarde_text.set_message("Sauvegarder");
    m_sauvegarde_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_afficher);
    m_afficher.set_dim(116,30);
    m_afficher.set_pos(-2,40);

    m_afficher.set_bg_color(BLEUCLAIR);
    m_afficher.add_child(m_afficher_text);
    m_afficher_text.set_message("Afficher ");
    m_afficher_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_menu);
    m_menu.set_dim(116,30);
    m_menu.set_pos(-2,700);

    m_menu.set_bg_color(BLEUCLAIR);
    m_menu.add_child(m_menu_text);
    m_menu_text.set_message("Retour");
    m_menu_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);


}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
/*void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 400, 50, "tamanoir.jpg");
    add_interfaced_vertex(1, 60.0, 700, 50, "jaguar.jpg");
    add_interfaced_vertex(2,  50.0, 200, 200, "fourmis.jpg");
    add_interfaced_vertex(3,  0.0, 375, 300, "tatou.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "tapir.jpg");
    add_interfaced_vertex(5,  0.0, 700, 600, "capybara.jpg", 0);
    add_interfaced_vertex(6,  0.0, 375, 600, "vegetaux.jpg", 1);
    add_interfaced_vertex(7,  0.0, 75, 600, "phasme.jpg", 2);
    add_interfaced_vertex(8,  0.0, 0, 350, "mante.jpg", 2);
    add_interfaced_vertex(9,  0.0, 50, 50, "mygale.jpg", 2);
    add_interfaced_vertex(10,  0.0, 200, 450, "papillon.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 6, 7, 50.0);
    add_interfaced_edge(1, 6, 10, 50.0);
    add_interfaced_edge(2, 6, 3, 50.0);
    add_interfaced_edge(3, 6, 4, 50.0);
    add_interfaced_edge(4, 6, 5, 50.0);
    add_interfaced_edge(5, 7, 8, 50.0);
    add_interfaced_edge(6, 10, 8, 50.0);
    add_interfaced_edge(7, 10, 2, 50.0);
    add_interfaced_edge(8, 10, 3, 50.0);
    add_interfaced_edge(9, 3, 1, 50.0);
    add_interfaced_edge(10, 4, 1, 50.0);
    add_interfaced_edge(11, 5, 1, 50.0);
    add_interfaced_edge(12, 0, 1, 50.0);
    add_interfaced_edge(13, 10, 8, 50.0);
    add_interfaced_edge(14, 8, 2, 50.0);
    add_interfaced_edge(15, 8, 9, 50.0);
    add_interfaced_edge(16, 2, 0, 50.0);



}*/

int Graph::Boutonsgraph(std::string NomDuGraph)
{
    if(grman::mouse_click && m_interface->m_sauvegarde.is_mouse_over())
    {
        Sauvegarde(NomDuGraph);
    }

    if(grman::mouse_click && m_interface->m_afficher.is_mouse_over())
    {
                Sauvegarde(NomDuGraph);
                this->detruire_graph();

        for ( auto &elmt : m_vertices ){
            elmt.second.Cacher=false;
        }
                Charger(NomDuGraph);

    }
    if(grman::mouse_click && m_interface->m_menu.is_mouse_over())
    {
        return 1;
    }

}

void Vertex::Bouton_Vertex()
{
        if(grman::mouse_click && m_interface->m_option.is_mouse_over())
        Vertex::Cacher = 1;
}

void Edge::hide_edge_in(Vertex& v){

m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
m_interface->m_top_edge.detach_from();


}
void Edge::hide_edge_out(Vertex& v){

m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
m_interface->m_top_edge.detach_to();

}
void Edge::Show_Edges(Vertex& from , Vertex& to){

    m_interface->m_top_edge.attach_from(from.m_interface->m_top_box);
    m_interface->m_top_edge.attach_to(to.m_interface->m_top_box);
    m_interface->m_top_edge.reset_arrow_with_bullet();

    m_interface->m_top_edge.add_child(m_interface->m_box_edge);

}

void Vertex::Show_Vertex(){

        if(m_interface->m_top_box.get_dimx()!=130)
        {


        m_interface->m_top_box.set_dim(130, 100);
        //m_interface->m_top_box.set_border(2);

        m_interface->m_top_box.add_child( m_interface->m_img );
        m_interface->m_img.set_pos(30,0);

        m_interface->m_top_box.add_child(m_interface->m_slider_value);
        m_interface->m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

        m_interface->m_top_box.add_child(m_interface->m_label_value);
        m_interface->m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);




        m_interface->m_top_box.add_child(m_interface->m_option);
        m_interface->m_option.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

        m_interface->m_option.add_child(m_interface->m_option_img);
        m_interface->m_option_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

        m_interface->m_top_box.add_child(m_interface-> m_box_label_idx );
        m_interface->m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
        }

}
void Vertex::Hide_Vertex(){

    m_interface->m_top_box.remove_child(m_interface->m_option);
    m_interface->m_top_box.remove_child(m_interface->m_option_img);
    m_interface->m_top_box.remove_child(m_interface->m_slider_value);
    m_interface->m_top_box.remove_child(m_interface->m_box_label_idx);
    m_interface->m_top_box.remove_child(m_interface->m_label_value);
    m_interface->m_top_box.remove_child(m_interface->m_img);
    m_interface->m_top_box.set_dim(0,0);


}

void Graph::Delete_vertex(){


    std::map<int,Vertex>::iterator it1;
    std::map<int,Edge>::iterator it2;

    for ( auto &elmt : m_vertices){
        if(elmt.second.Cacher==true){
            elmt.second.Hide_Vertex();

            //std::cout<<elmt.second.m_out.size();
            for(int i =0 ; i < (int)elmt.second.m_in.size();i++){
            m_edges[elmt.second.m_in[i]].hide_edge_in(elmt.second);

            }

            for(int i =0 ; i < (int)elmt.second.m_out.size();i++){
                m_edges[elmt.second.m_out[i]].hide_edge_out(elmt.second);


            }
            }
        }
    }

void Graph::Charger(std::string NomDuGraph){
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::ifstream f(NomDuGraph+".txt",std::ios::in);
    int X, Y, SommetEntrant, SommetSortant;
    double PoidsArretes,PoidsSommet;
    std::string NomImage;


    if (f){

        f >> Graph::ordre;

        f >> Graph::nbrEdge;
        std::cout<< nbrEdge;
        for(int i=0 ; i < ordre ; i++){

        f >> PoidsSommet;
        f >> X;
        f >> Y;
        f >> NomImage;

        add_interfaced_vertex(i,PoidsSommet,X,Y,NomImage+".jpg");
        }
        for(int j=0 ; j < nbrEdge ; j++){

            f >> SommetEntrant;
            f >> SommetSortant;
            f >> PoidsArretes;
            add_interfaced_edge(j,SommetEntrant,SommetSortant,PoidsArretes);



        }


    f.close();
    }



}
void Graph::Charger_Edges(std::string NomDuGraph){
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::ifstream f(NomDuGraph+".txt",std::ios::in);
    int X, Y, SommetEntrant, SommetSortant;
    double PoidsArretes,PoidsSommet;
    std::string NomImage;


    if (f){

        f >> Graph::ordre;

        f >> Graph::nbrEdge;
        std::cout<< nbrEdge;
        for(int i=0 ; i < ordre ; i++){

        f >> PoidsSommet;
        f >> X;
        f >> Y;
        f >> NomImage;

        //add_interfaced_vertex(i,PoidsSommet,X,Y,NomImage+".jpg");
        }
        for(int j=nbrEdge ; j < nbrEdge*2 ; j++){

            f >> SommetEntrant;
            f >> SommetSortant;
            f >> PoidsArretes;
            add_interfaced_edge(j,SommetEntrant,SommetSortant,PoidsArretes);




        }


    f.close();
    }



}
void Graph::Sauvegarde(std::string NomDuGraph){

    std::ofstream f(NomDuGraph+".txt",std::ios::out | std::ios::trunc);
    std::string NomImage;
        if(f){
            f << Graph::ordre <<std::endl;
            f << Graph::nbrEdge<<std::endl;

            for(auto &elt : m_vertices){
         f << elt.second.m_value<<" ";
         f <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
         f <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
        NomImage=elt.second.m_interface->m_img.get_pic_name();
        NomImage.erase(NomImage.size()-4,4);
         f <<NomImage<<std::endl;
    }
        for(auto &elt : m_edges){

            f << elt.second.m_from<<" ";
            f << elt.second.m_to<<" ";
            f << elt.second.m_weight<<std::endl;

        }
        f.close();
        std::cout<<"Sauvegarde effectue avec succes !"<< std::endl;
        }

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(std::string NomDuGraph)
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();
    Boutonsgraph(NomDuGraph);
    Delete_vertex();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);


}
void Graph::detruire_graph()
{

    for(std::map<int,Vertex>::iterator it= m_vertices.begin(); it!=m_vertices.end();it++)
    {
        m_interface->m_main_box.remove_child(it->second.m_interface->m_top_box);

    }

    m_vertices.clear();

    for(std::map<int,Edge>::iterator et= m_edges.begin(); et!=m_edges.end();et++)
    {
        m_interface->m_main_box.remove_child(et->second.m_interface->m_top_edge);


    }
    m_edges.clear();

    m_interface.reset();
    m_interface=nullptr;


}
/// eidx index of edge to remove
void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge);  */
        /* m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );


    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

}

