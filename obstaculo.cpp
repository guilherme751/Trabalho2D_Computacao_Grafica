#include "obstaculo.h"
#include <stdio.h>

/**
 * Desenha um retângulo.
 * A origem está no vértice inferior esquerdo.
*/
void Obstaculo::DesenhaRect(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B) {
    
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
    glEnd();  

}
/**
 * Desenha o obstáculo
*/
void Obstaculo::DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B) {

    
    glPushMatrix();
        glTranslatef(x, y, 0);
        DesenhaRect(height, width, R, G, B);
    glPopMatrix();

    
}