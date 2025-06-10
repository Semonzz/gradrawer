#include "Parser.h"
#include "Func.h"

void initGrid() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2 / SCALE, SCREEN_WIDTH / 2 / SCALE, -SCREEN_HEIGHT / 2 / SCALE, SCREEN_HEIGHT / 2 / SCALE);
    glMatrixMode(GL_MODELVIEW);
}

void drawGrid() {
    glColor3f(0.0, 1.0, 1.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = -SCREEN_WIDTH; i <= SCREEN_WIDTH; i++) {
        glVertex2f(i, -SCREEN_HEIGHT);
        glVertex2f(i, SCREEN_HEIGHT);
        glVertex2f(-SCREEN_HEIGHT, i);
        glVertex2f(SCREEN_HEIGHT, i);
    }

    glEnd();
    glFlush();
}

void drawAxes() {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-SCREEN_WIDTH, 0);
    glVertex2f(SCREEN_WIDTH, 0);
    glVertex2f(0, -SCREEN_HEIGHT);
    glVertex2f(0, SCREEN_HEIGHT);
    
    glEnd();
}

void drawGraph() {
    for (Point i : pointsP1) {
        i.draw(0, 1, 0);
    }
    for (Point i : pointsP2) {
        i.draw(1, 0, 0);
    }
}

void displayGrid() {
    drawGrid();
    drawAxes();
    calcGraph();
    drawGraph();
    glFlush();
}

void Grid() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    displayGrid();
    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {

    double worldX, worldY, worldZ;
    GLint viewport[4];
    GLdouble modelview[16], projection[16];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        gluUnProject(x, viewport[3] - y, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);

        Point menuChoice = { worldX, worldY };

        cout << "Mouse coordinates(x, y): " << menuChoice.x << ' ' << menuChoice.y << '\n';

        double eps = dX;

        for (const auto& point : pointsP1) {
            if (std::fabs(point.x - menuChoice.x) < eps) {
                std::cout << "Найдено в pointsP1: ("
                    << point.x << ", " << point.y << ")\n";
                break;
            }
        }

        
        for (const auto& point : pointsP2) {
            if (std::fabs(point.x - menuChoice.x) < eps) {
                std::cout << "Найдено в pointsP2: ("
                    << point.x << ", " << point.y << ")\n";
                break;
            }
        }

    }
}

void menu(int& argc, char**& argv) {
    setlocale(LC_ALL, "RUS");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Gradrawer!");

    initGrid();
    glutDisplayFunc(Grid);
    glutMouseFunc(mouseClick);

    glutMainLoop();
}

void enterParams(){
    string p0s, n1s, n2s, sigmas, psis;
    cout << "Enter p0: ";
    cin >> p0s;

    cout << "Enter n1: ";
    cin >> n1s;

    cout << "Enter n2: ";
    cin >> n2s;

    cout << "Enter sigma: ";
    cin >> sigmas;

    cout << "Enter psi: ";
    cin >> psis;

    int ind = 0;
    vector<Token> tokensP0 = tokenize(p0s);
    vector<Token> tokensN1 = tokenize(n1s);
    vector<Token> tokensN2 = tokenize(n2s);
    vector<Token> tokensSigma = tokenize(sigmas);
    vector<Token> tokensPsi = tokenize(psis);

    map<string, double> variables;

    p0 = parse(tokensP0, ind, variables);
    ind = 0;
    variables.clear();

    n1 = parse(tokensN1, ind, variables);
    ind = 0;
    variables.clear();

    n2 = parse(tokensN2, ind, variables);
    ind = 0;
    variables.clear();

    sig = parse(tokensSigma, ind, variables);
    ind = 0;
    variables.clear();

    psi = parse(tokensPsi, ind, variables);
    ind = 0;
    variables.clear();

    cout << '\n';
    cout << "Result p0: " << p0 << '\n';
    cout << "Result n1: " << n1 << '\n';
    cout << "Result n2: " << n2 << '\n';
    cout << "Result sig: " << sig << '\n';
    cout << "Result psi: " << psi << '\n';
    cout << '\n';
}

int main(int argc, char** argv) {
    cout << "Drawing program!\np1(t) = p0 + n1 * cos(sigma * t)\np2(t) = p0 + n2 * cos(sigma * t + psi)\n";

    enterParams();

    while (true) {
        int choice = 0;
        cout << "What you want to?\n1. Draw graph\n2. Calculate value\n3. Update parameters\n 4. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter min t: ";
            cin >> X_MIN;
            cout << "Enter max t: ";
            cin >> X_MAX;
            cout << "Enter step: ";
            cin >> dX;
            cout << "Enter Scale (20 is optimal): ";
            cin >> SCALE;
            cout << "\np1 - green\np2 - red\n";
            menu(argc, argv);
            break;
        case 2:
            double t;
            cout << "Enter t value: ";
            cin >> t;
            cout << "Value in p1 for this t is: " << funcP1(t) << '\n';
            cout << "Value in p2 for this t is: " << funcP2(t) << '\n';
            break;
        case 3:
            enterParams();
            break;
        case 4:
            return 0;
        default:
            cout << "Wrong choice!\n";
            break;
        }
    }
    return 0;
}