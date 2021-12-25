#ifndef GEOFENCE_H
#define GEOFENCE_H

typedef struct point {
    double x;
    double y;
} point, *point_ptr;

typedef struct polygon {
    size_t number_of_vertices;
    point vertices[];
} polygon, *polygon_ptr;

bool is_inside(point_ptr p_ptr, polygon_ptr poly_ptr);

#endif