

struct PS_INPUT
{
	float4 pColour    : COLOR;
	float4 pPosition  : SV_POSITION;
};


float4 main(PS_INPUT In) : SV_Target
{
	return In.pColour;
}