#include "InputLayout.hlsli"
#include "Samplers.hlsli"

cbuffer Constant : register(b0)
{
    float4x4 MVP;
}

VEROUT_POSNORDIFF main(VERIN_POSNORDIFF input) 
{

    VEROUT_POSNORDIFF output = (VEROUT_POSNORDIFF) 0;
    input.position.y = 10.0f * heightMap.SampleLevel(pointClamp, (input.position.xz + 50.0f) / 100.0f, 0).x;
    output.position = mul(float4(input.position, 1), MVP);
    output.normal = mul(float4(input.normal, 0), MVP).xyz;
    output.texcoord = input.texcoord.xy;
    return output;
}