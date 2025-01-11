#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "obstaculo.h"
#include <vector>
#include "jogador.h"
class Arena {
    GLfloat height;
    GLfloat width;
    GLfloat x;  
    GLfloat y;  
    std::vector<Obstaculo*> obstaculos;
    Jogador* jogador;
    std::vector<Jogador*> oponentes;


    private:
        void DesenhaRect(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaArena(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);

    public:
        Arena(GLfloat height, GLfloat width, GLfloat x, GLfloat y) {
            this->height = height;
            this->width = width;
            this->x = x;
            this->y = y;
        };
        void Desenha() {
            DesenhaArena(this->x, this->y, this->height, this->width, 0, 0, 255);
        }; 

        void AtualizaCoordenadas();
        void printArena();
        GLfloat getHeight() {
            return this->height;
        }
        GLfloat getWidth() {
            return this->width;
        }

        std::vector<Obstaculo*> getObstaculos() {
            return this->obstaculos;
        }

        void addObstaculo(GLfloat height, GLfloat width, GLfloat x, GLfloat y) {
            Obstaculo* obstaculo = new Obstaculo(height, width, x, y);
            this->obstaculos.push_back(obstaculo);
        }

        void addOponente(GLfloat x, GLfloat y, GLfloat size) {
            Jogador* oponente = new Jogador(x, y, size);
            this->oponentes.push_back(oponente);
        }

        void setJogador(Jogador* jogador) {
            this->jogador = jogador;
        }
        Jogador* getJogador() {
            return this->jogador;
        }

        GLfloat getX() {
            return this->x;
        }

        GLfloat getY() {
            return this->y;
        }

        std::vector<Jogador*> getOpponents() {
            return this->oponentes;
        }



};



#endif /* ARENA_H */