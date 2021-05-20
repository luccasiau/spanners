import numpy as np
import math
from scipy.spatial import ConvexHull

# "Cross" product as used in UBC-ACM
def cross(p1, p2):
  return p1[0] * p2[1] - p1[1] * p2[0]


# Euclidean distance between two points
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
# Returns a point A' such that the vector PA' is in the same direction of PA,
# with its length multiplied by k
def scale_vector(P, A, k):
    return (A-P)*k + P


# Reflect around the X-axis (negate its y coordinate)
def refX(point):
    return [point[0], -point[1]]


# Reflect around the Y-axis (negate its x coordinate)
def refY(point):
    return [-point[0], point[1]]


# Scale point's coordinates by k
def scale(point, k):
    return [point[0]* k, point[1]*k]


# Shift/translate point by x and y coordinate
def shift(point, x=0, y=0):
    return [point[0]+x, point[1]+y]


# Value (in radians) of angle APB
def angle_between(A, P, B):
    ap = np.sqrt(np.sum((A-P)**2))
    pb = np.sqrt(np.sum((B-P)**2))
    return math.acos(np.dot((A-P), (B-P))/(ap*pb))


# Returns true iff there are three collinear points in the set
def check_collinearity(points):
    for a in range(len(points)):
        for b in range(len(points)):
            for c in range(len(points)):
                if (a == b or b == c or a == c):
                    continue
                if (abs(angle_between(points[a], points[b], points[c])-pi)<0.000001):
                    return True
    return False


# Returns true iff pointset is convex.
# NOTE: If there are three collinear points, it will be considered NOT convex.
def are_convex(points):
    return len(points) == len(ConvexHull(points).vertices)