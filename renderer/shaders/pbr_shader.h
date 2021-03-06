#ifndef PBR_SHADER_H
#define PBR_SHADER_H

#include "../core/api.h"

typedef enum {METALNESS_WORKFLOW, SPECULAR_WORKFLOW} workflow_t;

typedef struct ibldata {
    int mip_level;
    cubemap_t *diffuse_map;
    cubemap_t *specular_maps[15];
    texture_t *brdf_lut;
} ibldata_t;

typedef struct {
    vec4_t basecolor_factor;
    float metalness_factor;
    float roughness_factor;
    const char *basecolor_map;
    const char *metalness_map;
    const char *roughness_map;
    /* additional maps */
    const char *normal_map;
    const char *occlusion_map;
    const char *emission_map;
    /* render settings */
    int double_sided;
    int enable_blend;
    float alpha_cutoff;
} pbrm_material_t;

typedef struct {
    vec4_t diffuse_factor;
    vec3_t specular_factor;
    float glossiness_factor;
    const char *diffuse_map;
    const char *specular_map;
    const char *glossiness_map;
    /* additional maps */
    const char *normal_map;
    const char *occlusion_map;
    const char *emission_map;
    /* render settings */
    int double_sided;
    int enable_blend;
    float alpha_cutoff;
} pbrs_material_t;

typedef struct {
    vec3_t position;
    vec2_t texcoord;
    vec3_t normal;
    vec4_t tangent;
    vec4_t joint;
    vec4_t weight;
} pbr_attribs_t;

typedef struct {
    vec3_t world_position;
    vec3_t depth_position;
    vec3_t world_normal;
    vec3_t world_tangent;
    vec3_t world_bitangent;
    vec2_t texcoord;
} pbr_varyings_t;

typedef struct {
    vec3_t light_dir;
    vec3_t camera_pos;
    mat4_t model_matrix;
    mat3_t normal_matrix;
    mat4_t light_vp_matrix;
    mat4_t camera_vp_matrix;
    mat4_t *joint_matrices;
    mat3_t *joint_n_matrices;
    float ambient_strength;
    float punctual_strength;
    texture_t *shadow_map;
    /* metalness workflow */
    vec4_t basecolor_factor;
    float metalness_factor;
    float roughness_factor;
    texture_t *basecolor_map;
    texture_t *metalness_map;
    texture_t *roughness_map;
    /* specular workflow */
    vec4_t diffuse_factor;
    vec3_t specular_factor;
    float glossiness_factor;
    texture_t *diffuse_map;
    texture_t *specular_map;
    texture_t *glossiness_map;
    /* additional maps */
    texture_t *normal_map;
    texture_t *occlusion_map;
    texture_t *emission_map;
    /* for environment */
    ibldata_t *shared_ibldata;
    /* render control */
    workflow_t workflow;
    float alpha_cutoff;
    int shadow_pass;
} pbr_uniforms_t;

/* low-level api */
vec4_t pbr_vertex_shader(void *attribs, void *varyings, void *uniforms);
vec4_t pbr_fragment_shader(void *varyings, void *uniforms, int *discard);

/* high-level api */
model_t *pbrm_create_model(const char *mesh, const char *skeleton,
                           mat4_t transform, pbrm_material_t material,
                           const char *env_name);
model_t *pbrs_create_model(const char *mesh, const char *skeleton,
                           mat4_t transform, pbrs_material_t material,
                           const char *env_name);

#endif
