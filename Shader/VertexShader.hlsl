cbuffer object : register(b0)
{
    float4x4 gWorld;
    float4x4 gInvTransWorld;
}

cbuffer camera : register(b1)
{
    float4x4 gViewProj;
}

struct InVertex
{
    float3 posL     : POSITION;
    float3 normalL  : NORMAL;
    float3 color    : COLOR;
};

struct OutVertex
{
    float3 posW     : POSITION;
    float4 posH     : SV_POSITION;
    float3 normalW  : NORMAL;
    float3 color    : COLOR;
};

void VS(in InVertex inVertex, out OutVertex outVertex)
{
    outVertex.posW = mul(float4(inVertex.posL, 1.0f), gWorld).xyz;
    outVertex.posH = mul(float4(outVertex.posW, 1.0f), gViewProj);
    
    outVertex.normalW = mul(float4(inVertex.normalL, 0.0f), gInvTransWorld).xyz;
    
    outVertex.color = inVertex.color;
}