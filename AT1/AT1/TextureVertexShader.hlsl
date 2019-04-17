
cbuffer cbPerObject
{
    matrix WVP;
	matrix World;
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
	float3 normal : NORMAL;
	//0 indicates which set of coords, can have multiple
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, WVP);

	//For lighting
	output.normal = mul(input.normal, World);

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    return output;
}