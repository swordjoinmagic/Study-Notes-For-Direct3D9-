sampler MainTex;

struct Input{
    float2 uv : TEXCOORD0;
    float3 modelPos : TEXCOORD1;
};


float4 main(Input input) : COLOR{
    return tex2D(MainTex,input.modelPos.yz);
}