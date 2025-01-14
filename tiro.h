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
    void DesenhaTiro(GLfloat x, GLfloat y);
public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng){
        this->x = x; 
        this->y = y; 
        this->x = x; 
        this->y = y; 
        this->directionAng = directionAng; 
        this->vel = 5;
    };
    void Desenha(){ 
        DesenhaTiro(this->x, this->y);
    };
    void Move(GLdouble timeDifference);
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = this->x;
        yOut = this->y;
    };

    
};

#endif	/* TIRO_H */
