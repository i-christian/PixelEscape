#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "config.h"
#include "linear_algebra.h"
#include "game_data.h"

/* Constants */
#define RAY_EPS (WALL_SIZE / 3.0f)

/**
 * struct RayTuple - represent horizontal and vertical rays
 * @vRay: vertical ray
 * @hRay: horizontal ray
 */
typedef struct RayTuple
{
    Vector3f vRay;
    Vector3f hRay;
} RayTuple;

/* Global data */
extern Vector3f viewplaneDir;
extern float distFromViewplane;
extern Matrix3f counterClockwiseRotation;
extern Matrix3f clockwiseRotation;
extern RayTuple rays[VIEWPLANE_LENGTH];

/* Functions */

void initializeRayDirections(gameData *gameData);

void extendRaysToFirstHit(RayTuple *rays);

Vector3f findVerticalRayStepVector(Vector3f *ray);


Vector3f findHorizontalRayStepVector(Vector3f *ray);

void raycast(RayTuple *rays);


Vector3f getTileCoordinateForVerticalRay(Vector3f *ray);

Vector3f getTileCoordinateForHorizontalRay(Vector3f *ray);


void updateRaycaster(gameData *gameData);


void initRaycaster(void);


#endif /* RAYCASTER_H */
