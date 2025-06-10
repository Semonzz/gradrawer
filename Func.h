#pragma once
#include "Head.h"

double p0 = 3, n1 = 1.05, n2 = 0.08, sig = 1, psi = -0.4;

double SCALE = 30;
double X_MIN = -10;
double X_MAX = 10;
double dX = 0.1;

vector<Point> pointsP1;
vector<Point> pointsP2;

double funcP1(double t) {
    return p0 + n1 * cos(sig * t);
}

double funcP2(double t) {
    return p0 + n2 * cos(sig * t + psi);
}

void calcGraph() {
    pointsP1.clear();
    pointsP2.clear();
    double x, y;
    for (float i = X_MIN; i <= X_MAX; i += dX) {
        y = funcP1(i);
        pointsP1.push_back({ i, y });
    }
    for (float i = X_MIN; i <= X_MAX; i += dX) {
        y = funcP2(i);
        pointsP2.push_back({ i, y });
    }
}
