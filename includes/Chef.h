#ifndef CHEF_H
#define CHEF_H
#include "../includes/Agarrable.h"
#include "../includes/Definiciones.h"
#include "../includes/Mapa.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Chef {
private:
    float desaceleracionCaminar, aceleracionCaminar, desaceleracionCorrer, aceleracionCorrer, angulo;
    sf::RectangleShape rectShape;
    sf::RectangleShape hitbox;
    sf::Vector2f velocidad;
    sf::Vector2f velocidadCorrer;
    sf::Vector2f velocidadCaminar;
    Agarrable *enMano;
    sf::Clock dtInteraccion;
    sf::Clock dtCorrer;
    void actualizar(Mapa *map);
    void actualizarAtributos();
    void actualizarColisiones(Mapa *map);
	sf::Sound sonidoMesada;
	sf::Sound sonidoMostrador;
	sf::Sound sonidoPlato;
	sf::Sound sonidoTacho;
	sf::Sound sonidoHeladera;
	sf::SoundBuffer bufferMesada;
	sf::SoundBuffer bufferMostrador;
	sf::SoundBuffer bufferPlato;
	sf::SoundBuffer bufferTacho;
	sf::SoundBuffer bufferHeladera;

public:
    Chef(sf::Texture *tex, int x, int y);
    void dibujar(sf::RenderWindow *w, Mapa *map);
    void mover(bool izq, bool der, bool arriba, bool abajo, bool correr);
    sf::RectangleShape getRectangleShape();
    sf::RectangleShape getHitbox();
    void interactuar(bool interactuar, Mapa *map);
};

#endif // CHEF_H
