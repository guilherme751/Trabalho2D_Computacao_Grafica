#include "arena.h"
#include <stdio.h>

void Arena::DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height/2);
        glVertex2f(0, -height/2);
        glVertex2f(width, -height/2);
        glVertex2f(width, height/2);
    glEnd();

}



void Arena::DesenhaArena(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(180, 0, 0, 1);
        glRotatef(180, 0, 1, 0);

        DesenhaRect(height, width, R, G, B);
        for (Obstaculo obstaculo : this->obstaculos) {
            obstaculo.Desenha();
        }
    glPopMatrix();

}

void Arena::printArena() {
    printf("Altura %f\nLargura: %f\n", this->height, this->width);
}