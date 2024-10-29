#pragma once

#include "raylib.h"

namespace collisions
{

	bool rectangleXrectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	bool circleCircle(Vector2 pos1, float c1r, Vector2 pos2, float c2r);

	bool circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh);

}