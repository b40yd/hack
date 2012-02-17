/* include OpenGL utility toolkit */
#include <GL/glut.h>


/* rectangle with position */
GLfloat xx1 = 0.0f;
GLfloat yy1 = 0.0f;
GLfloat rsize = 25;

/* move pixel */
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;


void RenderScene(void)
{
  /* use current color clear window */
  glClear(GL_COLOR_BUFFER_BIT);
  /* set red color */
  glColor3f(1.0f,0.0f,0.0f);
  /* Draws a filled rectangle with the current color */
  glRectf(xx1,yy1,xx1 + rsize ,yy1 - rsize);
  /* Refresh the drawing command and swaping */
  glutSwapBuffers();
}

/* free time glut function libraries call */ 
void TimerFunction(int value){
  /* arrive left and right veer */
  if (xx1 > windowWidth-rsize || xx1 < -windowWidth){
    xstep = -xstep;
  }
  /* arrive top and buttom veer */
  if (yy1 > windowHeight || yy1 < -windowHeight + rsize ){
    ystep = -ystep;
  }
  xx1 += xstep;
  yy1 += ystep;
  
  if(xx1 > (windowWidth-rsize + xstep))
    xx1 = windowWidth-rsize-1;
  else if (xx1 < -(windowWidth + xstep))
    xx1 = - windowWidth-1;
  if (yy1 > (windowHeight+ystep))
    yy1 = windowHeight-1;
  else if (yy1 < -(windowHeight - rsize + ystep))
    yy1 = -windowHeight + rsize - 1;

  glutPostRedisplay();
  glutTimerFunc(33,TimerFunction,1);
}

 /* set romance status */
void SetupRC(void){
  /* set clear color */
  glClearColor(0.0f,0.0f,1.0f,1.0f);
}

void ChangeSize(int w ,int h){
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
  if (w <= h) 
    {
      windowWidth = 100;
      windowHeight = 100 / aspectRatio;
      glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    }
  else 
    {
      windowWidth = 100 * aspectRatio;
      windowHeight = 100;
      glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  /* initialize window position */
  //glutInitWindowPosition(200, 200);
  /* initialize window size */
  glutInitWindowSize(800, 600);
  /* Create window,and set title */
  glutCreateWindow("rectangle opengl");
  /* Displays the callback function */
  glutDisplayFunc(RenderScene);
  /* change window size callback function */
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33,TimerFunction,1);
  SetupRC();
  /* Start glut framework, defined screen display callback function and other function. */
  glutMainLoop();
  return 0;
}
