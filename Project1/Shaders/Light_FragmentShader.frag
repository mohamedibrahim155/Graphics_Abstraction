#version 330 core

out vec4 FragColor;

struct Material 
{
   // vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
    float alpha;
    sampler2D alphaMask;
}; 




struct sLight
{
    vec3 position;			
	vec3 diffuse;	// Colour of the light (used for diffuse)
	vec3 specular;	// rgb = highlight colour, w = power
		
	vec3 direction;	// Spot, directional lights
	int lightType;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	        
                   // 0 = pointlight
   float constant;
    float linear;
    float quadratic;	
    
    // 1 = spot light
					// 2 = directional light
    vec3 ambient;

     float cutOff;
    float outerCutOff;
    vec3 color;
    
};


in vec3 FragPosition;  
in vec3 Normal;  
in vec2 TextureCoordinates;
in vec4 meshColour;

uniform vec3 viewPos;
uniform Material material;
uniform bool isMasking;

uniform int DIRECTION_LIGHT_ID =0;
uniform int POINT_LIGHT_ID =1;
uniform int SPOTLIGHT_ID =2;
const int LIGHTCOUNT = 15;
uniform sLight lights[LIGHTCOUNT];


vec3 CalculateLight(vec3 norm, vec3 viewDir );


void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPosition);

    

    vec3 result = CalculateLight(norm,viewDir);
  




//    vec4 finalColor = texture(material.diffuse, TextureCoordinates);
   vec4 finalColor = vec4(result, material.alpha);

    if (isMasking)
    {
        // Sample the mask texture
        vec4 maskSample = texture(material.alphaMask, TextureCoordinates);

        // Multiply the alpha channel of the final color with the alpha channel of the mask
        finalColor.a *= maskSample.a;

        // If the alpha of the mask is below a threshold, discard the fragment
        if (maskSample.a < 0.1)
        {
            discard;
        }
    }

    FragColor = finalColor;
}


vec3 CalculateLight(vec3 norm, vec3 viewDir )
{

    vec3 result =vec3(0,0,0);
  

    for( int index = 0; index < LIGHTCOUNT; index++)
    {


       int LightType = lights[index].lightType;

       if(LightType == DIRECTION_LIGHT_ID)
       {
          vec3 lightDir = normalize(-lights[index].direction);
          float diff = max(dot(norm, lightDir), 0.0);
         vec3 reflectDir = reflect(-lightDir, norm);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

         vec3 ambient = lights[index].ambient   *         meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 diffuse = lights[index].diffuse   * diff  * meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 specular = lights[index].specular * spec  * meshColour.rgb * vec3(texture(material.specular, TextureCoordinates));


//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

         vec3 finalValueforDir =(ambient+diffuse+specular);
         result+=finalValueforDir*lights[index].color;
        
       }
       if(LightType ==POINT_LIGHT_ID)
       {
        vec3 lightDir = normalize(lights[index].position - FragPosition);
        // diffuse shading
        float diff = max(dot(norm, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(lights[index].position - FragPosition);
        float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));    
        // combine results
         vec3 ambient = lights[index].ambient   *         meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 diffuse = lights[index].diffuse   * diff  * meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 specular = lights[index].specular * spec  * meshColour.rgb * vec3(texture(material.specular, TextureCoordinates));

        
//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
         vec3 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
          result+=finalValueforDir;
       }

       if(LightType == SPOTLIGHT_ID)
       {
                vec3 lightDir = normalize(lights[index].position - FragPosition);
         // diffuse shading
         float diff = max(dot(norm, lightDir), 0.0);
         // specular shading
         vec3 reflectDir = reflect(-lightDir, norm);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
         // attenuation
         float distance = length(lights[index].position - FragPosition);
         float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));    
         // spotlight intensity
         float theta = dot(lightDir, normalize(-lights[index].direction)); 
         float epsilon = lights[index].cutOff - lights[index].outerCutOff;
         float intensity = clamp((theta - lights[index].outerCutOff) / epsilon, 0.0, 1.0);
         // combine results
         vec3 ambient = lights[index].ambient   *         meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 diffuse = lights[index].diffuse   * diff  * meshColour.rgb * vec3(texture(material.diffuse, TextureCoordinates));
         vec3 specular = lights[index].specular * spec  * meshColour.rgb * vec3(texture(material.specular, TextureCoordinates));

//
//                vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

         ambient *= attenuation * intensity;
         diffuse *= attenuation * intensity;
         specular *= attenuation * intensity;
         vec3 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
          result+=finalValueforDir;
       }

    }


    return result;
}