

//float4 PS(Input input) : SV_TARGET
//{
//	return input.colour;
//}
struct PS_INPUT
{
	float4 pColour    : COLOR;
};
struct PS_OUTPUT
{
	float4 pColour    : COLOR;
};


PS_OUTPUT main(PS_INPUT In) : SV_Target
{
	PS_OUTPUT Output;
	Output.pColour = In.pColour;

	return Output;
}