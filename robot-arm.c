#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0;

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  /* origem posicionada no ombro */
  glTranslatef (-1.0, 0.0, 0.0);
  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

  /* origem posicionada no centro do braco */ 
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();
   
  /* origem posicionada no cotovelo */
  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo1 */
	glTranslatef (1.0, 0.0, 0.0);	
	glPushMatrix();
  glTranslatef (0.0, -0.2, 0.0);
  glRotatef ((GLfloat) finger1, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
  glutWireCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo2 */
  glTranslatef (0.0, 0.2, 0.0);
	glPushMatrix();
	glTranslatef (0.0, 0.0, 0.25);
  glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
  glutWireCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo3 */
	glTranslatef (0.0, 0.0, -0.25);
  glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
  glutWireCube (1.0);
  glPopMatrix();

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -10.0);
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
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 600); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}