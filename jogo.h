#ifndef JOGO_H
#define JOGO_H
#include "arena.h"
#include <stdio.h>
#include <iostream>


class Jogo {

    Arena* arena; 
      

    private:
        void DesenhaJogo(Arena* arena);
    public:
        bool gameOver = false;
        bool vitoria = false;
        bool reiniciar = false;
        bool teste = false;
        void CarregarArquivoSVG(const char* caminho);
        void Desenha() {
            DesenhaJogo(this->arena);
        };

        GLfloat getArenaHeight() {
            return this->arena->getHeight();
        }  
        GLfloat getArenaWidth() {
            return this->arena->getWidth();
        }   

        Arena* getArena() {
            return this->arena;
        }
       
};

#endif