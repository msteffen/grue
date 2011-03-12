#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <Glut/glut.h>

#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

const double pi = 3.1415926535897932384626433832795;
const double halfpi = 1.570796326794897;
static double theta = 0, phi = pi, uphi = pi-1;
static int oldx, oldy;

void renderOrientation();

void initLighting() {
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {90.0};
 
    GLfloat position[4] = {7.0,-7.0,12.0,0.0};
    //GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
    GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
    GLfloat specular[4] = {1.0,1.0,1.0,1.0};
    
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

GLvoid doNothing() {
    glDrawBuffer(GL_FRONT_AND_BACK);
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0,800.0/600,1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(sin(phi)*cos(theta)*5, 5*cos(phi), sin(phi)*sin(theta)*5,
              0,0,0,
              (sin(phi)-sin(uphi))*cos(theta)*5,cos(phi)-cos(uphi),(sin(phi)-sin(uphi))*sin(theta)*5);

    glColor4f(1.0,1.0,0.0,1.0);
    static GLUquadric *quadric = gluNewQuadric();
    gluSphere(quadric, 1,10,10);

    glPushMatrix();
    glTranslatef(0,1,0);
    glColor3f(1,0,0);
    gluSphere(quadric, 0.5,10,10);
    glPopMatrix();


    renderOrientation();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    oldx = x;
    oldy = y;
}

void motion(int x, int y) {
    phi += (y - oldy)/50.0;
    theta += (x - oldx)/50.0;
    uphi += (y - oldy)/50.0;
    oldx = x;
    oldy = y;
    int iters = 100;
    while(iters && iters-- && theta > 2*pi) theta -= (2*pi);
    while(iters && iters-- && theta < 0)    theta += (2*pi);
    while(iters && iters-- && phi > 2*pi) phi -= (2*pi);
    while(iters && iters-- && phi < 0)    phi += 2*pi;
    while(iters && iters-- && uphi > 2*pi) uphi -= (2*pi);
    while(iters && iters-- && uphi < 0)    uphi += 2*pi;
}

void key(int c, int x, int y) {
    switch(c) {
      case 'q':
        exit(0);
    }
}

void renderOrientation() {
    static const int tx = 550, ty = 550, px = 500, py = 550;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glLoadIdentity();
    glOrtho(0,800,600,0,0,1);

    glColor4f(0.2,1.0,1.0,1.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
      glVertex2f(px,py);
      glVertex2f(px+30*cos(phi),py+30*sin(phi));
      glVertex2f(tx,ty);
      glVertex2f(tx+30*cos(theta),ty+30*sin(theta));
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // non-stereo for main window
    glutInitWindowPosition (300, 50);
    glutInitWindowSize (800, 600);
    glutCreateWindow("GLUT Basics");

    initLighting();
    glutDisplayFunc(doNothing);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    //glutPassiveMotionFunc(mouse);
    glutIdleFunc(doNothing);
    glutSpecialFunc(key);
    glutMainLoop();

    return 0;
}
