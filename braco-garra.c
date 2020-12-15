#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "png_texture.h"

/*
Codigo feito para a disciplina de Computacao Grafica - Semestre 2020.6
Projeto: Braco robotico 3D controlavel e com articulacoes
Controles:
- 'a' e 'A': Rotacoes no "ombro" do braco
- 's' e 'S': Rotacoes no "cotovelo" do braco
- 'd' e 'D': Rotacoes no dedo inferior do braco
- 'f' e 'F': Rotacoes no dedo direito do braco
- 'g' e 'G': Rotacoes no dedo esquerdo do braco
- 'r' e 'R': Altera raio de rotacao na posicao da camera
- 'UP', 'DOWN', 'LEFT' e 'RIGHT': Rotacionam camera
*/
#define PI 3.1415

#define COORD_TEXTURA_BRACO 1.0
#define COR_DO_BRACO 0.24,0.24,0.24,1.0
#define TEXTURA_DO_BRACO "metal.png"

#define COORD_TEXTURA_PLANO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define TEXTURA_DO_PLANO "montanhas.png"

GLint WIDTH =800;
GLint HEIGHT=600;

static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLuint  textura_plano;
GLuint textura_braco;

GLshort texturas=0;
GLfloat tetaxz=0;
GLfloat raioxz=6;
GLuint braco;

GLfloat ctp[4][2]={
  {-COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO},
  {-COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO}
};

void compoe_braco(void){
  /* inicia a composicao do braco */
  braco = glGenLists(1); //Retorna uma lista de exibicao vazia
  glNewList(braco, GL_COMPILE); //Inicia a criacao do primeiro (e unico) elemento da display lit

  /* origem posicionada no ombro */
  glTranslatef (-1.0, 0.0, 0.0);
  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

  /* origem posicionada no centro do braco */ 
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glColor3f(0.0, 0.0, 128.0);
  glutSolidCube(1.0);
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
  glColor3f(107.0,35.0,142.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo2 */
  glTranslatef (0.0, 0.2, 0.0);
	glPushMatrix();
	glTranslatef (0.0, 0.0, 0.25);
  glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
  glColor3f(107.0,35.0,142.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* origem posicionada no dedo3 */
	glTranslatef (0.0, 0.0, -0.25);
  glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);
  glTranslatef (0.25, 0.0, 0.0);
	glScalef (0.5, 0.1, 0.33);
  glColor3f(107.0,35.0,142.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* termina a composicao do braco*/
  glEndList();
}
void display(void){
  glEnable(GL_DEPTH_TEST);
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  /* calcula a posicao do observador */
  /* O movimento da camera corresponde a um movimento circular em torno do objeto */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);

  /* 
  obs[0],obs[1],obs[2] -> eyeX, eyeY, eyeZ -> Coordenadas x, y e z da posicao da camera
  look[0],look[1],look[2] ->  centerx, centery, centerz -> Coordenadas x, y e z da posicao do alvo
  0.0,1.0,0.0 -> upX, upY, upZ -> Vetor que estabelecem o vetor que aponta "para cima"
  */
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

/* habilita/desabilita uso de texturas*/
  if(texturas){
    glEnable(GL_TEXTURE_2D);  
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  //plano texturizado
  glColor4f(COR_DO_PLANO);
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
  glBindTexture(GL_TEXTURE_2D,textura_plano);
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
  glEnd();

  //braco texturizado
  glTranslatef(0.0,2.0,-3.0);
  glColor4f(COR_DO_BRACO);
  glBindTexture(GL_TEXTURE_2D,textura_braco);
  glCallList(braco);
  glPopMatrix();
  
  /* Chama funcao com objetos criados para o display */
  compoe_braco();
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
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
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
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

void carregar_texturas(void){
  textura_braco = png_texture_load(TEXTURA_DO_BRACO, NULL, NULL);
  textura_plano = png_texture_load(TEXTURA_DO_PLANO, NULL, NULL);
}

void init(void){
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  compoe_braco();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  carregar_texturas();
  glShadeModel(GL_FLAT);
  glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv){
   
  glutInitWindowPosition(0, 0);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_ALPHA);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutCreateWindow ("BRACO GARRA");
  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}