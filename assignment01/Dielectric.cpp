//
// Created by mySab on 2018/9/27.
//

#include "Dielectric.h"
#include "HitInfo.h"

Dielectric::Dielectric(double _ref_index) : refractive_index(_ref_index) {

}

bool Dielectric::scatter(const Ray &_in_ray, const HitInfo &_hit_info, Vector3 &_attenuation,
                         Ray &_scattered_ray) const {
    // implement your refraction here
    Vector3 reflection = reflect(_in_ray.direction(), _hit_info.normal);
    Vector3 refraction;
    Vector3 normal_out = _hit_info.normal;

    //init doubles assuming reflection, no refraction, and ray entering
    double refr_index_ratio = 1.0 / refractive_index;
    double refl_prob = 1.0;
    double cos = -1 * dot(_in_ray.direction().normalize(), _hit_info.normal);

    _attenuation = Vector3(1.0, 1.0, 1.0);

if(dot(_in_ray.direction(), _hit_info.normal) > 0) {
    normal_out = -1 * normal_out;
    refr_index_ratio = refractive_index;
    cos = refr_index_ratio * dot(_in_ray.direction().normalize(), _hit_info.normal );
}

if(refract(_in_ray.direction(), normal_out, refr_index_ratio, refraction)) {
    double reflectance = (1 - refractive_index) / (1 + refractive_index) * (1 - refractive_index) / ( 1 + refractive_index);
    refl_prob = reflectance * (1 - reflectance) * pow((1-cos), 5);
}

if((double)rand() / (RAND_MAX) < refl_prob) {
    _scattered_ray = Ray(_hit_info.pos, reflection, 0.0);
}
else {
    _scattered_ray = Ray(_hit_info.pos, refraction, 0.0);
}
    return true;
}
