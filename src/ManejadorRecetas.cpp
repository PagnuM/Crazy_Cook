#include "../includes/ManejadorRecetas.h"
#include <algorithm>
#include <fstream>
#include <iostream>

ManejadorRecetas::ManejadorRecetas() {
}
ManejadorRecetas::ManejadorRecetas(std::string path) {
    pathArchivo = path;
}
ManejadorRecetas::~ManejadorRecetas() {
}
std::list<Plato> ManejadorRecetas::listarPlatos() {
    std::list<Plato> listaPlatos;
    std::ifstream inArchivo(pathArchivo);
    // Lee el archivo
    if (inArchivo.is_open()) {
        // Loopea por todo el archivo
        while (!inArchivo.eof()) {
            std::string lineaLeer;
            getline(inArchivo, lineaLeer);
            if (lineaLeer != "") {
                Plato *p = new Plato();
                int numEspacios = std::count(lineaLeer.begin(), lineaLeer.end(), ' ');
                int index = 0;
                for (int i = 0; i < lineaLeer.size() - numEspacios; i++) {
                    IngredienteType tipoIng = (IngredienteType)std::stoi(lineaLeer.substr(index, 1));
                    Ingrediente ing = Ingrediente(tipoIng);
                    p->pushIngrediente(ing);
                    index += 2;
                }
                listaPlatos.push_back(*p);
            }
        }
        inArchivo.close();
    } else {
        throw "Error al abrir el archivo";
    }
    return listaPlatos;
}

/**
@param indice El indice de 0 hasta tamanio-1
@return Plato con ese indice
*/
Plato ManejadorRecetas::getPlato(int indice) {
    return *std::next(listarPlatos().begin(), indice);
}

int ManejadorRecetas::getCantidadPlatos() {
    std::ifstream inArchivo(pathArchivo);
    int lin = 0;
    if (inArchivo.is_open()) {
        while (!inArchivo.eof()) {
            std::string lineaLeer;
            getline(inArchivo, lineaLeer);
            if (lineaLeer != "") {
                lin++;
            }
        }
        inArchivo.close();
    } else {
        throw "Error al abrir el archivo";
    }
    return lin;
}

void ManejadorRecetas::setPath(std::string path) {
    pathArchivo = path;
}
