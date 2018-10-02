struct Input
{
	float2 pos : POSITION;
	float3 colour : COLOR;
};

struct Output
{
	float4 pos : SV_POSITION;
	float3 colour : COLOR;
};

Output main(Input input)
{
	Output output;

	output.pos = float4(input.pos.x, input.pos.y, 0, 1);
	output.colour = input.colour;

	return output;
}