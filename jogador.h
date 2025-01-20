#ifndef JOGADOR_H
#define JOGADOR_h
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <list> 
#include "tiro.h"
#define JOGADOR 1
#define OPONENTE 2
#define PROPORCAO 0.3
class Jogador {
    GLfloat x_init;
    GLfloat y_init;
    GLfloat x;
    GLfloat y;
    GLfloat size; 
    GLfloat total_size;
    GLfloat angle;
    GLfloat dim_proporcional;
    GLfloat bodyHeight;
    GLfloat bodyWidth;
    GLfloat arm_leg_Height;
    GLfloat arm_leg_Width;
    GLfloat dist2base;
    std::list<Tiro*> tiros;
    GLfloat tempoUltimoTiro;
    GLfloat tempoEntreTiros;
    GLfloat angle_left_leg1;
    GLfloat angle_right_leg1;
    GLfloat angle_left_leg2;
    GLfloat angle_right_leg2;

    
    

    private:
        void DesenhaCirc(GLfloat size, 
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
        void DesenhaJogador(GLfloat x, GLfloat y, GLfloat size, GLfloat angle);
        void DesenhaOponente(GLfloat x, GLfloat y, GLfloat size, GLfloat angle);
        Tiro* AtiraOponente();
        Tiro* AtiraJogador();

    public:
        GLfloat vel;
        int dir;
        bool oponente;
        bool morreu;
        bool oponente_dentro_visao;
        bool left_leg_up;
        Jogador(GLfloat x, GLfloat y, GLfloat size) {
            this->x = x;
            this->y = y;
            this->size = size;
            this->dir = 1;
            this->angle = -85;
            this->dim_proporcional = size*PROPORCAO;
            this->bodyHeight = this->dim_proporcional * 1.3;
            this->bodyWidth = this->dim_proporcional;
            this->arm_leg_Height = this->bodyHeight*0.8;
            this->arm_leg_Width = this->dim_proporcional*0.2;
            this->dist2base = size/2;
            this->total_size = this->dim_proporcional + this->bodyHeight + 2*this->arm_leg_Height;
            this->morreu = false;            
            this->oponente_dentro_visao = false;
            this->x_init = x;
            this->y_init = y;
            this->angle_left_leg1 = 30;
            this->angle_left_leg2 = 20;
            this->angle_right_leg1 = -30;
            this->angle_right_leg2 = 20;
            this->left_leg_up = true;
            this->vel = 0.05;
        }
        void Desenha(int tipo) {
            if (tipo == JOGADOR)
                DesenhaJogador(this->x, this->y, this->size, this->angle);
            else if (tipo == OPONENTE) {
                DesenhaOponente(this->x, this->y, this->size, this->angle);
            }
        }
        GLfloat MoveEmX(GLfloat dx, GLdouble timeDiference, bool jump_or_falling);
        GLfloat MoveEmY(GLfloat dy, GLdouble timeDiference);

        GLfloat getX() {
            return this->x - size*0.15;
        }
        GLfloat getY() {
            return this->y + size/2 - total_size;
        }
        void setY(GLfloat y) {
            this->y = y;
        }
        void setX(GLfloat x) {
            this->x = x;
        }
        GLfloat getWidth() {
            return this->size*0.3;
        }

        GLfloat getSize() {
            return this->total_size;
        }        

        void updateX(GLfloat x_arena) {
            this->x = this->x - x_arena;
            this->x_init = this->x;
        }
        void updateY(GLfloat y_arena) {
            this->y = this->y - y_arena;     
            this->y_init = this->y;       
        }

        GLfloat updateAngle(GLfloat angle) {
            this->angle += angle;
            return this->angle;
        }

        GLfloat getAngle() {
            return this->angle;
        }

        void addTiro(Tiro * tiro) {
            this->tiros.push_front(tiro);
        }

        std::list<Tiro*>& getTiros() {
            return this->tiros;
        }

        
        Tiro* Atira(int tipo) {
            if (tipo == JOGADOR) {
                return AtiraJogador();
            }
            else if (tipo == OPONENTE) {
                return AtiraOponente();
            }
            return NULL;
        }

        bool temTiro() {
            if (tiros.size() > 0) {
                return true;
            }
            else {
                return false;
            }
        }

        void DesenhaTiros();
        void UpdateTiros(GLfloat timeDifference);
        void updateAngleOponente(Jogador* jogador_principal, GLfloat view_width);

        void reiniciaPosicao() {
            this->x = this->x_init;
            this->y = this->y_init;
            this->morreu = false;
        }

        void updateAngulosPerna(GLfloat dx);


};





#endif