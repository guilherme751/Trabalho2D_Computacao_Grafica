#include "obstaculo.h"
#include <stdio.h>


void Obstaculo::DesenhaRectVertical(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B) {
    
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
    glEnd();  

}

void Obstaculo::DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B) {

    
    glPushMatrix();
        glRotatef(180, 1, 0, 0);
        glTranslatef(x, y, 0);
        DesenhaRectVertical(height, width, R, G, B);
    glPopMatrix();

    
}