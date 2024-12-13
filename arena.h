#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "obstaculo.h"
#include <vector>

class Arena {
    GLfloat height;
    GLfloat width;
    GLfloat x;  
    GLfloat y;  
    std::vector<Obstaculo> obstaculos;


    private:
        void DesenhaRect(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaArena(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);

    public:
        Arena(GLfloat height, GLfloat width, GLfloat x, GLfloat y) {
            this->height = height;
            this->width = width;
            this->x = x;
            this->y = y;
        };
        void Desenha() {
            DesenhaArena(this->x, this->y, this->height, this->width, 0, 0, 255);
        }; 

        void printArena();
        GLfloat getHeight() {
            return this->height;
        }

        void addObstaculo(GLfloat height, GLfloat width, GLfloat x, GLfloat y) {
            Obstaculo obstaculo = Obstaculo(height, width, x, y);
            this->obstaculos.push_back(obstaculo);
        }


};



#endif /* ARENA_H */