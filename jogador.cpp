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


void Jogador::DesenhaJogador(GLfloat x, GLfloat y, GLfloat size, GLfloat angle) {    

    glPushMatrix();
        glTranslatef(x, y+dist2base, 0); 


        glPushMatrix();
            glTranslatef(0, -total_size + dim_proporcional/2, 0); 
            DesenhaCirc(dim_proporcional, 0, 255, 0);  // desenha a cabeça

            glTranslatef(0,  dim_proporcional/2, 0);
            DesenhaRect(bodyHeight, bodyWidth, 0, 255, 0); // desenha o tronco


            glPushMatrix();
                glTranslatef(0, bodyHeight/2, 0);
                glRotatef(angle, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 255, 0); // desenha o braço
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(0, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(0, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(-30, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(60, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0);
            glPopMatrix();



        glPopMatrix();  


    glPopMatrix();
}



void Jogador::DesenhaOponente(GLfloat x, GLfloat y, GLfloat size) {
    

    glPushMatrix();
        glTranslatef(x, y+dist2base, 0); 

        glPushMatrix();
            glTranslatef(0, -total_size + dim_proporcional/2, 0); 
            DesenhaCirc(dim_proporcional, 255, 0, 0);  // desenha a cabeça

            glTranslatef(0,  dim_proporcional/2, 0);
            DesenhaRect(bodyHeight, bodyWidth, 255, 0, 0); // desenha o tronco


            glPushMatrix();
                glTranslatef(0, bodyHeight/2, 0);
                glRotatef(100, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 255, 0); // desenha o braço
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(30, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(30, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(-30, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(60, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);
            glPopMatrix();



        glPopMatrix();  


    glPopMatrix();
}


GLfloat Jogador::MoveEmX(GLfloat dx) {
    Jogador::x += dx; 
    return Jogador::x;  
}

GLfloat Jogador::MoveEmY(GLfloat dy) {
    Jogador::y += dy;    
    return Jogador::y;  
}

void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    xOut = cos(angle * M_PI/180)*x - sin(angle * M_PI/180)*y;
    yOut = sin(angle * M_PI/180)*x + cos(angle * M_PI/180)*y;
    
}

// glTranslatef(x, y+dist2base, 0); 
// glTranslatef(0, -total_size + dim_proporcional/2, 0); 
// glTranslatef(0,  dim_proporcional/2, 0);
// glTranslatef(0, bodyHeight/2, 0);

Tiro* Jogador::Atira() {
    

    GLfloat baseX = 0, baseY = 0;
    RotatePoint(baseX, baseY, angle, baseX, baseY);
    baseX += this->x;
    baseY += bodyHeight/2;
    baseY += dim_proporcional/2;
    baseY += -total_size + dim_proporcional/2;
    baseY += this->y + dist2base;

    GLfloat tiroX = 0, tiroY = arm_leg_Height;

    RotatePoint(tiroX, tiroY, angle, tiroX, tiroY);
    tiroX += this->x;
    tiroY += bodyHeight/2;
    tiroY += dim_proporcional/2;
    tiroY += -total_size + dim_proporcional/2;
    tiroY += this->y + dist2base;


    return new Tiro(tiroX, tiroY, 20);
}

