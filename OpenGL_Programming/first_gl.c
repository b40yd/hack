/* include OpenGL utility toolkit */
#include <GL/glut.h>
#include <math.h>


void myDisplay(void)
{
  /* display a triangles */

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin (GL_TRIANGLES);
  glVertex3f (0,1,0);
  glVertex3f (-1, 0, 0);
  glVertex3f (1, 0, 0);
  glEnd ();
  glFlush();
}


int main(int argc, char *argv[])
{
  /* initialize glut  */
  glutInit(&argc, argv);
  /* use what display mode 
     use single buffer,and use RGBA color mode
   */
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  /* initialize window position */
  glutInitWindowPosition(200, 200);
  /* initialize window size */
  glutInitWindowSize(500, 500);
  /* Create window,and set title */
  glutCreateWindow("first opengl");
  /* Displays the callback function */
  glutDisplayFunc(&myDisplay);
  /* Start glut framework, defined screen display callback function and other function. */
  glutMainLoop();
  return 0;
}
