import numpy as np
from py_models.geo_math import point_distance

class Pointset:
  """
  Class to store and represent R^d pointsets. It has support for the before and
  after edges used in general path greedy.

  Please do not edit the points in the pointset after creation. Just initialize
  a whole new one.
  """
  # If a file_path is provided, it overrides the points
  def __init__(self, points=[], file_path=''):
    self.points = []
    self._before_edges = []
    self._after_edges = []

    if file_path != '':
      f = open(file_path, 'r')
      for line in f:
        if (len(line.split()) != 2):
            continue
        self.points.append(np.array([float(line.split()[0]), float(line.split()[1])]))
      f.close()
    else: self.points = [np.array(p) for p in points]
    
  
  def size(self):
    return len(self.points)
  
  def add_before_edge(self, edge):
    self._before_edges.append(edge)

  def add_after_edge(self, edge):
    self._after_edges.append(edge)

  def get_point(self, idx):
    return self.points[idx]
  
  def print_points(self):
    for i, p in enumerate(self.points):
        print(f'{[i]}: {p}')

  def find_diameter(self):
    longest_distance = 0
    diam = []
    for i in range(len(self.points)):
      for j in range(i+1, len(self.points)):
        dist = point_distance(self.points[i], self.points[j])
        if dist > longest_distance:
          longest_distance = dist
          diam = [i, j]
    return diam

  # Format:
  # Line 1: len(points) len(before_edges) len(after_edges)
  # Lines 2-(len(points)+1): coordinates of i-th point
  # Lines (len(points)+2)-(len(points)+len(before_edges)+1): before edges
  # Lines (len(points)+len(before_edges)+2)-
  #  (len(points)+len(before_edges)+len(after_edge)1): after edges
  def print_all_string(self):
    ret = ''
    ret += str(len(self.points)) + ' '
    ret += str(len(self._before_edges)) + ' '
    ret += str(len(self._after_edges)) + '\n'
    for point in self.points:
      for i, d in enumerate(point):
        ret += str(d) + (' ' if i<len(point)-1 else '\n')
    for be in self._before_edges:
      ret += str(be[0]) + ' ' + str(be[1]) + '\n'
    for ae in self._after_edges:
      ret += str(ae[0]) + ' ' + str(ae[1]) + '\n'
    return ret

  # Prints to console
  def print_all(self):
    print(self.print_all_string())

  # Format is the same as above
  # OVERWRITES FILE
  def print_all_to_file(self, file_path='./temp_file.in'):
    f = open(file_path, 'w')
    f.write(self.print_all_string())
    f.close()
     