import numpy as np
import math

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