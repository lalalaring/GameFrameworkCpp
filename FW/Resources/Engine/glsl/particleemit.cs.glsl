// layout (binding = 2) requires 420
// compute shader requires 430
#version 430 core

// uniforms
layout (binding = 1) uniform CB01
{
	vec4	GameTimerData;
}CbSceneCommon;

float CurrentTime()
{
	return CbSceneCommon.GameTimerData.x;
}

float DeltaTime()
{
	return CbSceneCommon.GameTimerData.y;
}

// buffers
struct Particle
{
	vec4	Position_Id;
	vec3	Velocity;
	vec2	Begintime_Lifetime;
};

layout (std430, binding = 0) buffer SSBO00
{
	Particle 	p[];
} g_ParticleList;

struct DeadParticle
{
	uint	Id;
};

layout (std430, binding = 2) buffer SSBO02
{
	DeadParticle 	n[];
} g_DeadParticleList;

struct EmitterInstance
{
	vec3	Position;
	float	EmissionRate;
	float	Accumulator;
};

layout (std430, binding = 3) buffer SSBO03
{
	EmitterInstance 	n[];
} g_EmitterInstanceList;


// Util function


// Input layout qualifier declaring a 16x 16(x 1)local
// workgroup size
layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
void main()
{
	EmitterInstance emt = g_EmitterInstanceList.n[gl_GlobalInvocationID.x];
	if( emt.EmissionRate != 0.0 )
	{
		if( emt.Accumulator > 1.0 )
		{
			emt.Accumulator = 0;
			// emit particle
		}
	}
}