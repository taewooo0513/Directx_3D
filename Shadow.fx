float3 LightDir;
float4 LightColor;
texture MeshText;
float4x4 matW;
float4x4 matV;
struct VS_INPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
	float2 uv : TEXCOORD;
};
VS_OUTPUT vs_Main(VS_INPUT input, float3 Normal)
{
	float3 NormalWorldSpace;
	VS_OUTPUT output;
	output.Pos = input.Pos;
	output.Color = input.Color;
	output.uv = input.uv;
	NormalWorldSpace = normalize(mul(Normal, (float3x3)matW));
	float3 TotalLightColor += LightColor * max(0, dot(NormalWorldSpace, LightDir));
	output.Color = TotalLightColor;
	output.Color.a = 1;

	return output;
}

PS_OUTPUT ps_Main(VS_OUTPUT input)
{
	PS_OUTPUT output;
	output.RGBColor = tex2D(Meshtext, input.uv) * input.Color;
}

struct PS_OUPUT
{
	float4 RGBColor : COLOR0;
};

technique Shader
{
	pass P0
	{
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 ps_Main();
	};
};