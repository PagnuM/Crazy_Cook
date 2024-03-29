#include "../includes/Mapa.h"
#include "../includes/Definiciones.h"
#include "../includes/Espacio.h"
#include "../includes/Heladera.h"
#include "../includes/Hornalla.h"
#include "../includes/Mesada.h"
#include "../includes/Mostrador.h"
#include "../includes/Rejilla.h"
#include "../includes/Suelo.h"
#include "../includes/Tacho.h"
#include <list>
#include <stdlib.h>
#include <time.h>
#include <vector>

Mapa::Mapa(std::vector<std::vector<int>> niv, std::vector<std::vector<int>> rot, sf::Texture *tMapa, ManejadorClientes *manCli) {
    //se inicializa la posicion de los tiles
    setLayout(niv, rot);
    fondo.setTexture(*tMapa);

    // assign le da el tamaño al vector
    espacios.assign(nivel.size(), std::vector<Espacio *>(nivel[0].size(), new Espacio()));

    music.openFromFile("resources/Sound/Sonido_Cocina.wav");
    music.setLoop(true);
    music.setVolume(40);
    // Le asigna un espacio a cada elemento
    std::list<IngredienteType> listaIngrediente = {
        IngredienteType::Lechuga,
        IngredienteType::Tomate,
        IngredienteType::PanAbajo,
        IngredienteType::PanArriba,
        IngredienteType::HamburgesaCruda};
    srand(time(NULL));
    sf::Vector2f texSize(32, 32);
    sf::Vector2i tamanioMapa(0, 0);
    for (int x = 0; x < nivel.size(); x++) {
        tamanioMapa.x += texSize.x;
        for (int y = 0; y < nivel[x].size(); y++) {
            if (x == 0)
                tamanioMapa.y += texSize.y;
            if (nivel[x][y] == TileType::Suelo) {
                //se crea un espacio de tipo suelo
                espacios[x][y] = (Espacio *)new class Suelo(sf::Vector2i(x, y), rotacion[x][y], texSize);
            } else if (nivel[x][y] == TileType::Mesada) {
                //se crea un espacio de tipo mesada
                class Mesada *s = new class Mesada(sf::Vector2i(x, y), rotacion[x][y], texSize);
                espacios[x][y] = (Espacio *)s;
            } else if (nivel[x][y] == TileType::Heladera) {
                IngredienteType tipo = *std::next(listaIngrediente.begin(), std::rand() % listaIngrediente.size());
                listaIngrediente.remove(tipo);
                sf::Texture *tex = new sf::Texture();
                if (tipo == IngredienteType::Lechuga)
                    tex->loadFromFile("resources/Imagenes/Lechuga_Hoja.png");
                else if (tipo == IngredienteType::Tomate)
                    tex->loadFromFile("resources/Imagenes/Tomate_Rodaja.png");
                else if (tipo == IngredienteType::PanAbajo)
                    tex->loadFromFile("resources/Imagenes/Pan_Abajo.png");
                else if (tipo == IngredienteType::PanArriba)
                    tex->loadFromFile("resources/Imagenes/Pan_Arriba.png");
                else if (tipo == IngredienteType::HamburgesaCruda)
                    tex->loadFromFile("resources/Imagenes/Hamburguesa_Cruda.png");

                Ingrediente *ingr = new Ingrediente(sf::Vector2f(x, y), 90 * rotacion[x][y], tex, tipo);
                class Heladera *s = new class Heladera(sf::Vector2i(x, y), rotacion[x][y], texSize, ingr);
                espacios[x][y] = (Espacio *)s;
            } else if (nivel[x][y] == TileType::Tacho) {
                class Tacho *s = new class Tacho(sf::Vector2i(x, y), rotacion[x][y], texSize);
                espacios[x][y] = (Espacio *)s;
            } else if (nivel[x][y] == TileType::Hornalla) {
                class Hornalla *s = new class Hornalla(sf::Vector2i(x, y), rotacion[x][y], texSize, this);
                espacios[x][y] = (Espacio *)s;
            } else if (nivel[x][y] == TileType::Rejilla) {
                class Rejilla *s = new class Rejilla(sf::Vector2i(x, y), rotacion[x][y], texSize);
                espacios[x][y] = (Espacio *)s;
            } else if (nivel[x][y] == TileType::Mostrador) {
                class Mostrador *s = new class Mostrador(sf::Vector2i(x, y), rotacion[x][y], texSize, manCli);
                espacios[x][y] = (Espacio *)s;
            }
        }
    }
    MAPWIDTH = tamanioMapa.x;
    MAPHEIGHT = tamanioMapa.y;
}
void Mapa::actualizarIngPresentes(IngredienteType ing, bool agregado) {
    bool encontrado = false;
    std::list<IngredienteType>::iterator itIngrediente;
    int i = 0;
    for (itIngrediente = ingPresentes.begin(); itIngrediente != ingPresentes.end() && !encontrado; itIngrediente++) {
        if (*itIngrediente == ing) {
            encontrado = true;
            if (!agregado) {
                std::list<int>::iterator it = cantIngPresentes.begin();
                std::advance(it, i);
                *it -= 1;
                if (*it == 0) {
                    ingPresentes.remove(*itIngrediente);
                    cantIngPresentes.erase(it);
                }
            } else {
                std::list<int>::iterator it = cantIngPresentes.begin();
                std::advance(it, i);
                *it += 1;
            }
        }
        i++;
    }
    if (!encontrado && agregado) {
        ingPresentes.push_back(ing);
        cantIngPresentes.push_back(1);
    }
}
std::list<IngredienteType> *Mapa::getIngPresentes() {
    return &ingPresentes;
}

Mapa::~Mapa() {
    for (int x = 0; x < nivel.size(); x++)
        for (int y = 0; y < nivel[x].size(); y++)
            delete getEspacioAt(x, y);
}

void Mapa::dibujar(sf::RenderWindow *w) {
    w->draw(fondo);
    for (int x = 0; x < nivel.size(); x++)
        for (int y = 0; y < nivel[x].size(); y++)
            getEspacioAt(x, y)->dibujar(w);
}

Espacio *Mapa::getEspacioAt(int x, int y) {
    return espacios[x][y];
}

void Mapa::setLayout(std::vector<std::vector<int>> niv, std::vector<std::vector<int>> rot) {
    nivel = niv;
    rotacion = rot;
}
void Mapa::playMusic(bool play) {
    if (play)
        music.play();
}

int Mapa::getAncho() {
    return nivel.size();
}
int Mapa::getAlto() {
    return nivel[0].size();
}
