#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>

#include <vector>

/*Is a pointer some type. 
Every time its value is assigned to another pointer, a count is incremented.
Every time one of those duplicated pointers fall out of scope, the count is decremented.
Once the count reaches 0 (all pointers are out of scope) the object is safely deleted.
*/
using std::make_shared;
using std::shared_ptr;

class hittableList : public hittable{
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittableList(){}
        hittableList(shared_ptr<hittable> object){ add(object); }
        
        void clear(){objects.clear();}
        void add(shared_ptr<hittable> object){
            objects.push_back(object);
        }

        bool hit(const ray& r, double rayTMin, double rayTMax, hit_record& rec) const override{
            hit_record tempRec;
            bool hitAnything = false;
            auto closestSoFar = rayTMax;

            for(const auto& object : objects){
                if(object->hit(r, rayTMin, closestSoFar, tempRec)){
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }
};

#endif