#pragma once
#include "Head.h"

double p0 = 3, n1 = 1.05, n2 = 0.08, sig = 1, psi = -0.4;

double SCALE = 30;
double X_MIN = -10;
double X_MAX = 10;
double dX = 0.1;

vector<Point> pointsP1;
vector<Point> pointsP2;

void calcGraph() {
    double x, y;
    for (float i = X_MIN; i <= X_MAX; i += dX) {
        x = i;
        y = p0 + n1 * cos(sig * x);
        pointsP1.push_back({ x, y });
    }
    for (float i = X_MIN; i <= X_MAX; i += dX) {
        x = i;
        y = p0 + n1 * cos(sig * x + psi);
        pointsP2.push_back({ x, y  });
    }
}