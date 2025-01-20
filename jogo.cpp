#include "jogo.h"
#include "tinyxml2.h"

using namespace tinyxml2;


void Jogo::CarregarArquivoSVG(const char* caminho) {
    XMLDocument doc;

    if (doc.LoadFile(caminho) != XML_SUCCESS) {
        std::cerr << "Error when opening SVG file" << std::endl;
        return; 
    }

    XMLElement* svg = doc.FirstChildElement("svg");

    if (!svg) {
        std::cerr << "<svg> element not found!" << std::endl;
        return;
    }

    for (XMLElement* element = svg->FirstChildElement(); element; element = element->NextSiblingElement()) {
        const char* tag = element->Name();

        if (strcmp(tag, "rect") == 0) {
            const char* fill = element->Attribute("fill");
            if (fill && std::string(fill) == "blue") {
                GLfloat x = element->FloatAttribute("x");
                GLfloat y = element->FloatAttribute("y");
                GLfloat width = element->FloatAttribute("width");
                GLfloat height = element->FloatAttribute("height");
                this->arena = new Arena(height, width, x, y);
            }
            else if (fill && std::string(fill) == "black") {
                GLfloat x = element->FloatAttribute("x");
                GLfloat y = element->FloatAttribute("y");
                GLfloat width = element->FloatAttribute("width");
                GLfloat height = element->FloatAttribute("height");
                this->arena->addObstaculo(height, width, x, y);
            }
        }
        else if (strcmp(tag, "circle") == 0) {
            const char* fill = element->Attribute("fill");
            if (fill && std::string(fill) == "green") {
                GLfloat x = element->FloatAttribute("cx");
                GLfloat y = element->FloatAttribute("cy");
                GLfloat raio = element->FloatAttribute("r");
                Jogador* jogador = new Jogador(x, y, raio*2);
                jogador->oponente = false;
                this->arena->setJogador(jogador);
            }
            else if (fill && std::string(fill) == "red") {
                GLfloat x = element->FloatAttribute("cx");
                GLfloat y = element->FloatAttribute("cy");
                GLfloat raio = element->FloatAttribute("r");
                Jogador* jogador = new Jogador(x, y, raio*2);
                jogador->oponente = true;
                this->arena->addOponente(x, y, raio*2);
            }

        }



    }
}

void Jogo::DesenhaJogo(Arena* arena) {
    if (teste)  arena->teste = true;
    if (arena) {
        arena->Desenha(); // Desenha a arena
    }

}

