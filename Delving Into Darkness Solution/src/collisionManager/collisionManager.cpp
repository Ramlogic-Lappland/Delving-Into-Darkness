#include "collisionManager.h"

#include <iostream>
#include "raylib.h"

namespace collisions
{

	bool rectangleXrectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) 
	{

		// are the sides of one rectangle touching the other?

		if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
			r1x <= r2x + r2w &&    // r1 left edge past r2 right
			r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
			r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
			return true;
		}
		return false;
	}

	bool circleCircle(Vector2 pos1, float c1r, Vector2 pos2, float c2r)
	{

		// get distance between the circle's centers
		// use the Pythagorean Theorem to compute the distance
		float distX = pos1.x - pos2.x;
		float distY = pos1.y - pos2.y;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the sum of the circle's
		// radii, the circles are touching!
		if (distance <= c1r + c2r) {
			return true;
		}
		return false;
	}

	bool circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh) 
	{

		// temporary variables to set edges for testing
		float testX = cx;
		float testY = cy;

		// which edge is closest?
		if (cx < rx)         testX = rx;      // test left edge
		else if (cx > rx + rw) testX = rx + rw;   // right edge
		if (cy < ry)         testY = ry;      // top edge
		else if (cy > ry + rh) testY = ry + rh;   // bottom edge

		// get distance from closest edges
		float distX = cx - testX;
		float distY = cy - testY;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the radius, collision!
		if (distance <= radius) {
			return true;
		}
		return false;
	}

}
