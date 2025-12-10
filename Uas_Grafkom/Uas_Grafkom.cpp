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
float animationSpeed = 3.0f;
bool isAnimating = true;
int lastTime = 0;

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

    glDisable(GL_BLEND);

    glPopMatrix();
}

void drawBee() {
    glPushMatrix();

    glTranslatef(0.2f * sinf(flyingAngle), 0.15f * cosf(flyingAngle * 0.7f), 0.0f);

    drawHead();
    drawBody();
    drawWings();

    glPopMatrix();
}

void initLighting() {
    GLfloat light_position[] = { 3.0f, 4.0f, 3.0f, 0.0f };
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat light_specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void init() {
    glClearColor(0.95f, 0.95f, 0.98f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    initLighting();

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    printf("KONTROL:\n");
    printf("  W/A/S/D     → Pan Camera\n");
    printf("  ↑/↓/←/→     → Rotate View\n");
    printf("  R           → Reset View\n");
    printf("  SPACE       → Pause animation\n");
    printf("  ESC         → Exit\n\n");
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
        0.0f, 0.1f, 0.0f,
        0.0f, 1.0f, 0.0f);

    drawBee();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cute Bee 3D - Kawaii Bee! 🐝");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}