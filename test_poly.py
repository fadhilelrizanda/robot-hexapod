import matplotlib.pyplot as plt

import math


coxa = 2.5
femur = 4.7
tibia = 9
l1 = coxa+femur+tibia
zoffset = 5
l = 0

gamma = 0
alpha = 0
beta = 0

x = 5.7
y = 5.7
z = 6


x1 = 7.7
y2 = 5.7
z2 = 6

s1 = []
s2 = []


def inverse2():
    global gamma, alpha, beta, x, y, z, coxa, femur, tibia, l1, zoffset, l
    l = math.sqrt(zoffset**2+(l1-coxa))
    gamma = math.atan(x/y)
    alpha1 = math.acos(zoffset/l)
    alpha2 = math.acos((tibia**2-femur**2-l**2)/(-2*femur*l))
    alpha = alpha1+alpha2
    beta = math.acos((l**2-tibia**2-femur**2)/(-2*tibia*femur))
    gamma = gamma*180/math.pi
    alpha = alpha*180/math.pi
    beta = beta*180/math.pi


# inverse2()


# poly
def poly(start_point, end_point, iteration, z_points, max_z):
    step_y = (end_point-start_point)/iteration
    step_z = (max_z-z_points)/(iteration/2)
    z_point = z_points
    y_point = start_point
    i = 0
    down = False
    while(y_point < end_point):
        y_point = y_point+step_y
        print(y_point)
        print("---=---")
        print("z: "+str(z_point))
        s1.append(i)
        s2.append(z_point)
        i += 1
        if(i > iteration/2):
            z_point = z_point-step_z
        else:
            z_point = z_point + step_z


poly(3, 10, 30, 6, 8)


plt.plot(s1, s2)
plt.show()
