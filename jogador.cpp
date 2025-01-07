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

void Jogador::DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    glEnd(); 
}



void Jogador::DesenhaJogador(GLfloat x, GLfloat y, GLfloat size) {
    size = size*0.6;
    GLfloat bodyHeight = size * 1.3; 
    GLfloat bodyWidth = size * 0.8; 
    GLfloat armHeight = bodyHeight*0.8;
    GLfloat armWidth = size*0.2;

    glPushMatrix();
        glTranslatef(x, y, 0); 

        glPushMatrix();
            glTranslatef(0, -size*3, 0); 
            DesenhaCirc(size, 0, 255, 0);  // desenha a cabeça

            glTranslatef(0,  size/2, 0);
            DesenhaRect(bodyHeight, bodyWidth, 0, 255, 0); // desenha o tronco


            glPushMatrix();
                glTranslatef(0, bodyHeight/2, 0);
                glRotatef(-100, 0, 0, 1);
                DesenhaRect(armHeight, armWidth, 255, 255, 0); // desenha o braço
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(30, 0, 0, 1);
                DesenhaRect(armHeight, armWidth, 255, 0, 0);

                glTranslatef(0, armHeight, 0);
                glRotatef(30, 0, 0, 1);
                DesenhaRect(armHeight, armWidth, 255, 0, 0);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(-30, 0, 0, 1);
                DesenhaRect(armHeight, armWidth, 255, 0, 0);

                glTranslatef(0, armHeight, 0);
                glRotatef(60, 0, 0, 1);
                DesenhaRect(armHeight, armWidth, 255, 0, 0);
            glPopMatrix();



        glPopMatrix();  


    glPopMatrix();
}



void Jogador::DesenhaOponente(GLfloat x, GLfloat y, GLfloat size) {
    glPushMatrix();
        // glRotatef(180, 1, 0, 0);
        glTranslatef(x, y, 0);
        DesenhaCirc(size, 255, 0, 0);
    glPopMatrix();
}


void Jogador::MoveEmX(GLfloat dx) {
    Jogador::x += dx;    
}

void Jogador::MoveEmY(GLfloat dy) {
    Jogador::y += dy;    
}

