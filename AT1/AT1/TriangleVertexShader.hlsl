
cbuffer cbPerObject
{
	float4x4 WVP;
};

struct VS_INPUT
{
	float3 vPosition   : SV_POSITION;
	float3 vColour : COLOR;
};

struct VS_OUTPUT
{
	float4 vPosition   : SV_POSITION;
	float4 vColour : COLOR;
};


VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
	VS_OUTPUT Output;

	float4 pos = float4(input.vPosition, 1.0f);

	// Transform the position from object space to homogeneous projection space
	pos = mul(pos, WVP);
	Output.vPosition = pos;

	// Just pass through the color data
	Output.vColour = float4(input.vColour, 1.0f);

	return Output;
}

//struct Input
//{
//	float4 position : POSITION;
//	float4 colour : COLOR;
//};
//struct Output
//{
//	float4 Pos : SV_POSITION;
//	float4 Color : COLOR;
//};
//constant buffer, world, viewport, position

//
//Output VS(float4 inPos : POSITION, float4 inColour : COLOR)
//{
//	Output output;
//
//	output.Pos = mul(inPos, WVP);
//	output.Color = inColour;
//
//	return output;
//}

