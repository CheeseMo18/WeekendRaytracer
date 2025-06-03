#ifndef MATERIAL_H
#define MATERIAL_H
#include "../hittable.h"
#include "../colour.h"

class material {
    public: 
        virtual ~material() = default;

        virtual bool scatter(const ray& rIn, const hit_record& rec, colour& attenuation, ray& scattered) const{
            return false;
        }
};

#endif