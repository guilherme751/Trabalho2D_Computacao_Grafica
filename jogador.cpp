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
    GLfloat bodyHeight = size; // Height of the torso (relative to the head size)
    GLfloat bodyWidth = size * 0.5; // Width of the torso
    GLfloat limbLength = size;      // Length of arms and legs
    GLfloat limbWidth = size * 0.2; // Width of arms and legs

    glPushMatrix();
        // Translate the entire player to the specified position
        glTranslatef(x, y, 0); // Negate Y because the arena is rotated on the X-axis

        // Draw the head (circle)
        glPushMatrix();
            glTranslatef(0, -size*4, 0); // Adjust position above the torso
            DesenhaCirc(size / 2, 0, 255, 0); // Head in green

        // Draw the torso (rectangle)
            glTranslatef(0, size/2, 0);
            DesenhaRect(bodyHeight, bodyWidth, 0, 255, 0); // Torso in green
        glPopMatrix();  

        // // Draw the right arm
        // glPushMatrix();
        //     glTranslatef(bodyWidth / 2, -(bodyHeight / 2), 0); // Attach to the right shoulder
        //     glRotatef(45, 0, 0, 1);                          // Rotate downward at an angle
        //     DesenhaRect(limbLength, limbWidth, 255, 255, 0); // Arm in yellow
        // glPopMatrix();

        // // Draw the left arm
        // glPushMatrix();
        //     glTranslatef(-bodyWidth / 2, -(bodyHeight / 2), 0); // Attach to the left shoulder
        //     glRotatef(-45, 0, 0, 1);                           // Rotate downward at an angle
        //     DesenhaRect(limbLength, limbWidth, 255, 255, 0);   // Arm in yellow
        // glPopMatrix();

        // // Draw the right leg
        // glPushMatrix();
        //     glTranslatef(bodyWidth / 4, bodyHeight / 2, 0); // Attach to the right hip
        //     glRotatef(-45, 0, 0, 1);                       // Rotate outward at an angle
        //     DesenhaRect(limbLength, limbWidth, 255, 0, 0); // Leg in red
        // glPopMatrix();

        // // Draw the left leg
        // glPushMatrix();
        //     glTranslatef(-bodyWidth / 4, bodyHeight / 2, 0); // Attach to the left hip
        //     glRotatef(45, 0, 0, 1);                         // Rotate outward at an angle
        //     DesenhaRect(limbLength, limbWidth, 255, 0, 0);  // Leg in red
        // glPopMatrix();

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
