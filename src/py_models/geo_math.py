import numpy as np
import math
from scipy.spatial import ConvexHull

# "Cross" product as used in UBC-ACM
def cross(p1, p2):
  return p1[0] * p2[1] - p1[1] * p2[0]


# Euclidean istance between two points
def point_distance(p1, p2):
  return np.linalg.norm(p1-p2)


# Return the rotation of point A around P (default [0, 0]) by an
# angle of theta (COUNTER-CLOCKWISE!)
def point_rotation(theta, A, P = np.array([0, 0])):
  sin_t = np.sin(theta)
  cos_t = np.cos(theta)

  NP = np.array(A) - np.array(P)
  NP = np.array([NP[0] * cos_t - NP[1] * sin_t, NP[0] * sin_t + NP[1] * cos_t])
  NP = NP + P
  return NP

# Scale the vector PA with P FIXED by factor K
# Returns a new vector PA' in the same direction as PA, with magnitude
# |PA|k
def scale_vector(P, A, k):
    return (A-P)*k + P

# Reflect around the X-axis
def refX(point):
    return [point[0], -point[1]]

# Reflect around the Y-axis
def refY(point):
    return [-point[0], point[1]]


def scale(point, k):
    return [point[0]* k, point[1]*k]


def shift(point, x=0, y=0):
    return [point[0]+x, point[1]+y]


def angle_between(A, P, B):
    ap = np.sqrt(np.sum((A-P)**2))
    pb = np.sqrt(np.sum((B-P)**2))
    return math.acos(np.dot((A-P), (B-P))/(ap*pb))


def check_collinearity(points):
    for a in range(len(points)):
        for b in range(len(points)):
            for c in range(len(points)):
                if (a == b or b == c or a == c):
                    continue
                if (abs(angle_between(points[a], points[b], points[c])-pi)<0.000001):
                    return True
    return False


def are_convex(points):
    return len(points) == len(ConvexHull(points).vertices)