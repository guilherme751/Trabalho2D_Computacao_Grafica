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
        glTranslatef(-x, y, 0);
        glRotatef(180, 1, 0, 0);
        glPushMatrix();
            glTranslatef(x, y, 0);
            DesenhaRect(height, width, R, G, B);
        glPopMatrix();
        for (Obstaculo obstaculo : this->obstaculos) {
                obstaculo.Desenha();
            }
        this->jogador->Desenha(JOGADOR);

        for (Jogador oponente : this->oponentes) {
            oponente.Desenha(OPONENTE);
        }
    glPopMatrix();
}

void Arena::printArena() {
    printf("Altura %f\nLargura: %f\n", this->height, this->width);
}