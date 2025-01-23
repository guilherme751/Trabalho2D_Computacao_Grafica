#include "jogador.h"
#include <math.h>
#include <stdio.h>
#include <random>

GLfloat distanciaEntrePontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    GLfloat dx = x2 - x1;
    GLfloat dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

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
                glRotatef(this->angle_left_leg1, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0); // parte superior da perna esquerda

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(this->angle_left_leg2, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0); // parte inferior da perna esquerda
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(this->angle_right_leg1, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0); // parte superior da perna direita

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(this->angle_right_leg2, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 0, 0); // parte inferior da perna direita
            glPopMatrix();



        glPopMatrix();  


    glPopMatrix();
}



void Jogador::DesenhaOponente(GLfloat x, GLfloat y, GLfloat size, GLfloat angle) {
    

    glPushMatrix();
        glTranslatef(x, y+dist2base, 0); 

        glPushMatrix();
            glTranslatef(0, -total_size + dim_proporcional/2, 0); 
            DesenhaCirc(dim_proporcional, 255, 0, 0);  // desenha a cabeça

            glTranslatef(0,  dim_proporcional/2, 0);
            DesenhaRect(bodyHeight, bodyWidth, 255, 0, 0); // desenha o tronco


            glPushMatrix();
                glTranslatef(0, bodyHeight/2, 0);
                glRotatef(angle, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 255, 255, 0); // desenha o braço
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(this->angle_left_leg1, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(this->angle_left_leg2, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, bodyHeight, 0);
                glRotatef(this->angle_right_leg1, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);

                glTranslatef(0, arm_leg_Height, 0);
                glRotatef(this->angle_right_leg2, 0, 0, 1);
                DesenhaRect(arm_leg_Height, arm_leg_Width, 0, 255, 0);
            glPopMatrix();



        glPopMatrix();  


    glPopMatrix();
}

void Jogador::updateAngulosPerna(GLfloat dx) {    
        if (this->left_leg_up) {
            this->angle_left_leg1 -= 4*dx;
            this->angle_right_leg1 += 4*dx;


            // this->angle_left_leg2 -= 1;
            
            // this->angle_right_leg2 -= 0.2;

            if (this->angle_left_leg1 < -36 && this->angle_right_leg1 > 36 ) {
                this->left_leg_up = false;       
            }
        } else {
            
            this->angle_right_leg1 -= 4*dx;
            // this->angle_right_leg2 -= 0.2;
            this->angle_left_leg1 += 4*dx;
            // this->angle_left_leg2 -= 0.2;
            if (this->angle_right_leg1 < -36 && this->angle_left_leg1 > 36 ) {
                this->left_leg_up  = true;     
            }

        }   

}

GLfloat Jogador::MoveEmX(GLfloat dx, GLdouble timeDiference, bool jump_or_falling) {
    if (timeDiference > 100)    timeDiference = 1;
    if (!jump_or_falling)
        updateAngulosPerna(timeDiference * this->vel);
    Jogador::x += dx * timeDiference * this->vel;
    return Jogador::x;  
}

GLfloat Jogador::MoveEmY(GLfloat dy, GLdouble timeDiference) {
    if (timeDiference > 100)    timeDiference = 1;
    Jogador::y += dy * timeDiference * this->vel;    
    return Jogador::y;  
}

void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    xOut = cos(angle * M_PI/180)*x - sin(angle * M_PI/180)*y;
    yOut = sin(angle * M_PI/180)*x + cos(angle * M_PI/180)*y;    
}



Tiro* Jogador::AtiraJogador() {
    

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


    return new Tiro(tiroX, tiroY, atan2(tiroY-baseY, tiroX-baseX) * 180.0 / M_PI);
}
std::random_device rd;  // Fonte de aleatoriedade
std::mt19937 gen(rd()); // Gerador de números aleatórios
std::uniform_real_distribution<float> dist(0.0, 1.0); 

Tiro* Jogador::AtiraOponente() {
    
    float randomNumber = dist(gen);
    if (randomNumber < 0.05 && this->oponente_dentro_visao && !this->morreu) {
    
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


        return new Tiro(tiroX, tiroY, atan2(tiroY-baseY, tiroX-baseX) * 180.0 / M_PI);
    } else {
        return NULL;
    }
}

void Jogador::DesenhaTiros(){
    for (Tiro* tiro : tiros) {       
        tiro->Desenha();       
    }
}

void Jogador::UpdateTiros(GLfloat timeDifference) {

    for (Tiro* tiro : tiros) {
        tiro->Move(timeDifference);
    }
}
GLfloat normalizaAngulo(GLfloat angulo) {
    while (angulo < 0) angulo += 360;
    while (angulo >= 360) angulo -= 360;
    return angulo;
}
void Jogador::updateAngleOponente(Jogador* jogador_principal, GLfloat view_width) {
    if (this->x - jogador_principal->x  <= view_width/1.9) {
            this->oponente_dentro_visao = true;
            GLfloat angle_temp = atan2(jogador_principal->y - this->y, jogador_principal->x - this->x)* 180.0/M_PI - 90;
            angle_temp = normalizaAngulo(angle_temp);
            
            if (angle_temp < 40) {
                angle_temp = 40;
            } else if (angle_temp > 130) {
                angle_temp = 130;
            }    

            this->angle = angle_temp;        
    }
    else {
        this->oponente_dentro_visao = false;
    }
    
    
}





