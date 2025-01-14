#ifndef JOGADOR_H
#define JOGADOR_h
#include <GL/gl.h>
#include <GL/glu.h>
#include <list> 
#include "tiro.h"
#define JOGADOR 1
#define OPONENTE 2
#define PROPORCAO 0.3
class Jogador {
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
    

    private:
        void DesenhaCirc(GLfloat size, 
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
        void DesenhaJogador(GLfloat x, GLfloat y, GLfloat size, GLfloat angle);
        void DesenhaOponente(GLfloat x, GLfloat y, GLfloat size);

    public:
        int dir;
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

        }
        void Desenha(int tipo) {
            if (tipo == JOGADOR)
                DesenhaJogador(this->x, this->y, this->size, this->angle);
            else if (tipo == OPONENTE) {
                DesenhaOponente(this->x, this->y, this->size);
            }
        }
        GLfloat MoveEmX(GLfloat dx);
        GLfloat MoveEmY(GLfloat dy);

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
        }
        void updateY(GLfloat y_arena) {
            this->y = this->y - y_arena;            
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

        
        Tiro* Atira();

        bool temTiro() {
            if (tiros.size() > 0) {
                return true;
            }
            else {
                return false;
            }
        }



};





#endif