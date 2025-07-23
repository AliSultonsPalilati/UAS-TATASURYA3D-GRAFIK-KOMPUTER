#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

// BAGIAN 1: FONDASI & STRUKTUR DASAR

//-----------------------------------------------------
// 1.1 Variabel Global & Definisi
//-----------------------------------------------------

float sunRotation = 0.0f;
float mercuryOrbit = 0.0f, mercuryRotation = 0.0f;
float venusOrbit = 0.0f, venusRotation = 0.0f;
float earthOrbit = 0.0f, earthRotation = 0.0f;
float moonOrbit = 0.0f;
float marsOrbit = 0.0f, marsRotation = 0.0f;
float jupiterOrbit = 0.0f, jupiterRotation = 0.0f;
float saturnOrbit = 0.0f, saturnRotation = 0.0f;
float uranusOrbit = 0.0f, uranusRotation = 0.0f;
float neptuneOrbit = 0.0f, neptuneRotation = 0.0f;
float plutoOrbit = 0.0f, plutoRotation = 0.0f;

float cameraAngleH = 0.0f, cameraAngleV = 0.0f;
float cameraDistance = 25.0f;
int autoRotateEnabled = 1;

float mercuryOrbitSpeed = 2.0f;
float venusOrbitSpeed = 0.8f;
float earthOrbitSpeed = 0.5f;
float earthRotationSpeed = 5.0f;
float moonOrbitSpeed = 5.0f;
float marsOrbitSpeed = 0.2f;
float jupiterOrbitSpeed = 0.1f;
float saturnOrbitSpeed = 0.07f;
float uranusOrbitSpeed = 0.05f;
float neptuneOrbitSpeed = 0.03f;
float plutoOrbitSpeed = 0.01f;

#define MAX_STARS 500
#define MAX_NEBULA_POINTS 100
float starFieldRotation = 0.0f;

GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

//-----------------------------------------------------
// 1.2 Struktur Data (Structs)
//-----------------------------------------------------

typedef struct {
    float x, y, z;
    float brightness;
    float twinkleSpeed;
    float twinklePhase;
} Star;

typedef struct {
    float x, y, z;
    float r, g, b, a;
    float size;
    float pulsePhase;
} NebulaPoint;

Star stars[MAX_STARS];
NebulaPoint nebula[MAX_NEBULA_POINTS];

void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void update(int);
void initStars();
void initNebula();

//-----------------------------------------------------
// 1.3 Fungsi Inisialisasi Utama
//-----------------------------------------------------

void init() {
    glClearColor(0.0f, 0.0f, 0.02f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    initStars();
    initNebula();
}

//-----------------------------------------------------
// 1.4 Fungsi Main (Titik Awal Program)
//-----------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simulasi Tata Surya 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}

// BAGIAN 2: LATAR BELAKANG KOSMIK 

//-----------------------------------------------------
// 2.1 Fungsi Inisialisasi Latar
//-----------------------------------------------------

void initStars() {
    int i;
    srand((unsigned int)time(NULL));

    for (i = 0; i < MAX_STARS; i++) {
        float theta = (float)rand() / RAND_MAX * 2.0f * M_PI;
        float phi = (float)rand() / RAND_MAX * M_PI;
        float radius = 40.0f + (float)rand() / RAND_MAX * 30.0f;

        stars[i].x = radius * sin(phi) * cos(theta);
        stars[i].y = radius * cos(phi);
        stars[i].z = radius * sin(phi) * sin(theta);

        stars[i].brightness = 0.3f + (float)rand() / RAND_MAX * 0.7f;
        stars[i].twinkleSpeed = 1.0f + (float)rand() / RAND_MAX * 3.0f;
        stars[i].twinklePhase = (float)rand() / RAND_MAX * 2.0f * M_PI;
    }
}

void initNebula() {
    int i;
    for (i = 0; i < MAX_NEBULA_POINTS; i++) {
        float theta = (float)rand() / RAND_MAX * 2.0f * M_PI;
        float phi = (float)rand() / RAND_MAX * M_PI;
        float radius = 35.0f + (float)rand() / RAND_MAX * 25.0f;

        nebula[i].x = radius * sin(phi) * cos(theta);
        nebula[i].y = radius * cos(phi);
        nebula[i].z = radius * sin(phi) * sin(theta);

        float colorType = (float)rand() / RAND_MAX;
        if (colorType < 0.25f) {
            nebula[i].r = 0.6f + (float)rand() / RAND_MAX * 0.4f;
            nebula[i].g = 0.2f + (float)rand() / RAND_MAX * 0.3f;
            nebula[i].b = 0.8f + (float)rand() / RAND_MAX * 0.2f;
        } else if (colorType < 0.5f) {
            nebula[i].r = 0.1f + (float)rand() / RAND_MAX * 0.3f;
            nebula[i].g = 0.4f + (float)rand() / RAND_MAX * 0.4f;
            nebula[i].b = 0.8f + (float)rand() / RAND_MAX * 0.2f;
        } else if (colorType < 0.75f) {
            nebula[i].r = 0.8f + (float)rand() / RAND_MAX * 0.2f;
            nebula[i].g = 0.3f + (float)rand() / RAND_MAX * 0.4f;
            nebula[i].b = 0.6f + (float)rand() / RAND_MAX * 0.3f;
        } else {
            nebula[i].r = 0.2f + (float)rand() / RAND_MAX * 0.3f;
            nebula[i].g = 0.7f + (float)rand() / RAND_MAX * 0.3f;
            nebula[i].b = 0.8f + (float)rand() / RAND_MAX * 0.2f;
        }

        nebula[i].a = 0.1f + (float)rand() / RAND_MAX * 0.3f;
        nebula[i].size = 0.5f + (float)rand() / RAND_MAX * 1.5f;
        nebula[i].pulsePhase = (float)rand() / RAND_MAX * 2.0f * M_PI;
    }
}

//-----------------------------------------------------
// 2.2 Fungsi Menggambar Latar
//-----------------------------------------------------

void drawStarField() {
    int i;
    glDisable(GL_LIGHTING);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2.0f);

    glPushMatrix();
    glRotatef(starFieldRotation * 0.1f, 0.0f, 1.0f, 0.0f);
    glRotatef(starFieldRotation * 0.05f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    for (i = 0; i < MAX_STARS; i++) {
        float twinkle = sin(stars[i].twinklePhase + starFieldRotation * stars[i].twinkleSpeed * 0.1f);
        float brightness = stars[i].brightness * (0.7f + 0.3f * twinkle);

        if (i % 10 == 0) {
            glColor3f(brightness * 0.8f, brightness * 0.9f, brightness);
        } else if (i % 15 == 0) {
            glColor3f(brightness, brightness * 0.7f, brightness * 0.5f);
        } else if (i % 20 == 0) {
            glColor3f(brightness, brightness * 0.9f, brightness * 0.7f);
        } else {
            glColor3f(brightness, brightness, brightness);
        }
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawNebula() {
    int i;
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);

    glPushMatrix();
    glRotatef(starFieldRotation * 0.02f, 0.0f, 0.0f, 1.0f);

    for (i = 0; i < MAX_NEBULA_POINTS; i++) {
        glPushMatrix();
        glTranslatef(nebula[i].x, nebula[i].y, nebula[i].z);

        float pulse = sin(nebula[i].pulsePhase + starFieldRotation * 0.02f);
        float alpha = nebula[i].a * (0.7f + 0.3f * pulse);
        float size = nebula[i].size * (0.8f + 0.4f * pulse);

        glColor4f(nebula[i].r, nebula[i].g, nebula[i].b, alpha);
        glPointSize(size);

        glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();

        glPopMatrix();
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawCosmicDust() {
    int i;
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(1.0f);

    glColor4f(0.4f, 0.3f, 0.6f, 0.15f);

    glBegin(GL_POINTS);
    for (i = 0; i < 200; i++) {
        float theta = i * 0.618f * 2.0f * M_PI;
        float phi = i * 0.1f;
        float radius = 30.0f + i * 0.15f;

        float x = radius * sin(phi + starFieldRotation * 0.005f) * cos(theta);
        float y = radius * cos(phi + starFieldRotation * 0.005f) + sin(i * 0.1f + starFieldRotation * 0.01f) * 5.0f;
        float z = radius * sin(phi + starFieldRotation * 0.005f) * sin(theta);

        glVertex3f(x, y, z);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

// BAGIAN 3: MENGGAMBAR MATAHARI & PLANET 

//-----------------------------------------------------
// 3.1 Fungsi Pembantu (Helpers) & Pencahayaan
//-----------------------------------------------------

void drawSphere(float radius, int slices, int stacks) {
    glutSolidSphere(radius, slices, stacks);
}

void drawOrbit(float radius) {
    int i;
    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.5f, 0.6f);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void setupLighting() {
    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 0.9f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

//-----------------------------------------------------
// 3.2 Fungsi Menggambar Benda Langit
//-----------------------------------------------------

void drawSun() {
    GLfloat sunMaterial[] = {1.0f, 0.4f, 0.0f, 1.0f};
    GLfloat sunEmission[] = {0.9f, 0.35f, 0.0f, 1.0f};

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sunMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, sunEmission);

    glRotatef(sunRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(1.5f, 30, 30);

    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawMercury() {
    GLfloat mercuryMaterial[] = {0.8f, 0.75f, 0.7f, 1.0f};
    GLfloat mercuryEmission[] = {0.05f, 0.05f, 0.03f, 1.0f};
    GLfloat mercurySpecular[] = {0.2f, 0.2f, 0.15f, 1.0f};

    glPushMatrix();

    drawOrbit(1.5f + 0.7f);

    glRotatef(mercuryOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.5f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mercuryMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, mercuryEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mercurySpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

    glRotatef(mercuryRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.25f, 15, 15);

    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawVenus() {
    GLfloat venusMaterial[] = {1.0f, 0.9f, 0.5f, 1.0f};
    GLfloat venusEmission[] = {0.2f, 0.15f, 0.05f, 1.0f};
    GLfloat venusSpecular[] = {0.4f, 0.3f, 0.1f, 1.0f};

    glPushMatrix();

    drawOrbit(2.0f + 0.7f);

    glRotatef(venusOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(2.0f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, venusMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, venusEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, venusSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);

    glRotatef(venusRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.3f, 18, 18);

    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawMars() {
    GLfloat marsMaterial[] = {1.0f, 0.5f, 0.2f, 1.0f};
    GLfloat marsEmission[] = {0.15f, 0.05f, 0.0f, 1.0f};
    GLfloat marsSpecular[] = {0.3f, 0.15f, 0.08f, 1.0f};

    glPushMatrix();

    drawOrbit(5.2f + 0.7f);

    glRotatef(marsOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(5.2f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, marsMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, marsEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, marsSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0f);

    glRotatef(marsRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.35f, 18, 18);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawJupiter() {
    GLfloat jupiterMaterial[] = {0.9f, 0.7f, 0.4f, 1.0f};
    GLfloat jupiterEmission[] = {0.1f, 0.08f, 0.05f, 1.0f};
    GLfloat jupiterSpecular[] = {0.3f, 0.25f, 0.15f, 1.0f};

    glPushMatrix();
    drawOrbit(7.5f + 0.7f);

    glRotatef(jupiterOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(7.5f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, jupiterMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, jupiterEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, jupiterSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 35.0f);

    glRotatef(jupiterRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.7f, 25, 25);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawUranus() {
    GLfloat uranusMaterial[] = {0.5f, 0.8f, 0.9f, 1.0f};
    GLfloat uranusEmission[] = {0.04f, 0.06f, 0.07f, 1.0f};
    GLfloat uranusSpecular[] = {0.2f, 0.3f, 0.35f, 1.0f};

    glPushMatrix();
    drawOrbit(13.0f + 0.7f);

    glRotatef(uranusOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(13.0f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, uranusMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, uranusEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, uranusSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

    glRotatef(uranusRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.45f, 20, 20);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawNeptune() {
    GLfloat neptuneMaterial[] = {0.3f, 0.5f, 0.9f, 1.0f};
    GLfloat neptuneEmission[] = {0.03f, 0.04f, 0.08f, 1.0f};
    GLfloat neptuneSpecular[] = {0.15f, 0.2f, 0.3f, 1.0f};

    glPushMatrix();
    drawOrbit(16.0f + 0.7f);

    glRotatef(neptuneOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(16.0f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, neptuneMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, neptuneEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, neptuneSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0f);

    glRotatef(neptuneRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.43f, 20, 20);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

void drawPluto() {
    GLfloat plutoMaterial[] = {0.7f, 0.65f, 0.6f, 1.0f};
    GLfloat plutoEmission[] = {0.01f, 0.01f, 0.01f, 1.0f};
    GLfloat plutoSpecular[] = {0.1f, 0.1f, 0.08f, 1.0f};

    glPushMatrix();
    drawOrbit(18.5f + 0.7f);

    glRotatef(plutoOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(18.5f + 0.7f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, plutoMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, plutoEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plutoSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

    glRotatef(plutoRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.15f, 12, 12);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

// BAGIAN 4: ANIMASI, INTERAKSI & KASUS KHUSUS 

//-----------------------------------------------------
// 4.1 Fungsi Menggambar Kasus Khusus (Bumi & Saturnus)
//-----------------------------------------------------

void drawEarthSystem() {
    GLfloat earthMaterial[] = {0.4f, 0.7f, 1.0f, 1.0f};
    GLfloat earthEmission[] = {0.05f, 0.1f, 0.2f, 1.0f};
    GLfloat earthSpecular[] = {0.3f, 0.4f, 0.6f, 1.0f};
    GLfloat moonMaterial[] = {0.9f, 0.9f, 0.85f, 1.0f};
    GLfloat moonEmission[] = {0.02f, 0.02f, 0.02f, 1.0f};
    GLfloat moonSpecular[] = {0.15f, 0.15f, 0.1f, 1.0f};

    glPushMatrix(); 

    drawOrbit(3.5f + 0.7f);

    glRotatef(earthOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(3.5f + 0.7f, 0.0f, 0.0f);

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, earthMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, earthEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earthSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
    glRotatef(earthRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.4f, 20, 20);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glPopMatrix();

    glPushMatrix();
    glRotatef(moonOrbit, 0.2f, 1.0f, 0.1f);
    glTranslatef(0.8f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, moonMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, moonEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moonSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
    drawSphere(0.1f, 12, 12);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glPopMatrix();

    glPopMatrix();
}

void drawSaturnRings(float innerRadius, float outerRadius, int slices, int loops) {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat ringColor[] = {0.8f, 0.75f, 0.6f, 0.6f};
    glColor4fv(ringColor);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);

    glPushMatrix();
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quad, innerRadius, outerRadius, slices, loops);
    glPopMatrix();

    gluDeleteQuadric(quad);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawSaturn() {
    GLfloat saturnMaterial[] = {0.9f, 0.8f, 0.6f, 1.0f};
    GLfloat saturnEmission[] = {0.08f, 0.07f, 0.05f, 1.0f};
    GLfloat saturnSpecular[] = {0.35f, 0.3f, 0.2f, 1.0f};

    glPushMatrix();
    drawOrbit(10.0f + 0.7f);

    glRotatef(saturnOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(10.0f + 0.7f, 0.0f, 0.0f);

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, saturnMaterial);
    glMaterialfv(GL_FRONT, GL_EMISSION, saturnEmission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, saturnSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);
    glRotatef(saturnRotation, 0.0f, 1.0f, 0.0f);
    drawSphere(0.6f, 22, 22);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glPopMatrix();

    glPushMatrix();
    glRotatef(saturnRotation, 0.0f, 1.0f, 0.0f);
    drawSaturnRings(0.7f, 1.2f, 30, 5);
    glPopMatrix();

    glPopMatrix();
}

//-----------------------------------------------------
// 4.2 Fungsi Inti GLUT (Callbacks)
//-----------------------------------------------------

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float cameraX = cameraDistance * cos(cameraAngleV * M_PI / 180.0f) * cos(cameraAngleH * M_PI / 180.0f);
    float cameraY = cameraDistance * sin(cameraAngleV * M_PI / 180.0f);
    float cameraZ = cameraDistance * cos(cameraAngleV * M_PI / 180.0f) * sin(cameraAngleH * M_PI / 180.0f);
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    drawStarField();
    drawNebula();
    drawCosmicDust();

    setupLighting();

    drawSun();
    drawMercury();
    drawVenus();
    drawEarthSystem();
    drawMars();
    drawJupiter();
    drawSaturn();
    drawUranus();
    drawNeptune();
    drawPluto();

    glutSwapBuffers();
}

void update(int value) {
    
    sunRotation += 0.5f;
    mercuryOrbit += mercuryOrbitSpeed;
    mercuryRotation += 15.0f;
    venusOrbit += venusOrbitSpeed;
    venusRotation += 6.0f;
    earthOrbit += earthOrbitSpeed;
    earthRotation += earthRotationSpeed;
    moonOrbit += moonOrbitSpeed;
    marsOrbit += marsOrbitSpeed;
    marsRotation += 8.0f;
    jupiterOrbit += jupiterOrbitSpeed;
    jupiterRotation += 3.0f;
    saturnOrbit += saturnOrbitSpeed;
    saturnRotation += 2.5f;
    uranusOrbit += uranusOrbitSpeed;
    uranusRotation += 1.8f;
    neptuneOrbit += neptuneOrbitSpeed;
    neptuneRotation += 1.5f;
    plutoOrbit += plutoOrbitSpeed;
    plutoRotation += 0.5f;
    starFieldRotation += 0.05f;

    if (autoRotateEnabled) {
        cameraAngleH += 0.25f;
        cameraAngleV = 10.0f + 10.0f * sin(cameraAngleH * 0.5f * M_PI / 180.0f);
    }

    if (sunRotation > 360.0f) sunRotation -= 360.0f;
    if (mercuryOrbit > 360.0f) mercuryOrbit -= 360.0f;
    if (mercuryRotation > 360.0f) mercuryRotation -= 360.0f;
    if (venusOrbit > 360.0f) venusOrbit -= 360.0f;
    if (venusRotation > 360.0f) venusRotation -= 360.0f;
    if (earthOrbit > 360.0f) earthOrbit -= 360.0f;
    if (earthRotation > 360.0f) earthRotation -= 360.0f;
    if (moonOrbit > 360.0f) moonOrbit -= 360.0f;
    if (marsOrbit > 360.0f) marsOrbit -= 360.0f;
    if (marsRotation > 360.0f) marsRotation -= 360.0f;
    if (jupiterOrbit > 360.0f) jupiterOrbit -= 360.0f;
    if (jupiterRotation > 360.0f) jupiterRotation -= 360.0f;
    if (saturnOrbit > 360.0f) saturnOrbit -= 360.0f;
    if (saturnRotation > 360.0f) saturnRotation -= 360.0f;
    if (uranusOrbit > 360.0f) uranusOrbit -= 360.0f;
    if (uranusRotation > 360.0f) uranusRotation -= 360.0f;
    if (neptuneOrbit > 360.0f) neptuneOrbit -= 360.0f;
    if (neptuneRotation > 360.0f) neptuneRotation -= 360.0f;
    if (plutoOrbit > 360.0f) plutoOrbit -= 360.0f;
    if (plutoRotation > 360.0f) plutoRotation -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int width, int height) {
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
        case '=':
            mercuryOrbitSpeed += 0.2f;
            venusOrbitSpeed += 0.1f;
            earthOrbitSpeed += 0.1f;
            moonOrbitSpeed += 0.5f;
            marsOrbitSpeed += 0.05f;
            jupiterOrbitSpeed += 0.02f;
            saturnOrbitSpeed += 0.01f;
            uranusOrbitSpeed += 0.005f;
            neptuneOrbitSpeed += 0.003f;
            plutoOrbitSpeed += 0.001f;
            break;
        case '-':
            if (mercuryOrbitSpeed > 0.2f) mercuryOrbitSpeed -= 0.2f; else mercuryOrbitSpeed = 0.0f;
            if (venusOrbitSpeed > 0.1f) venusOrbitSpeed -= 0.1f; else venusOrbitSpeed = 0.0f;
            if (earthOrbitSpeed > 0.1f) earthOrbitSpeed -= 0.1f; else earthOrbitSpeed = 0.0f;
            if (moonOrbitSpeed > 0.5f) moonOrbitSpeed -= 0.5f; else moonOrbitSpeed = 0.0f;
            if (marsOrbitSpeed > 0.05f) marsOrbitSpeed -= 0.05f; else marsOrbitSpeed = 0.0f;
            if (jupiterOrbitSpeed > 0.02f) jupiterOrbitSpeed -= 0.02f; else jupiterOrbitSpeed = 0.0f;
            if (saturnOrbitSpeed > 0.01f) saturnOrbitSpeed -= 0.01f; else saturnOrbitSpeed = 0.0f;
            if (uranusOrbitSpeed > 0.005f) uranusOrbitSpeed -= 0.005f; else uranusOrbitSpeed = 0.0f;
            if (neptuneOrbitSpeed > 0.003f) neptuneOrbitSpeed -= 0.003f; else neptuneOrbitSpeed = 0.0f;
            if (plutoOrbitSpeed > 0.001f) plutoOrbitSpeed -= 0.001f; else plutoOrbitSpeed = 0.0f;
            break;
        case 'r':
        case 'R':
            sunRotation = mercuryRotation = venusRotation = earthRotation = marsRotation = 0.0f;
            jupiterRotation = saturnRotation = uranusRotation = neptuneRotation = plutoRotation = 0.0f;
            mercuryOrbit = venusOrbit = earthOrbit = moonOrbit = marsOrbit = 0.0f;
            jupiterOrbit = saturnOrbit = uranusOrbit = neptuneOrbit = plutoOrbit = 0.0f;

            cameraAngleH = 0.0f;
            cameraAngleV = 10.0f;
            cameraDistance = 25.0f;
            starFieldRotation = 0.0f;

            mercuryOrbitSpeed = 2.0f; venusOrbitSpeed = 0.8f; earthOrbitSpeed = 0.5f;
            moonOrbitSpeed = 5.0f; marsOrbitSpeed = 0.2f;
            jupiterOrbitSpeed = 0.1f; saturnOrbitSpeed = 0.07f; uranusOrbitSpeed = 0.05f;
            neptuneOrbitSpeed = 0.03f; plutoOrbitSpeed = 0.01f;
            break;
        case 'c':
        case 'C':
            autoRotateEnabled = !autoRotateEnabled;
            printf("Rotasi kamera otomatis: %s\n", autoRotateEnabled ? "ON" : "OFF");
            break;
        case 'z':
            if (cameraDistance > 2.0f) cameraDistance -= 0.5f;
            break;
        case 'x':
            if (cameraDistance < 50.0f) cameraDistance += 0.5f;
            break;
        case 's':
        case 'S':
            initStars();
            initNebula();
            printf("Bintang dan nebula di-regenerate!\n");
            break;
        case 27:
            exit(0);
            break;
    }
}