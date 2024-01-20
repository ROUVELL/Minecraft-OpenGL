#include "Engine.h"

//glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
    Engine engine;
    engine.Run();
    /*double now = glfwGetTime();
        if (now - prevTime > 0.016)
        {
            prevTime = now;
            angle += 10.5f;

            if (angle > 359.9f)
                angle = 0.0f;

            const float amplitude = 0.020f;
            const float frequency = 0.75f;

            const float rollAngle = amplitude * sinf(2.0f * 3.1415f * frequency * (float)now);
            const float pitchAgnle = amplitude * cosf(2.0f * 3.1415f * frequency * (float)now);

            UFO.SetRotate(pitchAgnle, glm::radians(angle), rollAngle);
        }*/

    return 0;
}