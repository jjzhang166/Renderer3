#include "InputLayout.hlsli"

cbuffer Constant : register(b0)
{
    float4x4 MVP;
}

VEROUT_POSNORDIFF main(VERIN_POSNORDIFF input) 
{

    VEROUT_POSNORDIFF output = (VEROUT_POSNORDIFF) 0;
    output.position = mul(float4(input.position, 1), MVP);
    output.normal = mul(float4(input.normal, 0), MVP).xyz;
    output.texcoord = input.texcoord.xy;
    return output;
}