#include "InputLayout.hlsli"
#include "CommonShaderFunctions.hlsli"

float4 main(VEROUT_POSNORDIFF input) : SV_TARGET
{
    return saturate(float4(HemisphericAmbient(float3(0.0f, 0.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), normalize(input.normal), float4(0.68f, 0.34f, 0.85f, 1.0f)), 1.0f));
	//return float4(1.0f, 0.0f, 1.0f, 1.0f);
}