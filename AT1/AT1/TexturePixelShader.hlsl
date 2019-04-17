
Texture2D shaderTexture; //resource
SamplerState SampleType; //determines which pixels are drawn

struct Light
{
	float3 direction;
	float4 ambientColour;
	float4 diffuseColour;
};

cbuffer cbPerFrame
{
	Light light;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float4 diffuse = shaderTexture.Sample(SampleType, input.tex);
	float3 finalColour;

	finalColour = diffuse * light.ambientColour;
	finalColour += saturate(dot(light.direction, input.normal) * light.diffuseColour * diffuse);

	return float4(finalColour, diffuse.a);

	//Pre-lighting implementation
    //float4 textureColor;
    
    // Sample the pixel color from the texture using the sampler 
    // at this texture coordinate location.
    //textureColor = shaderTexture.Sample(SampleType, input.tex);

    //return textureColor;
}