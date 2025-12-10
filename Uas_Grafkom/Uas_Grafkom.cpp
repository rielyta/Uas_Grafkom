#include <glut.h>
#include <math.h>
#include <stdio.h>

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 3.5f;
float cameraRotX = 0.0f;
float cameraRotY = 0.0f;

float flyingAngle = 0.0f;
float wingFlap = 0.0f;
float animationSpeed = 0.2f;
bool isAnimating = true;

// Definisi warna
float beeYellow[4] = { 255.0f / 255.0f, 223.0f / 255.0f, 0.0f / 255.0f, 1.0f };
float beeBlack[4] = { 20.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f };
float whiteColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float darkBrown[4] = { 101.0f / 255.0f, 67.0f / 255.0f, 33.0f / 255.0f, 1.0f };
float wingColor[4] = { 0.7f, 0.8f, 1.0f, 0.5f };
float skinColor[4] = { 255.0f / 255.0f, 223.0f / 255.0f, 0.0f / 255.0f, 1.0f };

void drawSphere(float radius, int slices, float color[]) {
    glColor3fv(color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    GLfloat specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
    glutSolidSphere(radius, slices, slices);
}

void drawCylinder(float radius, float height, int slices, float color[]) {
    glColor3fv(color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    GLfloat specular[] = { 0.02f, 0.02f, 0.02f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, slices);
    gluDeleteQuadric(quad);
}

void drawHead() {
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);

    drawSphere(0.30f, 25, skinColor);

    // Antena Kiri
    glPushMatrix();
    glTranslatef(-0.18f, 0.28f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.05f, 0.0f, 0.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    drawCylinder(0.025f, 0.15f, 8, beeBlack);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.12f, 0.08f, 0.0f);
    drawSphere(0.06f, 12, beeYellow);
    glPopMatrix();
    glPopMatrix();

    // Antena Kanan
    glPushMatrix();
    glTranslatef(0.18f, 0.28f, 0.0f);
    glPushMatrix();
    glTranslatef(0.05f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawCylinder(0.025f, 0.15f, 8, beeBlack);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.12f, 0.08f, 0.0f);
    drawSphere(0.06f, 12, beeYellow);
    glPopMatrix();
    glPopMatrix();

    // Mata Kiri
    glPushMatrix();
    glTranslatef(-0.12f, 0.08f, 0.28f);
    drawSphere(0.08f, 12, whiteColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.01f, 0.075f);
    drawSphere(0.04f, 10, darkBrown);
    glPopMatrix();
    glPopMatrix();

    // Mata Kanan
    glPushMatrix();
    glTranslatef(0.12f, 0.08f, 0.28f);
    drawSphere(0.08f, 12, whiteColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.01f, 0.075f);
    drawSphere(0.04f, 10, darkBrown);
    glPopMatrix();
    glPopMatrix();

    // Senyum
    for (int i = 0; i <= 6; i++) {
        float angle = 0.4f + (3.14159f - 0.8f) * (i / 6.0f);
        float x = 0.06f * cosf(angle);
        float y = -0.10f - 0.04f * sinf(angle);
        float z = 0.28f;
        glPushMatrix();
        glTranslatef(x, y, z);
        drawSphere(0.012f, 6, beeBlack);
        glPopMatrix();
    }

    glPopMatrix();
}

void drawBody() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    drawSphere(0.20f, 22, beeYellow);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.08f, 0.0f);
    drawSphere(0.20f, 22, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.21f, 0.0f);
    drawSphere(0.20f, 22, beeYellow);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.34f, 0.0f);
    drawSphere(0.18f, 20, beeBlack);
    glPopMatrix();

    // Kaki
    glPushMatrix();
    glTranslatef(-0.22f, -0.05f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, -0.05f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.24f, -0.15f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.24f, -0.15f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.22f, -0.28f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, -0.28f, 0.0f);
    drawSphere(0.05f, 8, beeBlack);
    glPopMatrix();

    glPopMatrix();
}

void drawWings() {
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    // Sayap Kiri
    glPushMatrix();
    glTranslatef(-0.28f, 0.05f, 0.0f);
    glRotatef(wingFlap * 30.0f, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(2.45f, 1.40f, 0.08f);
    drawSphere(0.15f, 14, wingColor);
    glPopMatrix();
    glPopMatrix();

    // Sayap Kanan
    glPushMatrix();
    glTranslatef(0.28f, 0.05f, 0.0f);
    glRotatef(-wingFlap * 30.0f, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(2.45f, 1.40f, 0.08f);
    drawSphere(0.15f, 14, wingColor);
    glPopMatrix();
    glPopMatrix();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glPopMatrix();
}

void drawBee() {
    glPushMatrix();

    float hoverY = 0.15f * cosf(flyingAngle * 0.7f);
    glTranslatef(0.0f, hoverY, 0.0f);

    drawHead();
    drawBody();
    drawWings();

    glPopMatrix();
}

void timer(int value) {
    if (isAnimating) {
        static float t_wing = 0.0f;
        t_wing += 1.5f;
        wingFlap = sinf(t_wing);
        flyingAngle += animationSpeed;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        cameraY -= 0.1f;
        break;
    case 's':
    case 'S':
        cameraY += 0.1f;
        break;
    case ' ':
        isAnimating = !isAnimating;
        break;
    case 'r':
    case 'R':
        cameraX = 0;
        cameraY = 0;
        cameraZ = 3.5f;
        cameraRotX = 0;
        cameraRotY = 0;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void initLighting() {
    GLfloat light_pos[] = { 3.0f, 4.0f, 5.0f, 1.0f };
    GLfloat white_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat amb_light[] = { 0.4f, 0.4f, 0.4f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_light);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float radX = cameraRotX * 3.14159f / 180.0f;
    float radY = cameraRotY * 3.14159f / 180.0f;

    float eyeX = cameraX + cameraZ * sinf(radY) * cosf(radX);
    float eyeY = cameraY + cameraZ * sinf(radX);
    float eyeZ = cameraZ * cosf(radY) * cosf(radX);

    gluLookAt(eyeX, eyeY, eyeZ,
        cameraX, cameraY, 0.0f,
        0.0f, 1.0f, 0.0f);

    drawBee();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("UAS Grafika Komputer - Cute Bee 3D");

    initLighting();
    glClearColor(0.95f, 0.95f, 0.98f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    printf("=== KONTROL PROGRAM ===\n");
    printf("W/S : Geser Kamera Vertikal\n");
    printf("Spasi : Pause/Play Animasi\n");
    printf("R : Reset Kamera\n");
    printf("ESC : Keluar\n");

    glutMainLoop();
    return 0;
}