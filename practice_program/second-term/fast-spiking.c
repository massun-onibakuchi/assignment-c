#include <stdio.h>
#define N 10000

float a = 0.02;
float b = 0.2;
float c = -65.0;
float d = 2.0;
float vth = 30.0;
float v0 = -65.0;
float u0 = 8.0;
float dt = 0.10;
float step = 300;

float f(float t, float v, float u)
{
    float I = 0.0;
    if (t > step)
        I = 10;
    // I = (t - step) * 0.01;
    return 0.04 * v * v + 5 * v + 140.0 - u + I;
}
float g(float t, float v, float u)
{
    return a * (b * v - u);
}

int main()
{
    float t, v = v0, u = u0;
    float dv, du;
    FILE *fd = fopen("../data/df.csv", "w");
    for (int i = 0; i < N; i++)
    {
        t = i * dt;
        dv = f(t, v, u) * dt;
        du = g(t, v, u) * dt;
        v += dv;
        u += du;
        if (v >= vth)
        {
            v = c;
            u += d;
        }
        fprintf(fd, "%f,%f\n", t, v);
    }
}