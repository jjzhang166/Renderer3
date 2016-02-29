#include "InputLayout.hlsli"
#include "CommonShaderFunctions.hlsli"
#include "Samplers.hlsli"

float4 main(VEROUT_POSNORDIFF input) : SV_TARGET
{

    float4 diffuse = diffuseMap.Sample(linearClamp, input.texcoord);
    //return saturate(diffuse * float4(64.0f / 255.0f, 156.0f / 255.0f, 255.0f / 255.0f, 1.0f));
    return saturate(diffuse * float4(HemisphericAmbient(float3(0.0f, 0.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), normalize(input.normal), float4(255.0f / 255.0f, 156.0f / 255.0f, 200.0f / 255.0f, 1.0f)), 1.0f));
	//return float4(1.0f, 0.0f, 1.0f, 1.0f);
}