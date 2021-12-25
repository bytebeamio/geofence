#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "geofence.h"

bool is_inside(point_ptr p_ptr, polygon_ptr poly_ptr) {
    int number_of_intersections = 0;
    bool inside = false;
    double x = p_ptr->x;
    double y = p_ptr->y;

    if(poly_ptr->number_of_vertices < 3){
        return false;
    } 

    for (size_t i=0; i<poly_ptr->number_of_vertices; i++){
        point_ptr vertices = poly_ptr->vertices;

        double x1 = vertices[i].x;
        double y1 = vertices[i].y;

        double x2 = vertices[(i + 1) % poly_ptr->number_of_vertices].x;
        double y2 = vertices[(i + 1) % poly_ptr->number_of_vertices].y;

        if ( (y1 > y && y2 > y) || (y1 < y && y2 < y) ){
            // No intersection
            // printf("No intersection\n");
            continue;
        } else {
            // intersection of line segment from vertices and line segment from given point
            double s = x1 + (x2-x1) * ((y-y1)/(y2-y1));
            // printf("s=%.2f\n", s);
            if(s <= x) {
                number_of_intersections++;
                if (x == x1 && y == y1) {
                    // if the point is at the vertex, then we need to reduce one count
                    number_of_intersections--;
                } else if (s == x1 && y == y1) {
                    // if the intersection is at a vertex, then we need to reduce one count
                    number_of_intersections--;
                }
                // printf("number of intersections: %d\n", number_of_intersections);
            }
        }
    }
    return (number_of_intersections%2 == 1);
}
