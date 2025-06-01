#version 420 core

in vec2 uvFrag;
in vec3 normalFrag;

out vec4 FragColor;
uniform sampler2D textureSampler;

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
    vec4 AmbientColor = vec4(Light.Color, 1.0f) *
                        Light.AmbientIntensity *
                        vec4(  0.3f, 0.3f, 0.3f/*gMaterial.AmbientColor*/, 1.0f);

    float DiffuseFactor = dot(Normal, -LightDirection);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * vec4(0.3f,0.3f,0.3f/*gMaterial.DiffuseColor*/, 1.0f) * DiffuseFactor;

       // vec3 PixelToCamera = normalize(gCameraLocalPos - LocalPos0);
      //  vec3 LightReflect = normalize(reflect(LightDirection, Normal));
       // float SpecularFactor = dot(PixelToCamera, LightReflect);
      //  if (SpecularFactor > 0) {
      //      float SpecularExponent = texture(gSamplerSpecularExponent, TexCoord0).r * 255.0;
      //      SpecularFactor = pow(SpecularFactor, SpecularExponent);
       //     SpecularColor = vec4(Light.Color, 1.0f) *
      //                      Light.DiffuseIntensity * // using the diffuse intensity for diffuse/specular
       //                     vec4(gMaterial.SpecularColor, 1.0f) *
      //                      SpecularFactor;
      //  }
    }

    return (AmbientColor + DiffuseColor + SpecularColor);
}


vec4 CalcDirectionalLight(vec3 Normal)
{ 
    BaseLight l;
    l.Color = vec3(0.9f,0.9f,0.9f);
    l.AmbientIntensity = 0.4f;
    l.DiffuseIntensity = 0.5f;

    vec3 dir = normalize(vec3(0.1, 0.1, -0.1));
    return CalcLightInternal(l, dir, Normal);
}

void main() {
    //vec4 TotalLight = CalcDirectionalLight(normalFrag);
    
    vec3 lightDir = normalize(vec3(0.1, 0.1, -1.0));
    float lighting = max(dot(normalize(normalFrag), -lightDir), 0.0);
    vec3 color = vec3(lighting);

    //FragColor =  vec4(0.5, 0.5, 0.5, 1.0);//texture(textureSampler, uvFrag) ;//* TotalLight;
    FragColor = vec4(color, 1.0);
//FragColor = vec4(TexCoord.x, TexCoord.y, 1.0, 1.0);
//FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
