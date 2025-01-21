#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 0.5

class Tiro {
    GLfloat XInit; 
    GLfloat YInit; 
    GLfloat x; 
    GLfloat y; 
    GLfloat directionAng;
    GLfloat vel;

private:
    void DesenhaCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y, GLfloat radius);
public:
    GLfloat radius;
    bool desenhado;
    
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng){
        this->XInit = x; 
        this->YInit = y; 
        this->x = x; 
        this->y = y; 
        this->directionAng = directionAng; 
        this->vel = 0.037;
        this->desenhado = false;
        this->radius = radiusTiro;
    };
    void Desenha(){ 
        DesenhaTiro(this->x, this->y, this->radius);
    };
    void Move(GLdouble timeDifference);
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = this->x;
        yOut = this->y;
    };

    GLfloat getX() {
        return this->x;
    }

    GLfloat getY() {
        return this->y;
    }

    
};

#endif	/* TIRO_H */
