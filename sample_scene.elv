[Frame]
width = 1920
height 823
num_samples 128
recursion_depth 50
filename image.png

[Camera]
position 13, 2, 3
target 0, 0, 0
vup 0, 1, 0
fov 35.0
focus_distance 10.0
aperture 0.1

[Material]
name "mat1"
type Metal
albedo 127, 127, 255
roughness 0.3

[Material]
name "mat2"
type Diffuse
albedo 255, 127, 127

[Material]
name "ground_material"
type Diffuse
albedo 127, 127, 127

[Object]
type Sphere
position 0.5, 1.0, 3.0
radius 1.0
material "mat1"

[Object]
type Sphere
position 4.0, 1.5, 0.0
radius 1.0
material "mat2"

[Object]
type Sphere
position 0.0, -1000, 0.0
radius 1000
material "ground_material"