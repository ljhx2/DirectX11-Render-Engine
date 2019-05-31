//=============================================================================
// BuildShadowMap.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Effect used to build the shadow map.
//
// A lot of code is copy and pasted from DisplacementMap.fx.  When drawing 
// depth to shadow map, we need to tessellate the geometry the same way
// when rendering from the eye so that the shadow map records the same
// geometry the eye sees.
//=============================================================================


cbuffer cbPerObject
{
	//float4x4 gWorld;
	//float4x4 gWorldInvTranspose;
	//float4x4 gViewProj;
	float4x4 gWorldViewProj;
	float4x4 gTexTransform;
}; 

cbuffer cbSkinned
{
	float4x4 gBoneTransforms[96];
};

// Nonnumeric values cannot be added to a cbuffer.
Texture2D gDiffuseMap;
 
SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VertexIn
{
	float3 PosL     : POSITION;
	float3 NormalL  : NORMAL;
	float2 Tex      : TEXCOORD;
};

struct SkinnedVertexIn
{
	float3 PosL       : POSITION;
	float3 NormalL    : NORMAL;
	float2 Tex        : TEXCOORD;
	float4 TangentL   : TANGENT;
	float3 Weights    : WEIGHTS;
	uint4 BoneIndices : JOINTINDICES;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float2 Tex  : TEXCOORD;
};
 
VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Tex  = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	return vout;
}

VertexOut SkinnedVS(SkinnedVertexIn vin)
{
    VertexOut vout;

	// Init array or else we get strange warnings about SV_POSITION.
	float weights[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	weights[0] = vin.Weights.x;
	weights[1] = vin.Weights.y;
	weights[2] = vin.Weights.z;
	weights[3] = 1.0f - weights[0] - weights[1] - weights[2];

	float3 posL     = float3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < 4; ++i)
	{
	    // Assume no nonuniform scaling when transforming normals, so 
		// that we do not have to use the inverse-transpose.
	    posL     += weights[i]*mul(float4(vin.PosL, 1.0f), gBoneTransforms[vin.BoneIndices[i]]).xyz;
	}
 
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(posL, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	return vout;
}


// This is only used for alpha cut out geometry, so that shadows 
// show up correctly.  Geometry that does not need to sample a
// texture can use a NULL pixel shader for depth pass.
void PS(VertexOut pin)
{
	float4 diffuse = gDiffuseMap.Sample(samLinear, pin.Tex);

	// Don't write transparent pixels to the shadow map.
	clip(diffuse.a - 0.15f);
}


RasterizerState Depth
{
	// [From MSDN]
	// If the depth buffer currently bound to the output-merger stage has a UNORM format or
	// no depth buffer is bound the bias value is calculated like this: 
	//
	// Bias = (float)DepthBias * r + SlopeScaledDepthBias * MaxDepthSlope;
	//
	// where r is the minimum representable value > 0 in the depth-buffer format converted to float32.
	// [/End MSDN]
	// 
	// For a 24-bit depth buffer, r = 1 / 2^24.
	//
	// Example: DepthBias = 100000 ==> Actual DepthBias = 100000/2^24 = .006

	// You need to experiment with these values for your scene.
	DepthBias = 100000;
    DepthBiasClamp = 0.0f;
	SlopeScaledDepthBias = 1.0f;
};

technique11 BuildShadowMapTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( NULL );

		SetRasterizerState(Depth);
    }
}

technique11 BuildShadowMapAlphaClipTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}

technique11 BuildShadowMapSkinnedTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, SkinnedVS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( NULL );

		SetRasterizerState(Depth);
    }
}

technique11 BuildShadowMapAlphaClipSkinnedTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, SkinnedVS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}