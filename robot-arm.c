#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415

GLint WIDTH =800;
GLint HEIGHT=600;

static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLfloat tetaxz=0;
GLfloat raioxz=6;

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

  /* origem posicionada no ombro */
  glTranslatef (-1.0, 0.0, 0.0);
  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

  /* origem posicionada no centro do braco */ 
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glColor3f(0.0, 0.0, 128.0);
  glutSolidCube (1.0);
  glPopMatrix();
   
  /* origem posicionada no cotovelo */
  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glColor3f(0.0, 191.0, 255.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo1 */
	glTranslatef (1.0, 0.0, 0.0);	
	glPushMatrix();
  glTranslatef (0.0, -0.2, 0.0);
  glRotatef ((GLfloat) finger1, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
  glScalef (0.5, 0.1, 0.33);
  glColor3f(72.0, 61.0, 139.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo2 */
  glTranslatef (0.0, 0.2, 0.0);
	glPushMatrix();
	glTranslatef (0.0, 0.0, 0.25);
  glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
   glColor3f(72.0, 61.0, 139.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo3 */
	glTranslatef (0.0, 0.0, -0.25);
  glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
   glColor3f(72.0, 61.0, 139.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,30.0);
  glMatrixMode(GL_MODELVIEW);
}

void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'a':
    shoulder = (shoulder + 5) % 360;
    glutPostRedisplay();
    break;
  case 'A':
    shoulder = (shoulder - 5) % 360;
    glutPostRedisplay();
    break;
  case 's':
    elbow = (elbow + 5) % 360;
    glutPostRedisplay();
    break;
  case 'S':
    elbow = (elbow - 5) % 360;
    glutPostRedisplay();
    break;
  case 'd':
    finger1 = (finger1 + 5) % 360;
    glutPostRedisplay();
    break;
  case 'D':
    finger1 = (finger1 - 5) % 360;
    glutPostRedisplay();
    break;
  case 'f':
    finger2 = (finger2 + 5) % 360;
    glutPostRedisplay();
    break;
  case 'F':
    finger2 = (finger2 - 5) % 360;
    glutPostRedisplay();
    break;
  case 'g':
    finger3 = (finger3 + 5) % 360;
    glutPostRedisplay();
    break;
  case 'G':
    finger3 = (finger3 - 5) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char** argv){
   
  glutInitWindowPosition(0, 0);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_ALPHA);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutCreateWindow ("GARRA");
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}