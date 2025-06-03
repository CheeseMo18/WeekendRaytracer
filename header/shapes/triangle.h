#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "../hittable.h"
#include "../vec3.h"
#include "../interval.h"

class triangle : public hittable{
    public:
        vec3 surfaceNormal;

        //Points in a triangle flow in the anti-clockwise direction
        triangle(const point3 pointA, const point3 pointB, const point3 pointC) : a(pointA), b(pointB), c(pointC){
            vec3 AB = b - a;
            vec3 AC = c - a;
            surfaceNormal = cross(AB, AC);
        }

        bool hit(const ray& r, interval rayT, hit_record& rec) const override{
            //Traingle has one side, see through on the other side
            if(dot(r.direction(), surfaceNormal) > 0) return false;

            vec3 AB = a-b;
            vec3 BC = b-c;
            vec3 CA = c-a;

            //Rotates edge vectors 90 degrees anti-clockwise
            vec3 rotEdgeA = vec3(-AB.y(), AB.x(), 0.0);
            vec3 rotEdgeB = vec3(-BC.y(), BC.x(), 0.0);
            vec3 rotEdgeC = vec3(-CA.y(), CA.x(), 0.0);


            /*
            Calculates dot product between the vector of the ray location that hits the triangle minus the vertex and the normalised rotated edge.
            Positive means hit, negative means miss.
            WARNING: r.at(10.0) needs to be automated.
            */
            bool dirA = dot(r.at(10.0) - b, rotEdgeA / rotEdgeA.length()) > 0;
            bool dirB = dot(r.at(10.0) - c, rotEdgeB / rotEdgeB.length()) > 0;
            bool dirC = dot(r.at(10.0) - a, rotEdgeC / rotEdgeC.length()) > 0;


            return (dirA == dirB && dirB == dirC);
        }

    private:
        point3 a;
        point3 b;
        point3 c;

};

#endif