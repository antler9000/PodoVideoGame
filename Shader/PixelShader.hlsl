#include "VertexShader.hlsl"

float4 PS(in OutVertex outVertex) : SV_TARGET
{
    return float4(outVertex.color, 1);
}