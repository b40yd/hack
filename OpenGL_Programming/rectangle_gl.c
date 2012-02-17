/* include OpenGL utility toolkit */
#include <GL/glut.h>
#include <math.h>

void RenderScene(void)
{
  /* use current color clear window */
  glClear(GL_COLOR_BUFFER_BIT);
  /* set red color */
  glColor3f(1.0f,0.0f,0.0f);
  /* Draws a filled rectangle with the current color */
  glRectf(-15.0f,15.0f,15.0f,-15.0f);
  /* Refresh the drawing command */
  glFlush();
}
 /* set romance status */
void SetupRC(void){
  /* set clear color */
  glClearColor(0.0f,0.0f,1.0f,1.0f);
}

void ChangeSize(GLsizei w ,GLsizei h){
  GLfloat aspectRatio;
  if (h == 0){
    h = 1;
  }
  /* set view for window size */
  glViewport(0,0,w,h);
  /* reset coordinate system */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* foundation cut area */
  aspectRatio = (GLfloat)w / (float)h;
  if (w <= h){
    /* projection mode command */
    glOrtho(-100.0,100.0,-100.0 / aspectRatio,100.0 / aspectRatio,1.0,-1.0);
  }else
    glOrtho(-100.0 * aspectRatio,100.0 * aspectRatio, -100.0,-100.0,1.0,-1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
  //glutInitWindowPosition(200, 200);
  /* initialize window size */
  //glutInitWindowSize(500, 500);
  /* Create window,and set title */
  glutCreateWindow("rectangle opengl");
  /* Displays the callback function */
  glutDisplayFunc(RenderScene);
  /* change window size callback function */
  glutReshapeFunc(ChangeSize);
  SetupRC();
  /* Start glut framework, defined screen display callback function and other function. */
  glutMainLoop();
  return 0;
}
