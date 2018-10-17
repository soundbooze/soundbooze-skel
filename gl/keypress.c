// gcc c.c -o c -lGL -lglut -lGLU

#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#define WIDTH   800
#define HEIGHT  600

void 
setup (float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 0.0, 0.0, 0.0);
}

void 
draw (void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex2f(-0.8, 0.8);
  glEnd();

  glFlush();

}

void 
keypress (unsigned char key, int x, int y) 
{
  switch (key) {
    case 27:
      glutLeaveMainLoop();
      exit(0);
      break;
	}
}

void 
main (int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (100, 100);

	glutCreateWindow ("Circle");

	setup(0.0,0.0,0.0);

	glutDisplayFunc(draw);
  glutKeyboardFunc(keypress);

	glutMainLoop();
}
