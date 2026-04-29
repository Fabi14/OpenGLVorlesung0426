#version 460 core
in vec2 vertexUVs;
out vec4 fragColor;

uniform vec2 winSize;

void main()
{
	if(gl_FragCoord.y < winSize.y/2)
	{
		fragColor = vec4(step(0.5f,gl_FragCoord.x/winSize.x), 0.0f, 0.0f, 1.0f);
	}
	else{
		fragColor = vec4(1-step(0.5f,gl_FragCoord.x/winSize.x), 0.0f, 0.0f, 1.0f);
	}

	fragColor = fragColor * 1-step(0.5, length(vertexUVs));
}