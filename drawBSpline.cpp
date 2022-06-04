#include "drawBSpline.h"
#include "stdld.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cstdio>

static long font = (long)GLUT_BITMAP_9_BY_15; // Seleção da fonte.
lista* li;
int WIDTH = 600, HEIGHT = 600, numCtrlPoints;
bool enable = false;
info curva;

bool verificaPontos(info dado, short point)
{
   short tam = listaTamanho(li);

   if ( tam > 0 )
   {
      info* curve = (info*)malloc(sizeof(info)*tam);

      for ( register short i = 0; i < tam; ++i )
         consultaListaPos(li, i+1, &curve[i]);
      
      for ( register short i = 0; i < tam; ++i )
         for ( register short j = 0; j < curve[i].l; ++j )
            for ( register short l = 0; l < point; ++l )
               if ( (dado.ctrlpoints[l][0] == curve[i].ctrlpoints[j][0]) && (dado.ctrlpoints[l][1] == curve[i].ctrlpoints[j][1]) )
                  return false;

      free(curve);
   }

   for ( register short i = 0; i < point-1; ++i )
      if ( (dado.ctrlpoints[i][0] == dado.ctrlpoints[i+1][0]) && (dado.ctrlpoints[i][1] == dado.ctrlpoints[i+1][1]) )
         return false;
   
   return true;
}

void colorizaCurva(short ID)
{
   switch (ID)
   {
   case 1:
      curva.vetColorPoint[0] = 0.5422;
      curva.vetColorPoint[1] = 0.40;
      curva.vetColorPoint[2] = 0.0578;

      curva.vetColorCurve[0] = 0.1176;
      curva.vetColorCurve[1] = 0.3588;
      curva.vetColorCurve[2] = 0.5235;
      break;

   case 2:
      curva.vetColorPoint[0] = 0.4628;
      curva.vetColorPoint[1] = 0.3031;
      curva.vetColorPoint[2] = 0.2341;

      curva.vetColorCurve[0] = 0.6067;
      curva.vetColorCurve[1] = 0.0933;
      curva.vetColorCurve[2] = 0.30;
      break;

   case 3:
      curva.vetColorPoint[0] = 0.0;
      curva.vetColorPoint[1] = 0.5090;
      curva.vetColorPoint[2] = 0.4910;

      curva.vetColorCurve[0] = 0.7520;
      curva.vetColorCurve[1] = 0.0;
      curva.vetColorCurve[2] = 0.2480;
      break;

   case 4:
      curva.vetColorPoint[0] = 0.4808;
      curva.vetColorPoint[1] = 0.3894;
      curva.vetColorPoint[2] = 0.1298;

      curva.vetColorCurve[0] = 0.5148;
      curva.vetColorCurve[1] = 0.4852;
      curva.vetColorCurve[2] = 0.0;
      break;
   
   default:
      curva.vetColorPoint[0] = 0.8164;
      curva.vetColorPoint[1] = 0.1836;
      curva.vetColorPoint[2] = 0.0;

      curva.vetColorCurve[0] = 0.2339;
      curva.vetColorCurve[1] = 0.2982;
      curva.vetColorCurve[2] = 0.4678;
      break;
   }
}

info editaCurva(short ID)
{
   removeMeio(li, ID);

   do
   {
      printf("Qual o numero de pontos (de 3 a 9): ");
      scanf(" %hi", &curva.l);
   } while ( curva.l > 9 || curva.l < 3 );

   for ( register short i = 0; i < curva.l; ++i )
      do
      {
         printf("Qual a coordenada do ponto %hi (x e y): ", i+1);
         scanf(" %f %f", &curva.ctrlpoints[i][0], &curva.ctrlpoints[i][1]);
         curva.ctrlpoints[i][0] *= 10.0;
         curva.ctrlpoints[i][1] *= 10.0;
         curva.ctrlpoints[i][2] = 0.0;
      } while ( (curva.ctrlpoints[i][0] > 100.0 || curva.ctrlpoints[i][0] < -100.0) ||
                (curva.ctrlpoints[i][1] > 100.0 || curva.ctrlpoints[i][1] < -100.0) ||
                !verificaPontos(curva, i+1) );

   colorizaCurva(ID);

   curva.ID = ID;

   return curva;
}

info leCurva(short numCurve)
{
   bool aux;

   do
   {
      printf("Qual o numero de pontos (de 3 a 9): ");
      scanf(" %hi", &curva.l);
   } while ( curva.l > 9 || curva.l < 3 );

   for ( register short i = 0; i < curva.l; ++i )
      do
      {
         printf("Qual a coordenada do ponto %hi (x e y): ", i+1);
         scanf(" %f %f", &curva.ctrlpoints[i][0], &curva.ctrlpoints[i][1]);
         curva.ctrlpoints[i][0] *= 10.0;
         curva.ctrlpoints[i][1] *= 10.0;
         curva.ctrlpoints[i][2] = 0.0;
      } while ( (curva.ctrlpoints[i][0] > 100.0 || curva.ctrlpoints[i][0] < -100.0) ||
                (curva.ctrlpoints[i][1] > 100.0 || curva.ctrlpoints[i][1] < -100.0) ||
                !verificaPontos(curva, i+1) );

  colorizaCurva(numCurve);

   curva.ID = numCurve;

   return curva;
}

void myInit(void)
{
   glClearColor(1.0188, 1.0188, 0.9624, 0.0);
}

// Função que imprime na janela o bitmap da string.
void writeBitmapString(void *font, char* string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Função que faz os traços dentro da janela.
void drawScene()
{
   char strNum[10];

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glTranslatef(0.0, 0.5, 0.0);

   // Imprime o su-eixo e eixo X.
   for (register int i = 0; i < 21; ++i )
   {
      if ( -10+i == 0)
      {
         glColor3f(0.0, 0.0, 0.0);  // Preto
         glLineWidth(1.5);
         glBegin(GL_LINES);
            glVertex3d(-100.0, -100.0 + (float)i*10.0, 0.0);
            glVertex3d( 100.0, -100.0 + (float)i*10.0, 0.0);  
         glEnd();
      }
      
      else  // sub-eixo X e y
      {
         glColor3f(0.8627, 0.8627, 0.8627); // cinza claro
         glLineWidth(0.75);
         glLineStipple(2.5, 0xAAAA);
         glEnable(GL_LINE_STIPPLE);
         glBegin(GL_LINES);
            glVertex3d(-100.0 + (float)i*10.0, -100.0, 0.0);   // Sub-eixo X
            glVertex3d(-100.0 + (float)i*10.0, 100.0, 0.0); 

            glVertex3d(-100.0, -100.0 + (float)i*10.0, 0.0);   // Sub-eixo Y
            glVertex3d(100.0, -100.0 + (float)i*10.0, 0.0);
         glEnd();
         glDisable(GL_LINE_STIPPLE);
      }
   }
   

   // Imprime os pontos do eixo X.
   glColor3f(0.0, 0.0, 0.0);  // Preto
   for (register int i = 0; i < 21; ++i )
   {
      if ( -10+i == 0 )
      {
         glPointSize(10.0);
         glBegin(GL_POINTS);
            glVertex3d(0.0, 0.0, 0.0);
         glEnd();
      }
      
      else
      {
         glLineWidth(1.5);
         glBegin(GL_LINES);
            glVertex3d(-100.0+(float)i*10.0, -2.0, 0.0);
            glVertex3d(-100.0+(float)i*10.0, 2.0, 0.0);
         glEnd();
      }
   }

   // Rotula os pontos do eixo X.
   for ( register int i = 0; i < 21; ++i )
   {
      sprintf(strNum, "%i", -10+i);
      
      if ( -10+i == 0 )
         glRasterPos3f(-99.0+(float)i*10.0, -5, 0.0);

      else
         glRasterPos3f(-100.0+(float)i*10.0, -5, 0.0);
      
      writeBitmapString((void*)font, strNum); 
   }

   // Imprime o eixo Y.
   glLineWidth(1.5);
   glBegin(GL_LINES);
      glVertex3d(0.0, -100.0, 0.0);
      glVertex3d(0.0, 100.0, 0.0);  
   glEnd();

   // Imprime os pontos do eixo Y.
   glLineWidth(1.5);
   glBegin(GL_LINES);
      for (register int i = 0; i < 21; ++i )
         if ( -100+i*10 != 0 ) 
         {
            glVertex3d(-2.0, -100.0 + (float)i*10.0, 0.0);
            glVertex3d(2.0, -100.0 + (float)i*10.0, 0.0);
         }
   glEnd();

   // Rotula os pontos do eixo Y.
   for ( register int i = 0; i < 21; ++i )
   {
     sprintf(strNum, " %i", -10+i);

      if ( -10+i != 0 )
      {
         glRasterPos3f(0.0, -100.0 + (float)i*10.0, 0.0);
         writeBitmapString((void*)font, strNum); 
      }
   }
   
   for ( register int i = 0; i < listaTamanho(li); ++i )
   {
      consultaListaPos(li, i+1, &curva);
      
      glShadeModel(GL_FLAT);
      glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, curva.l, curva.ctrlpoints[0]);
      glEnable(GL_MAP1_VERTEX_3);
      glEnable(GL_LINE_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

      glColor3f(curva.vetColorCurve[0], curva.vetColorCurve[1], curva.vetColorCurve[2]);    // Troca cor da curva
      glLineWidth(2.0);   // Grosura da linha
      glBegin(GL_LINE_STRIP);
         for ( register int j = 0; j <= 100; ++j ) // Passo da função
            glEvalCoord1f((GLfloat) j/100.0);
      glEnd();

      // O código abaixo imprime os pontos de controle.
      glPointSize(5.0);   // Tamanho do ponto.
      glColor3f(curva.vetColorPoint[0], curva.vetColorPoint[1], curva.vetColorPoint[2]);    // Troca cor dos pontos de controle
      glBegin(GL_POINTS);
         for ( register short j = 0; j < curva.l; ++j ) 
            glVertex3fv(curva.ctrlpoints[j]);
      glEnd();
      glDisable(GL_MAP1_VERTEX_3);
      glDisable(GL_LINE_SMOOTH);
      glDisable(GL_BLEND);
   }
   
   glPopMatrix();
   glutSwapBuffers();
   glFlush();
}

void reshape(int w, int h)
{
   WIDTH = w;
   HEIGHT = h;

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if ( w <= h )
      glOrtho(-110.0, 110.0, -110.0*(GLfloat)h/(GLfloat)w, 110.0*(GLfloat)h/(GLfloat)w, -110.0, 110.0);
   
   else
      glOrtho(-110.0*(GLfloat)w/(GLfloat)h, 110.0*(GLfloat)w/(GLfloat)h, -110.0, 110.0, -110.0, 110.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void printInteraction(void)
{
   system("cls || clear");
   printf("\t########## MENU ##########\n"
          "Pressione 1 para inserir uma curva por teclado.\n"
          "Pressione 2 para inserir uma curva por mouse.\n"
          "Pressione 3 para editar uma curva.\n"
          "Pressione 4 para remover uma curva.\n"
          "Pressione 5 para resetar.\n"
          "Pressione 0 para sair.\n"
          "###############################################\n");
}

void mouseInput(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && enable )
   {
      if ( WIDTH <= HEIGHT )
      {
         curva.ctrlpoints[numCtrlPoints][0] = ( (2.0*110.0*x)/WIDTH ) - 110.0;
         curva.ctrlpoints[numCtrlPoints][1] = (( (2.0*110.0*HEIGHT/WIDTH)*(y-HEIGHT) )/(-HEIGHT) ) - 110.0*HEIGHT/WIDTH;
         curva.ctrlpoints[numCtrlPoints][2] = 0.0;
      }

      else
      {
         curva.ctrlpoints[numCtrlPoints][0] = ( (2.0*110.0*WIDTH/HEIGHT*x)/WIDTH ) - 110.0*WIDTH/HEIGHT;
         curva.ctrlpoints[numCtrlPoints][1] = (( (2.0*110.0)*(y-HEIGHT) )/(-HEIGHT) ) - 110.0;
         curva.ctrlpoints[numCtrlPoints][2] = 0.0;
      }

      if ( (curva.ctrlpoints[numCtrlPoints][0] <= 100.0 && curva.ctrlpoints[numCtrlPoints][0] >= -100.0) &&
         (curva.ctrlpoints[numCtrlPoints][1] <= 100.0 && curva.ctrlpoints[numCtrlPoints][1] >= -100.0) &&
         verificaPontos(curva, numCtrlPoints+1) )
      {
         printf("A coordenada do ponto %hi (x e y): %.2f\t%.2f\n", numCtrlPoints+1, curva.ctrlpoints[numCtrlPoints][0]/10.0, curva.ctrlpoints[numCtrlPoints][1]/10.0);
         
         ++curva.l;
         ++numCtrlPoints;
      }
   }   

   if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && enable )
   {
      colorizaCurva(listaTamanho(li)+1);
      
      curva.ID = listaTamanho(li)+1;

      if ( numCtrlPoints <= 9 && numCtrlPoints >= 3 )
         insereListaFinal(li, curva);

      curva.l = 0;
      numCtrlPoints = 0;
      enable = false;

      printf("####################\n");

      printInteraction();
      glutPostRedisplay();
   }
}

void keyInput(unsigned char key, int x, int y)
{
   short aux, tam;

   switch (key) 
   {
      case '0':
         liberaLista(li);
         system("cls || clear");
         glutLeaveMainLoop();
         break;
      case '1':
         system("cls || clear");

         if ( (listaTamanho(li)+1) > 5 )
         {
            printf("O limite maximo de curvas ja foi atingindo,"
                   " por favor remova uma curva antes de inserir a proxima\n");
            printf("pressione qualquer tecla para continuar.\n");
            getchar();

            printInteraction();
            glutPostRedisplay();
            break;
         }
         
         printf("\t#####\tCURVA %hi\t#####\n", listaTamanho(li)+1);
         insereListaFinal(li, leCurva(listaTamanho(li)+1));
         printf("####################\n");
         
         printInteraction();
         glutPostRedisplay();
         break;
      case '2':
         system("cls || clear");
         curva.l = 0;
         numCtrlPoints = 0;
         enable = true;

         printf("Clique com botao esquerdo para inserir pontos de controle (1 a 9).\n"
                "Clique com botao direito para terminar a insercao.\n");
         printf("\t#####\tCURVA %hi\t#####\n", listaTamanho(li)+1);
         break;
      case '3':
         system("cls || clear");
         printf("Qual curva deseja editar (1 a 5): ");
         scanf(" %hi", &aux);

         if ( aux > 0 && aux <= listaTamanho(li) )
            insereListaMeio(li, editaCurva(aux));

         printInteraction();
         glutPostRedisplay();
         break;
      case '4':
         system("cls || clear");

         printf("Qual curva deseja remover (1 a 5): ");
         scanf(" %hi", &aux);

         if ( aux > 0 && aux <= listaTamanho(li) )
            removeMeio(li, aux);
            
        tam = listaTamanho(li);
         for ( register short i = aux; i <= tam; ++i )
         {
            consultaListaPos(li, aux, &curva);
            curva.ID=i;
            colorizaCurva(i);
            removeMeio(li, i+1);
            insereListaFinal(li, curva);
         }

         printInteraction();
         glutPostRedisplay();
         break;
      case '5':
         system("cls || clear");

         liberaLista(li);
         criaLista(&li);

         printf("Tela resetada com sucesso!\n");
         printf("pressione qualquer tecla para continuar.\n");
         getchar();

         printInteraction();
         glutPostRedisplay();
         break;
      default:
         break;
  }
}

void display(int argc, char** argv)
{
   criaLista(&li);
   
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("B-Spline Maker");
   myInit();

   glutDisplayFunc(drawScene); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseInput);
   glutMainLoop();
}

