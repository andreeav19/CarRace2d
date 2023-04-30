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
double speed = 0.15;
int points = 1000;
double rbl, rbr, rtl, rtr = 0;

const float PI = 3.14;
const int sides = 50;

void init(void)
{
	glClearColor(0.56, 0.58, 0.58, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}

void resetGame() {
	gameRunning = 1;
	j = 0.0;
	i = 0.0;
	firstIntermittentLineXTranslation = 0.0;
	secondIntermittentLineXTranslation = 0.0;
	thirdIntermittentLineXTranslation = 0.0;
	car_x_pos = 0.0;
	contor = 0;
	car_obstacle_x = 800;
	car_obstacle_y = vector[rand() % 3];
	score = 0;
	speed = 0.15;
	points = 1000;
	rbl, rbr, rtl, rtr = 0;
}


void startgame(void) {
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
		firstIntermittentLineXTranslation -= 2 * speed;
		secondIntermittentLineXTranslation -= 2 * speed;
		thirdIntermittentLineXTranslation -= 2 * speed;

		car_obstacle_x -= speed;
		coin_x -= speed;

		int random_i_o = rand() % 3; // random index for obstacle
		int random_i_c = rand() % 3; // random index for coin

		// ensure that obstacles and coins are not on the same line
		random_i_c = (random_i_c != random_i_o) ? random_i_c : (random_i_c + 1) % 3;

		if (coin_exists && abs(car_x_pos - coin_x) <= 50 && abs(j - coin_y) <= 25) {
			score += 50;
			cout << "Score:  " << score << endl;
			coin_x = -200;
			coin_exists = 0;
		}

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
			coin_y = vector[random_i_c];
			coin_x = 800;
		}

		if (score >= points && points <= 15000)
		{
			speed += 0.1;
			points += 1000;
		}

		glutPostRedisplay();
	}
	else {
		gameRunning = 0;
	}
}

void drawPlayerCar() {

	// draw windows

	glColor3f(0.88, 0.24, 0.22);

	float radius = 25;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * PI / sides;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();


	glColor3f(0.6, 0.92, 0.94);

	radius = 20;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * PI / sides;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.88, 0.24, 0.22);

	glRecti(-3, 0, 0, 24); // separate windows
	glRecti(-45, -10, 45, 10);	// car body

	// draw wheels

	glColor3f(0.22, 0.23, 0.23);

	radius = 8;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.35, 0.35, 0.35);

	radius = 5;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.22, 0.23, 0.23);

	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(17.0f, -5.0f);
	glVertex2f(24.0f, -15.0f);

	glVertex2f(24.0f, -5.0f);
	glVertex2f(17.0f, -15.0f);

	glVertex2f(25.5f, -10.0f);
	glVertex2f(15.5f, -10.0f);

	glVertex2f(-17.0f, -5.0f);
	glVertex2f(-24.0f, -15.0f);

	glVertex2f(-24.0f, -5.0f);
	glVertex2f(-17.0f, -15.0f);

	glVertex2f(-25.5f, -10.0f);
	glVertex2f(-15.5f, -10.0f);

	glEnd();

	// draw doors

	glColor3f(0.63, 0.24, 0.2);

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-15.0f, 5.0f);
	glVertex2f(-8.0f, 5.0f);

	glVertex2f(8.0f, 5.0f);
	glVertex2f(1.0f, 5.0f);
	glEnd();

	// draw headlights
	glColor3f(0.78, 0.74, 0.55);
	glRecti(35, 5, 45, 10);

	glColor3f(0.7, 0.34, 0.31);
	glRecti(-45, 5, -40, 10);

}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.55, 0.788, 0.451);

	// Bottom grass
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// bottom left
	glVertex2i(700, -140); // bottom right
	glVertex2i(700, -80);  // top right
	glVertex2i(-100, -80); // top left
	glEnd();

	// Top grass
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// bottom left
	glVertex2i(700, 400); // bottom right
	glVertex2i(700, 460); // top right
	glVertex2i(-100, 460);// top left
	glEnd();
	RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Outrun the cars!");

	// Road boundary
	glLineWidth(3);
	glColor3f(1, 1, 1);

	// Boundary between road and bottom grass
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Boundary between road and top grass
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Intermittent Lines
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


	// Draw player car
	glPushMatrix();
	glTranslated(car_x_pos, j, 0.0);

	drawPlayerCar();

	if (!gameRunning)
	{
		rbl = 8;
		rtl = -8;
		rbr = -8;
		rtr = 8;
	}

	glPopMatrix();
	glPopMatrix();

	if (contor == 1 && (j != 160 && j != 320))
		j = j + 1;
	else if (contor == -1 && (j != 160 && j != 0))
		j = j - 1;
	else {
		contor = 0;
	}

	// Draw car obstacle
	glPushMatrix();
	glTranslated(car_obstacle_x, car_obstacle_y, 0.0);

	glColor3f(0.471, 0.667, 0.949);
	glRecti(-45, -15, 45, 15);

	glPopMatrix();

	// Draw coin
	glPushMatrix();
	glTranslated(coin_x, coin_y, 0.0);

	glColor3f(1, 0.84, 0.33);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0); // centre of the coin
	for (int index = 0; index <= sides; index++) {
		float angle = index * 2.0f * PI / sides;
		float cx = 15 * cosf(angle);
		float cy = 20 * sinf(angle);
		glVertex2f(cx, cy);
	}
	glEnd();

	glPopMatrix();

	if (!gameRunning) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"GAME OVER");
		glColor3f(1, 0.4, 0.3);
		glBegin(GL_QUAD_STRIP);
		glVertex2f(260.0, 180.0);
		glVertex2f(260.0, 130.0);
		glVertex2f(350.0, 180.0);
		glVertex2f(350.0, 130.0);
		glEnd();
		RenderString(275.0f, 150.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Restart");
	}

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

void moveCarUp(void)
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

void moveCarDown(void)
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

void moveCarForwards(void) {
	if (gameRunning) {
		if (car_x_pos < 650) {
			car_x_pos += 0.5;
			speed += 0.0005;
		}
		glutPostRedisplay();
	}
}

void moveCarBackwards(void) {
	if (gameRunning) {
		if (car_x_pos > 0) {
			car_x_pos -= 0.5;
			speed -= 0.0005;
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

void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		double wx = (double)mx / glutGet(GLUT_WINDOW_WIDTH) * (right_m - left_m) + left_m;
		double wy = (1.0 - (double)my / glutGet(GLUT_WINDOW_HEIGHT)) * (top_m - bottom_m) + bottom_m;

		if (wx >= 260.0 && wx <= 350.0 && wy >= 130.0 && wy <= 180.0) {
			if (!gameRunning)
				resetGame();
		}
	}
}

bool keys[256]; // array to store the state of each key

void keyboard(int key, int x, int y)
{
	keys[key] = true; // set the corresponding element to true when a key is pressed

	// handling these two cases here because handling in handleKeys() makes the car move up two lanes with a slight keypress making precise movements hard to achieve
	if (key == GLUT_KEY_UP) {
		moveCarUp();
	}
	if (key == GLUT_KEY_DOWN) {
		moveCarDown();
	}
}

void keyboardUp(int key, int x, int y)
{
	keys[key] = false; // set the corresponding element to false when a key is released
}

void handleKeys()
{
	if (keys[GLUT_KEY_RIGHT]) {
		moveCarForwards();
	}
	if (keys[GLUT_KEY_LEFT]) {
		moveCarBackwards();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Outrun the cars! - mini game");
	init();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUp);

	glutIdleFunc(handleKeys);

	glutMainLoop();
}