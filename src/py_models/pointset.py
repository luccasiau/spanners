import numpy as np

class Pointset:
  """
  Class to store and represent R^d pointsets. It has support for the before and
  after edges used in general path greedy.
  """
  def __init__(self):
    self._points = []
    self._before_edges = []
    self._after_edges = []
  
  def __init__(self, file_path=''):
    self._points = []
    self._before_edges = []
    self._after_edges = []
    
    f = open(file_path, 'r')
    for line in f:
        if (len(line.split()) != 2):
            continue
        self._points.append(np.array([float(line.split()[0]), float(line.split()[1])]))
    f.close()
  
  def size(self):
    return len(self._points)
  
  def add_before_edge(self, edge):
    self._before_edges.append(edge)

  def add_after_edge(self, edge):
    self._after_edges.append(edge)

  def get_point(self, idx):
    return self._points[idx]
  
  def print_points(self):
    for i, p in enumerate(self._points):
        print(f'{[i]}: {p}')

  # Format:
  # Line 1: len(points) len(before_edges) len(after_edges)
  # Lines 2-(len(points)+1): coordinates of i-th point
  # Lines (len(points)+2)-(len(points)+len(before_edges)+1): before edges
  # Lines (len(points)+len(before_edges)+2)-
  #  (len(points)+len(before_edges)+len(after_edge)1): after edges
  def print_all_string(self):
    ret = ''
    ret += str(len(self._points)) + ' '
    ret += str(len(self._before_edges)) + ' '
    ret += str(len(self._after_edges)) + '\n'
    for point in self._points:
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
     