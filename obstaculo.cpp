#include "obstaculo.h"



void Obstaculo::DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height/2);
        glVertex2f(0, -height/2);
        glVertex2f(width, -height/2);
        glVertex2f(width, height/2);
    glEnd();

}

void Obstaculo::DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B) {

    
    glPushMatrix();
        glTranslatef(x, y, 0);
        DesenhaRect(height, width, R, G, B);
    glPopMatrix();

    
}