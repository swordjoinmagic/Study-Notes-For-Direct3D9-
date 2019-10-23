matrix model;
matrix view;
matrix projection;

struct a2v{
    float4 vertex : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct v2f{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 modelPos : TEXCOORD1;
};

v2f main(a2v v){
    v2f o;
    float4x4 mvp = mul(mul(model,view),projection);
    o.pos = mul(v.vertex,mvp);    
    o.uv = v.texcoord;
    o.modelPos = v.vertex.xyz;
    return o;
}