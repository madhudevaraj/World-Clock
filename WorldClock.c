/*===============================================
To excecute the program, type below commands in command line after changing directory to the directory where the program file is present-
gcc -framework OpenGL -framework GLUT project041.c -Wno-deprecated
./a.out
ctrl+c to exit

OR

To execute in command line -
cd to project folder
./project041.c
ctrl+c to exit
=================================================*/

#include<GLUT/glut.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;

GLfloat rx, ry, rz, angle;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; 
static int view_state = 1;

int f1=0;

void Sprint(int x, int y, char *st)
{
int l,i;

    l=strlen(st);
    glRasterPos3i( x, y, -1);
for(i=0; i < l; i++)
        {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
        }
}

static void TimeEvent(int te)
{	
    rx = 30 * cos( angle );
    ry = 30 * sin( angle );
    rz = 30 * cos( angle );
    angle += 0.01;
    glutPostRedisplay();
    glutTimerFunc( 100, TimeEvent, 1);
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT1);

   Cylinder = gluNewQuadric();
   gluQuadricDrawStyle( Cylinder, GLU_FILL);
   gluQuadricNormals( Cylinder, GLU_SMOOTH);
   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
   gluQuadricTexture( Cylinder, GL_TRUE);

   Disk = gluNewQuadric();
   gluQuadricDrawStyle( Disk, GLU_FILL);
   gluQuadricNormals( Disk, GLU_SMOOTH);
   gluQuadricOrientation( Disk, GLU_OUTSIDE);
   gluQuadricTexture( Disk, GL_TRUE);

}


void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )
{

int hour_ticks , sec_ticks;
  glPushMatrix();
  glTranslatef(cx,cy,cz);
  glRotatef( 180, 1.0, 0.0, 0.0);


  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef( 0.0, 0.0, 6.0);
  glutWireCube(14.0);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.0,0.8,0.7);
  glTranslatef( 0, 0, 1.0);
  gluDisk(Disk, 0, 6.75, 32, 16);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.0, 0.5);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/12) * newtime->tm_hour  + (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);
  glRotatef( 90, 1.0, 0.0, 0.0);
  //gluCylinder(Cylinder, .5, 0, 3, 3, 3);
  gluCylinder(Cylinder, .1, 0, 3, 3, 3);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.5, 0.2, 0.7);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
  glRotatef( 90, 1.0, 0.0, 0.0);
  //gluCylinder(Cylinder,0.5, 0, 5.5, 5.5, 5.5);
    gluCylinder(Cylinder,0.1, 0, 5.5, 5.5, 5.5);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.0, 0.3, 0.7);
  glTranslatef( 0, 0, -0.0);
  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.1, 0, 7, 7, 7);
  glPopMatrix();

for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
      {
      glPushMatrix();
      glColor3f(0.0, 0.9, 0.5);
      glTranslatef(0.0, 0.0, 0.0);
      glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
      glTranslatef( 6.0, 0.0, 0.0);
      glutSolidCube(1.0);

      glPopMatrix();
  }
    
for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
     {
       glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
    glTranslatef(6.0, 0.0, 0.0);
    glutSolidCube(0.25);
    glPopMatrix();
    }
    
  glPopMatrix();

}


void display(void)
{

  time(&ltime);
  newtime = localtime(&ltime);

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  glColor3f( 1.0, 1.0, 1.0);
if (view_state == 0)
      {
      Sprint(-3, -4, "                  Perspective view");
      }else Sprint(-2, -4, "Ortho view");

      Sprint(-2,-8, asctime(newtime));

if (view_state == 0)
     {
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();

     gluPerspective(60.0, 1, 1.0, 60.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);
     }

if (light_state == 1)
    {
       glEnable(GL_LIGHTING);
       glEnable(GL_COLOR_MATERIAL);  
    }
else
    {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);  
    }
    
	switch(f1)
	  {
	case 1:newtime->tm_hour=newtime->tm_hour+5;
		     newtime->tm_min=newtime->tm_min;
			break;
	case 2:newtime->tm_hour=newtime->tm_hour+14;
		     newtime->tm_min=newtime->tm_min;
			break;
	case 3:newtime->tm_hour=newtime->tm_hour+13;
		     newtime->tm_min=newtime->tm_min;
			break;
	case 4:newtime->tm_hour=newtime->tm_hour+8;
		     newtime->tm_min=newtime->tm_min;
			break;
	case 5:newtime->tm_hour=newtime->tm_hour;
		     newtime->tm_min=newtime->tm_min;
			break;
	  }

Draw_clock( 0.0, 0.0, -14.0);

glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

void keyboard (unsigned char key, int x, int y)
{
switch (key)
   {
case'l':
         light_state = abs(light_state - 1);
break;
case'v':
         view_state = abs(view_state - 1);
break;
default:
break;
   }
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		f1=0;
}


void menu1(int d)
{
	switch(d)
	{
		case 0: f1=1;
				break;
		case 1: f1=2;
				break;
		case 2:	f1=3;
				break;
		case 3: f1=4;
				break;
		case 4: f1=5;
				break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (999, 999);
   glutInitWindowPosition (0, 0);                
   glutCreateWindow ("WORLD CLOCK");
   glutCreateMenu(menu1);
	glutAddMenuEntry("UK (LONDON)",0);
	glutAddMenuEntry("AUSTRALIA (SYDNEY)",1);
	glutAddMenuEntry("JAPAN (TOKYO)",2);
	glutAddMenuEntry("SAUDI ARABIA (DUBAI)",3);
	glutAddMenuEntry("USA (VIRGINIA)",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutTimerFunc( 10, TimeEvent, 1);
   glutMainLoop();
return 0;
}
