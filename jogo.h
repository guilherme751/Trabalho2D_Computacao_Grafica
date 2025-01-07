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
        void CarregarArquivoSVG(const char* caminho);
        void Desenha() {
            DesenhaJogo(this->arena);
        };

        GLfloat getArenaHeight() {
            return this->arena->getHeight();
        }   

        Arena* getArena() {
            return this->arena;
        }
       
};

#endif