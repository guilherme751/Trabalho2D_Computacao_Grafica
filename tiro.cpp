#include "tiro.h"
#include <math.h>
#include <stdio.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (GLint angle = 0; angle < 360; angle += 20)
    {
        // Converte o ângulo de graus para radianos
        GLfloat rad = angle * (M_PI / 180.0);

        // Calcula as coordenadas x e y
        GLfloat x = radius * cos(rad);
        GLfloat y = radius * sin(rad);

        // Adiciona o ponto no círculo
        glVertex3f(x, y, 0);
    }

    glEnd();

}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y, GLfloat radius)
{
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glTranslatef(x, y, 0);
    DesenhaCirc(radius, 255, 255, 255);
    glPopMatrix();

}
// (x - gX, y - gY)
void Tiro::Move(GLdouble timeDifference)
{
    
    GLfloat dX = cos(directionAng * M_PI / 180.0);
    GLfloat dY = sin(directionAng * M_PI / 180.0);
   
    x = x + dX*vel;
    y = y + dY*vel;
   
}

