#include <stdio.h>
#include <stdbool.h>
#include "geofence.h"

typedef struct testcase {
    point_ptr point;
    polygon_ptr polygon;
    bool inside;
} testcase;

point origin = {
    .x = 0,
    .y = 0
};

point p2 = {
    .x = -1,
    .y = 0
};

point p3 = {
    .x = 0,
    .y = 0.5
};

point p4 = {
    .x = 5,
    .y = 0.5
};

point p5 = {
    .x = 0.5,
    .y = 0
};

point p6 = {
    .x = -1,
    .y = 1
};

polygon poly1 = {
    .number_of_vertices = 4,

    {
        {
            .x = 1,
            .y = 1
        },
        {
            .x = 1,
            .y = -1
        },
        {
            .x = -1,
            .y = -1
        },
        {
            .x = -1,
            .y = 1
        }
    }
};
polygon poly2 = {
    .number_of_vertices = 4,

    {
        {
            .x = 0,
            .y = 1
        },
        {
            .x = 1,
            .y = 0
        },
        {
            .x = 0,
            .y = -1
        },
        {
            .x = -1,
            .y = 0
        }
    }
};
polygon poly3 = {
    .number_of_vertices = 5,

    {
        {
            .x = 0,
            .y = 1
        },
        {
            .x = 1,
            .y = 0
        },
        {
            .x = 0,
            .y = -1
        },
        {
            .x = -1,
            .y = 0
        },
        {
            .x = 0,
            .y = 0
        }
    }
};

const polygon_ptr polygons[] = {
    &poly1,
};

testcase testcases[] = {
    {&origin, &poly1, true},
    {&p2, &poly1, true},
    {&p3, &poly2, true},
    {&p4, &poly2, false},
    {&origin, &poly2, true},
    {&p2, &poly2, true},
    {&p3, &poly3, true},
    {&origin, &poly3, true},
    {&p5, &poly3, true},
    {&p6, &poly3, false}
};

int main() {
    for (size_t i=0; i<sizeof(testcases)/sizeof(testcases[0]); i++){
        printf("Test %ld: ", i+1);
        testcase t = testcases[i];
        bool response = is_inside(t.point, t.polygon);
        if(response == t.inside) {
            printf("Pass\n");
        } else {
            printf("Fail\n");
            printf("\tPoint: (%.2f, %.2f)\n", t.point->x, t.point->y);
            printf("\tPolygon:\n");
            for(size_t i=0; i<t.polygon->number_of_vertices; i++){
                point p = (t.polygon->vertices)[i];
                printf("\t\t(%.2f, %.2f)\n", p.x, p.y);
            }
            printf("\tExpected answer: %s\n", t.inside? "true":"false");
            printf("\tReceived answer: %s\n", !t.inside? "true":"false");
        }
    }
    return 0;
}
