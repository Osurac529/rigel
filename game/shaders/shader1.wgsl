struct VertexInput {
    @location(0) position: vec3f,
    @location(2) texture_coordinate: vec2f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) texture_coordinate: vec2f,
    @location(1) color: vec3f,
};

struct GlobalUniforms {
    projection_matrix: mat4x4f,
    transform_matrix: mat4x4f
};

@group(0) @binding(0) var<uniform> global_uniforms: GlobalUniforms;
@group(0) @binding(1) var texture: texture_2d<f32>;
@group(0) @binding(2) var texture_sampler: sampler;

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
    var out: VertexOutput;

    out.position = global_uniforms.projection_matrix * global_uniforms.transform_matrix * vec4f(in.position, 1.0);
    out.texture_coordinate = in.texture_coordinate;
    if(in.position.z < 0)
    {
      out.color = vec3f(0,0,1);
    }else{
      out.color = vec3f(1,1,0);
    }

    return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    return vec4f(pow(in.color * textureSample(texture, texture_sampler, in.texture_coordinate).rgb, vec3f(2.2)), 1.0);
}
