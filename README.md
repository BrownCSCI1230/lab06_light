<!--
 * @FilePath: \lab06_light\README.md
 * @Author: AceSix
 * @Date: 2022-06-15 21:36:49
 * @LastEditors: AceSix
 * @LastEditTime: 2022-06-17 19:25:55
 * Copyright (C) 2022 Brown U. All rights reserved.
-->
# Lab 6: Light


## 1. Intro
In previous labs, you have learnt to perform transformation on shapes and handle coordinate systems. In this lab, we will implement the phong lighting model with previously acquired geometric information.

We will be writing a shader program that shows lighting on spheres. To focus on lighting, some variables necessary for the lighting models are already given. You only have to think about calculating three components of lighting: ambient, diffuse, and specular. And after calculating these components, you need to clip the final intensity to get the actual pixel value.

In this lab, you will focus solely on calculating the light intensity. Intersection points and normals are given to you on a per pixel basis.

## 2. Phong Lighting Model

In this lab, we will implement the phong lighting model, which is one of many lighting models people use for rendering scenes. The phong model we implement here is a simplified version:

$$
I_{\lambda}=k_{a}O_{a\lambda}
+\sum_{i=1}^{m}f_{att}I_{\lambda,i}\left[k_{d}O_{d\lambda}({\bf\hat{N}}\cdot{\bf\hat{L}_{i}})
+k_{s}O_{s\lambda}({\bf\hat{R}_{i}}\cdot{\bf\hat{V}})^{n}\right]
$$

Where:
* $I$ is the intensity of the light (or for our purposes,you can just think of it as the color).
*  $\lambda$ is the subscript for each wavelength (red,green, and blue).
*  $k$ is a constant coefficient. For example, $k_{a}$ isthe ambient coefficient.
*  $O$ is the color of the object being hit by the ray. Forexample, $O_{d\lambda}$ is the diffuse color at the pointof ray intersection on the object.
*  $m$ is the number of lights and i is the index for eachlight.
*  $I_{\lambda\,i}$: is the intensity of light i.
*  ${\bf\hat{N}}$: is the normalized normal on the objectat the point of intersection.
*  ${\bf\hat{L}_{i}}$: is the normalized vector from theintersection to light i.
*  ${\bf\hat{R}_{i}}$: is the normalized, reflected lightvector from light i
*  ${\bf\hat{V}}$: is the normalized line of sight vector
*  n: is the specular exponent (or shininess)

The equation above contains three components: ambient, diffuse and specular. Together they create a pretty realistic visual effect as the image shown below. In the remaining of this chapter, we will break down this equation and implement the components one by one.

<figure>
  <img src="images/full.png" style="width:60%">
  <figcaption>Fig.1 - Complete Phong effect</figcaption>
</figure>
<br clear="all" />

### 2.0 Clipping
To begin with, it is important to know how our rendered image is shown on the screen. An image is a grid of cells shere each cell has its own color values. Here we use the RGBA color format, which is a tuple of four integers in the range of $[0,255]$. But the light intensity we will calculate may range from zero to infinity. This requires converting the intensity values.

There exists many different methods to convert light intensity to finite RGB values. Here we use the simplest way: clipping. The light intensity of each wavelength is limited to the range of $[0,255]$


$$
I_\lambda = min(max(I_\lambda, 0), 255)
$$

##### Task 0
For convenient computation, material parameters we use range from 0 to 1. It is necessary to clip the over light values, map it to $[0,255]$ and convert illumination to unsigned int values.



### 2.1 The Ambient Component
$$
I_{a,\lambda}=k_{a}O_{a\lambda}
$$
We’ll start by adding in the ambient component. The ambient component simply adds a constant amount of lighting to all objects in the scene. This lighting component works regardless of any light sources. Without it many scenes appear too dark. The image below shows the ambient part of Fig.1.

<figure>
  <img src="images/ambient.png" style="width:60%">
  <figcaption>Fig.2 - Ambient effect alone</figcaption>
</figure>
<br clear="all" />

The amount of ambient light will be given by the object color (color) times the amount of ambient light (ambient Intensity).

##### Task 1
Fill in the ambient illumination in the phong equation.

##### Task 2
Add ambient illumination to total illumination after multiplying it by the ambient coefficient.


### 2.2 The Diffuse Component
$$
I_{d,\lambda}=\sum_{i=1}^{m}I_{\lambda,i}k_{d}O_{d\lambda}({\bf\hat{N}}\cdot{\bf\hat{L}_{i}})
$$
Now let’s add the diffuse component, which makes surfaces that are facing towards the light source appear brighter. We will represent how much a surface is facing the light source with the expression ${\bf\hat{N}}\cdot{\bf\hat{L}_{i}}$, where n is the normal vector and L is the normalized vector from the surface point to the light source. The image below shows the diffuse part of Fig.1.

<figure>
  <img src="images/diffuse.png" style="width:60%">
  <figcaption>Fig.3 - Diffuse effect alone</figcaption>
</figure>
<br clear="all" />

In this Lab, we will be working with point light source. Point light is the light that shoots light rays from one simple point. So the vector ${\bf \hat{L}}$ varies with the intersection point.


##### Task 3
Calculate the diretion from intersection point to the source of point light.

##### Task 4
Calculate the cosine value of angle between normal and light direction(aka ${\bf\hat{N}}\cdot{\bf\hat{L}_{i}}$). Beware that both vectors need to be normalized.

##### Task 5
Add diffuse illumination to total illumination after multiplying it by the diffuse coefficient.


### 2.3 The Specular Component
$$
I_{d,\lambda}=\sum_{i=1}^{m}I_{\lambda,i}k_{s}O_{s\lambda}({\bf\hat{R}_{i}}\cdot{\bf\hat{V}})^{n}
$$
Finally we have the specular component, which adds a highlight that makes objects appear shiny. The specular component peaks in brightness when light is reflected in the direction of the eye. We will now use the dot product ${\bf\hat{R}_{i}}\cdot{\bf\hat{V}}$.

In order to make the specular highlight small, we raise the dot product to an exponent called shininess. The higher the exponent, the smaller the highlight. The image below shows the diffuse part of Fig.1.

<figure>
  <img src="images/specular.png" style="width:60%">
  <figcaption>Fig.4 - Specular effect alone</figcaption>
</figure>
<br clear="all" />

##### Task 6
Calculate the reflection direction of the incoming light and eyesight direction based on the data provided.

##### Task 7
Calculate the specular component.


### 2.4 Attenuation
In real life, the intensity of light decreases as the distance between object and light source increases. We demonstrate the effect of attenuation in the picture below. The areas far from light source(left or right edges) is obviously darker than areas close to the light source(center of plain).

<figure>
  <img src="images/attenuation.png" style="width:60%">
  <figcaption>Fig.4 - Attenuation</figcaption>
</figure>
<br clear="all" />

##### Task 8
<span style="color:red">(May be optional)</span>
Calculate the distance from intersection point to light source. Apply attenuation to the diffuse and specular component according to the function below.
$$
f_{att} = min(1, \frac{1}{c_1 + distance*c_2 + distance^2*c_3})
$$


$$
I_{r,\lambda} = k_r*Phong(Intersection, reflect({\bf N}, {\bf V}))
$$
