float3 LightDir;
float4 LightColor;
texture MeshText;
float4x4 matW;
float4x4 ViewProjMatrix;
sampler MainTex = sampler_state
{
	Texture = (MeshText);
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float4 Normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 Color : COLOR;
};

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
	float2 uv : TEXCOORD;
};
VS_OUTPUT vs_Main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;

	input.Pos = mul(input.Pos, matW);

	output.Pos = mul(input.Pos, ViewProjMatrix);
	output.uv = input.uv;
	
	float3 NormalWorldSpace = normalize(mul(input.Normal, (float3x3)matW));
	float3 TotalLightColor = LightColor * max(0, dot(NormalWorldSpace, LightDir));
	output.Color.rgb = TotalLightColor+float4(1,1,1,1)* float4(0.35,0.35,0.35,0);
	output.Color.a = 1;

	return output;
}

struct PS_OUTPUT
{
	float4 Color : COLOR;
};

PS_OUTPUT ps_Main(VS_OUTPUT input)
{
	PS_OUTPUT output;
	output.Color = tex2D(MainTex, input.Color) * input.Color;
	return output;
}


technique Shader
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_Main();
		PixelShader = compile ps_2_0 ps_Main();
	}
};