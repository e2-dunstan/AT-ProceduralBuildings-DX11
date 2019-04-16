cbuffer cbPerObject
{
	matrix W;
	matrix VP;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	//0 indicates which set of coords, can have multiple
	float3 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, W);
	output.position = mul(input.position, VP);

	output.tex = input.tex;

	//Light
	output.normal = mul(input.normal, (float3x3)W);
	output.normal = normalize(output.normal);

	return output;
}