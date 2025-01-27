#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <GL/gl.h>
#include <GL/glu.h>


class Obstaculo {
    GLfloat height;
    GLfloat width;

    private:
        void DesenhaRect(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
       

    public:
        GLfloat x_init;
        GLfloat y_init;
        GLfloat x;  
        GLfloat y; 
        Obstaculo(GLfloat height, GLfixed width, GLfloat x, GLfloat y) {
            this->height = height;
            this->width = width;
            this->x = x;
            this->y = y;
            this->x_init = x;
            this->y_init = y;
        }

        void Desenha() {
            DesenhaObstaculo(this->x, this->y, this->height, this->width, 0, 0, 0);
        }

        void updateX(GLfloat x_arena) {
            this->x = this->x - x_arena;
        }
        void updateY(GLfloat y_arena) {
            this->y = this->y - y_arena;
        }

        GLfloat getHeight() {
            return this->height;
        }
        GLfloat getWidth() {
            return this->width;
        }
        
};






#endif
