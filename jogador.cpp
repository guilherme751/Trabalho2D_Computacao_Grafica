#include "jogador.h"
#include <math.h>
#include <stdio.h>

void Jogador::DesenhaCirc(GLfloat size, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (GLint angle = 0; angle < 360; angle += 20)
    {
        // Converte o ângulo de graus para radianos
        GLfloat rad = angle * (M_PI / 180.0);

        // Calcula as coordenadas x e y
        GLfloat x = size/2 * cos(rad);
        GLfloat y = size/2 * sin(rad);

        // Adiciona o ponto no círculo
        glVertex3f(x, y, 0);
    }

    glEnd();
}
void Jogador::DesenhaJogador(GLfloat x, GLfloat y, GLfloat size) {
    glPushMatrix();
        glRotatef(180, 1, 0, 0);
        glTranslatef(x, y, 0);
        DesenhaCirc(size, 0, 255, 0);
    glPopMatrix();
}


void Jogador::DesenhaOponente(GLfloat x, GLfloat y, GLfloat size) {
    glPushMatrix();
        glRotatef(180, 1, 0, 0);
        glTranslatef(x, y, 0);
        DesenhaCirc(size, 255, 0, 0);
    glPopMatrix();
}