//struct Input
//{
//	float2 pos : POSITION;
//	float3 colour : COLOR;
//};
//
//struct Output
//{
//	float4 pos : SV_POSITION;
//	float3 colour : COLOR;
//};
cbuffer cbPerObject
{
	float4x4 WVP;
};

VS_Output VS(float4 inPos : POSITION, float4 inColour : COLOR)
{
	VS_Output output;

	output.Pos = mul(inPos, WVP);
	output.Color = inColour;

	return output;
}