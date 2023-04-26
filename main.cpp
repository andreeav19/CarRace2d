#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/freeglut.h>

using namespace std;

GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;

double gameRunning = 1;
double j = 0.0;
double i = 0.0;

double firstIntermittentLineXTranslation = 0.0;
double secondIntermittentLineXTranslation = 0.0;
double thirdIntermittentLineXTranslation = 0.0;

double car_x_pos = 0.0;
double contor = 0;

int vector[3] = { 0, 160, 320 };
double car_obstacle_x = 800;
double car_obstacle_y = vector[rand() % 3];
double coin_x = 800;
double coin_y = ((int)car_obstacle_y + 160) % 320;
int coin_exists = rand() % 2;

int score = 0;
double timp = 0.15;
int pct = 1000;
double rsj, rdj, rss, rds = 0;

void init(void)
{
	glClearColor(0.98, 0.929, 0.792, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}
void startgame(void)
{
	if ((car_obstacle_y != j) || abs(car_obstacle_x - car_x_pos) >= 80)
	{

		if (firstIntermittentLineXTranslation < -1275) {
			firstIntermittentLineXTranslation = 0;
		}
		if (secondIntermittentLineXTranslation < -1700) {
			secondIntermittentLineXTranslation = -425;
		}
		if (thirdIntermittentLineXTranslation < -2125) {
			thirdIntermittentLineXTranslation = -850;
		}
		firstIntermittentLineXTranslation -=  2 * timp;
		secondIntermittentLineXTranslation -= 2 * timp;
		thirdIntermittentLineXTranslation -= 2 * timp;

		car_obstacle_x -= timp;
		coin_x -= timp;

		int random_i_o = rand() % 3; // random index for obstacle
		int random_i_c = rand() % 3; // random index for coin

		// ensure that obstacles and coins are not on the same line
		random_i_c = (random_i_c != random_i_o) ? random_i_c : (random_i_c + 1) % 3;


		if (car_obstacle_x < -150)
		{
			score += 100;
			car_obstacle_y = vector[random_i_o];
			cout << "Score:  " << score << endl;
			car_obstacle_x = 800;

			coin_exists = rand() % 2;
		}

		if (coin_exists && coin_x < -150)
		{
			cout << random_i_c << " ";
			cout << random_i_c << " " << random_i_o << "\n";

			coin_y = vector[random_i_c];
			coin_x = 800;
		}

		if (score >= pct && pct <= 15000)
		{
			timp += 0.1;
			pct += 1000;
		}

		glutPostRedisplay();
	}
	else {
		gameRunning = 0;
	}
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.55, 0.788, 0.451);

	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();
	RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Depaseste masinile!");

	// Delimitare sosea
	glLineWidth(3);
	glColor3f(1, 1, 1);

	// Delimitam soseaua de iarba partea de jos
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Delimitam soseaua de iarba partea de sus
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Liniile intrerupte
	glPushMatrix();
	glTranslated(firstIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(700, 80);
	glVertex2i(1075, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(700, 240);
	glVertex2i(1075, 240);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslated(secondIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(1125, 80);
	glVertex2i(1500, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(1125, 240);
	glVertex2i(1500, 240);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslated(thirdIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(1550, 80);
	glVertex2i(1925, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(1550, 240);
	glVertex2i(1925, 240);
	glEnd();

	glPopMatrix();


	//desenam masina
	glPushMatrix();
	glTranslated(car_x_pos, j, 0.0);

	glColor3f(0.996, 0.365, 0.149);
	glRecti(-45, -15, 45, 15);

	if (!gameRunning)
	{
		rsj = 8;
		rss = -8;
		rdj = -8;
		rds = 8;
	}

	glPopMatrix();
	glPopMatrix();

	if (!gameRunning) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
	}

	if (contor == 1 && (j != 160 && j != 320))
		j = j + 1;
	else if (contor == -1 && (j != 160 && j != 0))
		j = j - 1;
	else {
		contor = 0;
	}

	//desenam a doua masina (adversara)
	glPushMatrix();
	glTranslated(car_obstacle_x, car_obstacle_y, 0.0);

	glColor3f(0.471, 0.667, 0.949);
	glRecti(-45, -15, 45, 15);

	glPopMatrix();

	//draw coin
	glPushMatrix();
	glTranslated(coin_x, coin_y, 0.0);

	glColor3f(1, 0.84, 0.33);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0); // centre of the coin
	for (int index = 0; index <= 50; index++) {
		float angle = index * 2.0f * 3.14 / 50;
		float cx = 15 * cosf(angle);
		float cy = 20 * sinf(angle);
		glVertex2f(cx, cy);
	}
	glEnd();

	glPopMatrix();

	startgame();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscasus(void)
{
	if (gameRunning)
	{
		if (j < 320)
		{
			contor = 1;
			j += 1;
		}

		glutPostRedisplay();
	}
}

void moveCarForwards(void) {
	if (gameRunning) {
		if (car_x_pos < 650) {
			car_x_pos += 7;
			timp += 0.01;
		}
		glutPostRedisplay();
	}
}

void moveCarBackwards(void) {
	if (gameRunning) {
		if (car_x_pos > 0) {
			car_x_pos -= 7;
			timp -= 0.01;
		}
		glutPostRedisplay();
	}
}

void miscajos(void)
{
	if (gameRunning)
	{
		if (j > 0)
		{
			contor = -1;
			j -= 1;


		}

		glutPostRedisplay();
	}
}

void keyboard(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
			miscasus();
			break;
		case GLUT_KEY_DOWN:
			miscajos();
			break;
		case GLUT_KEY_RIGHT:
			moveCarForwards();
			break;
		case GLUT_KEY_LEFT:
			moveCarBackwards();
			break;
	}

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Depaseste masinile - mini game");
	init();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);

	glutMainLoop();
}