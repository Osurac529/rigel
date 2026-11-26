struct PerFrameUniforms
{
    world_to_camera: mat4x4f,
    camera_to_projection: mat4x4f
};

struct PerDrawUniforms
{
    local_to_world: mat4x4f,
    normal_transform: mat3x3f
};

struct VertexInput
{
    @location(0) position: vec3f,
    @location(1) normal: vec3f,
    @location(2) texture_coordinate: vec2f,
    @location(6) tangent: vec4f,
};

struct FragmentInput
{
    @builtin(position) position: vec4f,
    @location(0) world_position: vec3f,
    @location(1) world_tangent: vec3f,
    @location(2) world_normal: vec3f,
    @location(3) texture_coordinate: vec2f,
    @location(4) @interpolate(flat) handedness: f32,
};

struct FragmentOutput
{
    @location(0) world_position : vec4f,
    @location(1) world_normal : vec4f,
    @location(2) albedo : vec4f,
    @location(3) roughness_metallic : vec2f,
};

// performance is better when groups are ordered from least to higher frequent changes
@group(0) @binding(0) var<uniform> per_frame_uniforms : PerFrameUniforms;
@group(1) @binding(0) var albedo_texture : texture_2d<f32>;
@group(1) @binding(1) var normal_texture : texture_2d<f32>;
@group(1) @binding(2) var roughness_texture : texture_2d<f32>;
@group(1) @binding(3) var texture_sampler : sampler;
@group(2) @binding(0) var<uniform> per_draw_uniforms : PerDrawUniforms;

@vertex
fn vs_main(in: VertexInput) -> FragmentInput {
    var out: FragmentInput;

    out.world_position = (per_draw_uniforms.local_to_world * vec4f(in.position, 1)).xyz;

    out.position = per_frame_uniforms.camera_to_projection * 
                   per_frame_uniforms.world_to_camera * 
                   vec4f(out.world_position, 1);

    out.texture_coordinate = in.texture_coordinate;

    // Gram-Schmidt re-orthogonalize
    // This is theoretically not necessary but we will keep it since compressing
    // tangents into low-precision formats may cause some drift, will experiment with this.
    let tangent = normalize(in.tangent.xyz - dot(in.tangent.xyz, in.normal) * in.normal);

    out.world_tangent = per_draw_uniforms.normal_transform * tangent;

    out.world_normal = per_draw_uniforms.normal_transform * in.normal;

    out.handedness = in.tangent.w;

    return out;
}

@fragment
fn fs_main(in: FragmentInput) -> FragmentOutput {
    var out: FragmentOutput;

    let world_normal = normalize(in.world_normal);
    var world_tangent = normalize(in.world_tangent);

    // Gram-Schmidt orthogonalization to fix interpolation drift
    world_tangent = normalize(world_tangent - dot(world_tangent, world_normal) * world_normal);

    // reconstruct bi-tangent
    let world_bi_tangent = cross(world_normal, world_tangent) * in.handedness;

    let TBN = mat3x3f(world_tangent, world_bi_tangent, world_normal);

    let normal = textureSample(normal_texture, texture_sampler, in.texture_coordinate).xyz;

    // unpack from [0,1] to [-1,1]
    let tangent = normal * 2.0 - 1.0;

    out.world_normal = vec4f(normalize(TBN * tangent), 1);

    out.world_position = vec4f(in.world_position, 1);

    //out.albedo = textureSample(albedo_texture, texture_sampler, in.texture_coordinate).rgba;
    out.albedo = vec4f(1,0,0,1);

    out.roughness_metallic = textureSample(roughness_texture, texture_sampler, in.texture_coordinate).rg;

    return out;
}
