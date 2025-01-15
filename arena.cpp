#include "arena.h"
#include <stdio.h>

void Arena::DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
    glEnd();  
}

void Arena::DesenhaArena(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    
    glPushMatrix();
        
        glRotatef(180, 1, 0, 0);
        glPushMatrix();
            glTranslatef(x, y, 0);
            DesenhaRect(height, width, R, G, B);
        glPopMatrix();
        for (Obstaculo* obstaculo : this->obstaculos) {
                obstaculo->Desenha();
            }
        for (Jogador* oponente : this->oponentes) {
            if (!oponente->morreu)
                oponente->Desenha(OPONENTE);
        }
        this->jogador->Desenha(JOGADOR);

    glPopMatrix();
}

void Arena::printArena() {
    printf("Altura %f\nLargura: %f\n", this->height, this->width);
}

void Arena::AtualizaCoordenadas() {
    for (Obstaculo* obstaculo : obstaculos) {
        obstaculo->updateX(this->x);
        obstaculo->updateY(this->y);
    }

    for (Jogador* oponente : oponentes) {
        oponente->updateX(this->x);
        oponente->updateY(this->y);
    }

    this->jogador->updateX(this->x);
    this->jogador->updateY(this->y);

    this->x = 0;
    this->y = 0;

}