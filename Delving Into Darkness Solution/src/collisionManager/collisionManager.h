#pragma once

namespace collisions
{

	bool rectangleXrectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);

	bool circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh);

}