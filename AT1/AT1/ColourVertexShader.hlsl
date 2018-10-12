
cbuffer cbPerObject
{
	matrix WVP;
};

struct VS_OUTPUT
{
    float4 vColour : COLOR;
    float4 vPosition : SV_POSITION;
};


VS_OUTPUT main(float4 inPos : POSITION, float4 inColour : COLOR) // main is the default function name
{
	VS_OUTPUT Output;

	float4 pos = inPos;

	// Transform the position from object space to homogeneous projection space
	pos = mul(pos, WVP);
	Output.vPosition = pos;

	// Just pass through the color data
	Output.vColour = inColour;

	return Output;
}

