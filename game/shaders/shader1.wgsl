struct VertexInput {
    @location(0) position: vec3f
    //@location(1) color: vec3f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) color: vec3f,
};

struct GlobalUniforms {
    projection_matrix: mat4x4f,
    transform_matrix: mat4x4f
};

@group(0) @binding(0) var<uniform> global_uniforms: GlobalUniforms;

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
    var out: VertexOutput;

    out.position = global_uniforms.projection_matrix * global_uniforms.transform_matrix * vec4f(in.position, 1.0);
    if(in.position.z < 0)
    {
      out.color = vec3f(0,0,1);
    }else{
      out.color = vec3f(1,1,0);
    }

    //out.color = in.color;

    return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    return vec4f(pow(in.color, vec3f(2.2)), 1.0);
    //return vec4f(pow(vec3f(0,1,0), vec3f(2.2)), 1.0);
}
